#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HISTORIQUE 100
#define MAX_CARS 100
typedef struct {
    int top;
    int capacity;
    void** array;
} Stack;
Stack* createStack(int capacity);
int isStackFull(Stack* stack);
int isStackEmpty(Stack* stack);
void push(Stack* stack, void* item);
void* pop(Stack* stack);
typedef struct {
    int numcar;
    char marque[100];
    char etat [100];
}car;
typedef struct {
    char date[20];
    char action[100];
} historique;
void Sauvgarder(Stack* cars, Stack* histories);
void AjouterCar(Stack* cars, car* newCar);
void supprimer_car_en_panne(Stack* cars);
void Modifier_car(Stack* cars);
void Afficher_Historique(Stack* histories);
//
void Afficherlesvoituresdispo(Stack* cars);
void louercar(Stack* cars, Stack* histories);
void discriptioncar(Stack* cars);
void retournercar(Stack* histories);
int main(){
    Stack* cars = createStack(MAX_CARS);
    Stack* histories = createStack(MAX_HISTORIQUE);
    int util;
     do {
        printf("Bienvenue dans notre E-CARS Application:\nVous etes l'agent de E-CARS (1) ou Locataire(2):");scanf("%d",&util);
        switch (util) {
            case 1:
                printf("Bonjour Mr/MMe ceci est votre MENU;\n");
                printf("1. Ajouter une voiture\n");
                printf("2. Supprimer une voiture qui est en panne.\n");
                printf("3. Modifier la description et l'état d'une voiture.\n");
                printf("4. Afficher l'historique des locations.\n");
                printf("5. Sauvgarder les donnees\n");
                printf("6. Quitter l'APP\n");
                int choix;
                do {
                    printf("saisir votre choix:");scanf("%d",&choix);
                }while ((choix>=1) && (choix<=6));
                switch(choix){
                    case 1:
                        AjouterCar(cars,NULL);
                        break;
                    case 2:
                        supprimer_car_en_panne(cars);
                        break;
                    case 3:
                        Modifier_car(cars);
                        break;
                    case 4:
                        Afficher_Historique(histories);
                        break;
                    case 5:
                        Sauvgarder(cars,histories);
                        break;
                    case 6:
                        printf("Quitte E-Cars Application. Alakhyyr <3 !\n");
                        break;
                        default:
                        printf("Non valider!!!");
                }
                
            case 2:
                char nom[50];
                printf("ecrire vote Nom:");scanf("%s",&nom);
                printf("Bonjour Mr/MMe %s ceci est votre MENU;\n",nom);
                printf("1. Afficher les voitures disponible.\n");
                printf("2. Louer une voiture.\n");
                printf("3. Afficher la description d'une voiture.\n");
                printf("4. Retour d'une voiture en cas de réclamation.\n");
                printf("5. Sauvguarder les donnees.\n");
                printf("6. Quitter l'App.\n");
                int choix1;
                do {
                    printf("saisir votre choix:");scanf("%d",&choix1);
                }while ((choix1>=1) && (choix1<=6));
                switch(choix1){
                    case 1:
                        Afficherlesvoituresdispo(cars);
                        break;
                    case 2:
                        louercar(cars,histories);
                        break;
                    case 3:
                        discriptioncar(cars);
                        break;
                    case 4:
                        retournercar(histories);
                        break;
                    case 5:
                        Sauvgarder(cars,histories);
                        break;
                    case 6:
                        printf("Aurevoir <3 !!!");
                        break;
                    default:
                        printf("repeter svp!");
                }
                
            default:
                printf("svp repeter.\n");
        }
    } while ((util=1)||(util=2));
    free(cars->array);
    free(cars);
    free(histories->array);
    free(histories);
    return 0;
};
// Créer une pile avec une capacité donnée
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (void**)malloc(capacity * sizeof(void*));
    return stack;
}
// Vérifier si la pile est pleine
int isStackFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}
// Vérifier si la pile est vide
int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}
// Ajouter un élément à la pile
void push(Stack* stack, void* item) {
    if (isStackFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}
// Retirer un élément de la pile
void* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->array[stack->top--];
}
void AjouterCar(Stack* cars, car* newCar) {
    if (!isStackFull(cars)) {
        if (newCar == NULL) {
            newCar = (car*)malloc(sizeof(car));
            printf("Enter car num: ");
            scanf("%d", &newCar->numcar);
            printf("Enter marque: ");
            scanf("%s", &newCar->marque);
            strcpy(newCar->etat, "disponible");
        }
        push(cars, newCar);
        printf("Car added successfully!\n");
    } else {
        printf("Maximum number of cars reached.\n");
    }
};
void supprimer_car_en_panne(Stack* cars) {
    printf("Entre l'indice de la car en panne: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < cars->top + 1) {
        car* removedCar = (car*)pop(cars);
        free(removedCar); 
        printf("voiture supprimée qvec succee!\n");
    } else {
        printf("indice invalide.\n");
    }
};
void Modifier_car(Stack* cars) {
    printf("Entrer l'indice du voiture a modifier: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < cars->top + 1) {
        car* currentCar = (car*)pop(cars);
        printf("Enter new brand: ");
        scanf("%d", currentCar->numcar);
        printf("Entrer nouvelle marque: ");
        scanf("%s", currentCar->marque);
        printf("Entrer nouvelle etat: ");
        scanf("%s", currentCar->etat);
        push(cars, currentCar);
        printf("voiture mofifiée avec succees!\n");
    } else {
        printf("indice invalide.\n");
    }
};
void Afficher_Historique(Stack* histories) {
    printf("Historique de louer:\n");
    Stack* tempStack = createStack(histories->capacity);
    while (!isStackEmpty(histories)) {
        car* rentedCar = (car*)pop(histories);
        printf("%d %s  louée\n", rentedCar->numcar, rentedCar->marque);
        push(tempStack, rentedCar);
    }
    while (!isStackEmpty(tempStack)) {
        push(histories, pop(tempStack));
    }
    free(tempStack->array);
    free(tempStack);
};
void Sauvgarder(Stack* cars, Stack* histories) {
    FILE* file = fopen("Ecars.txt", "w");
    if (file == NULL) {
        printf("Euror d'ouvrire le fichier.\n");
        return;
    }

    fprintf(file, "Cars Data:\n");
    Stack* tempCarStack = createStack(cars->capacity);
    while (!isStackEmpty(cars)) {
        car* currentCar = (car*)pop(cars);
        fprintf(file, "%d %s %s\n", currentCar->numcar, currentCar->marque, currentCar->etat);
        push(tempCarStack, currentCar);
    }
    while (!isStackEmpty(tempCarStack)) {
        push(cars, pop(tempCarStack));
    }
    free(tempCarStack->array);
    free(tempCarStack);
    fprintf(file, "\nHistorique de louer:\n");
    Stack* tempHistoryStack = createStack(histories->capacity);
    while (!isStackEmpty(histories)) {
        car* rentedCar = (car*)pop(histories);
        fprintf(file, "%d %s louee\n", rentedCar->numcar, rentedCar->marque);
        push(tempHistoryStack, rentedCar);
    }
    while (!isStackEmpty(tempHistoryStack)) {
        push(histories, pop(tempHistoryStack));
    }
    free(tempHistoryStack->array);
    free(tempHistoryStack);
    fclose(file);
    printf("le donnes sont sauvgardés avec succees!\n");
};
void Afficherlesvoituresdispo(Stack* cars) {
    printf("les voitures disponible:\n");
    Stack* tempStack = createStack(cars->capacity);
    while (!isStackEmpty(cars)) {
        car* currentCar = (car*)pop(cars);
        if (strcmp(currentCar->etat, "Available") == 0) {
            printf("%d %s\n", currentCar->numcar, currentCar->marque);
        }
        push(tempStack, currentCar);
    }
    while (!isStackEmpty(tempStack)) {
        push(cars, pop(tempStack));
    }
    free(tempStack->array);
    free(tempStack);
};
void louercar(Stack* cars, Stack* histories) {
    Afficherlesvoituresdispo(cars);
    printf("entre l'indice de voiture à louer: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < cars->top + 1) {
        car* rentedCar = (car*)pop(cars);
        strcpy(rentedCar->etat, "Rented");
        push(histories, rentedCar);
        printf("voiture louee!\n");
    } else {
        printf("indice invalide!.\n");
    }
};
void discriptioncar(Stack* cars) {
    printf("Entrer l'indice de voiture recherche: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < cars->top + 1) {
        car* currentCar = (car*)pop(cars);
        printf("deiscription de la voiture:\n");
        printf("Num: %d\n", currentCar->numcar);
        printf("Model: %s\n", currentCar->marque);
        printf("etat: %s\n", currentCar->etat);
        push(cars, currentCar);
    } else {
        printf("Indice invalide.\n");
    }
};
void retournercar(Stack* histories) {
    printf("Entrer l'indice de la voiture retourner: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < histories->top + 1) {
        car* returnedCar = (car*)pop(histories);
        free(returnedCar);  
        printf("voiture retourner avec succees!\n");
    } else {
        printf("indice invalide.\n");
    }
}