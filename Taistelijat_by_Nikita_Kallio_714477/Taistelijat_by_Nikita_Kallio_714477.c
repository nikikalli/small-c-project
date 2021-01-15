#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

//Player struct
typedef struct {

	char name[30], weapon[30];
	int HP, Exp, wepDmg;

} Player;

//Game struct
typedef struct {

    unsigned int numberOfPlayers;
	Player* allPlayers;

} Game;

void addPlayers(Game* game, char* name1,  int hp1, char* weapon1, int dmg)
{

    //Updating the number of players in the game
    unsigned int number = game->numberOfPlayers + 1;
    game->numberOfPlayers = number;

    //Getting more memory space for new player
    game->allPlayers = realloc(game->allPlayers, (game->numberOfPlayers+1) * sizeof(Player));

    //Setting the name of a player
    strcpy(game->allPlayers[number - 1].name, name1);

    //In case of hp being negative we set the player dead
    if (hp1 < 0)
    {
        game->allPlayers[number - 1].HP = 0;
    }
    else if (hp1 > 1000) // So that hp wont get bugger than size of int
    {
        game->allPlayers[number - 1].HP = 1000;
    }
    else
    {
        game->allPlayers[number - 1].HP = hp1;
    }
    
    //Setting the name of a player's weapon
    strcpy(game->allPlayers[number - 1].weapon, weapon1);

    //In case of dmg being negative or too big we set the dmg manually
    if(dmg < 0)
    {
        game->allPlayers[number - 1].wepDmg = 0;
    }
    else if (dmg > 200) // So that dmg wont get bugger than size of int
    {
    game->allPlayers[number - 1].wepDmg = 200;
    }
    {
    game->allPlayers[number - 1].wepDmg = dmg;
    }
    

    //All players start with 0 exp
    game->allPlayers[number - 1].Exp = 0;

    
    
    

}
//Attack method
void attack(Game* game, char* player, char* enemy) 
{
    
    /* The idea is that we check players' names
     * If names do match then and only then we make players figth
     */

    /* Although using two loops for that task is not very efficient
     * It should be fine for this mini project
     */
        for (unsigned int i = 0; i < game->numberOfPlayers; i++)
        { 
            for (unsigned int j = 0; j < game->numberOfPlayers; j++)
            { 
                //Comparing 
                //Players can hit themself
                if (!strcmp(game->allPlayers[i].name, player) && !strcmp(game->allPlayers[j].name, enemy))
                {
                    //Check that both players are alive
                    if (game->allPlayers[i].HP > 0 && game->allPlayers[j].HP > 0)
                    {
                        //Attacking has a chance to miss
                        printf("%s hit %s!\n", game->allPlayers[j].name, game->allPlayers[i].name);
                        int hitprob = 50; // probability is se to 50%

                        if (rand() % 100 < hitprob) {
                            printf("Hit! ");
                            int dam = game->allPlayers[j].wepDmg; //dmg that the first player will get
                            printf("Damage: %d \n", dam);
                            printf("------------\n");
                            game->allPlayers[i].HP = game->allPlayers[i].HP - dam;
                            game->allPlayers[j].Exp = game->allPlayers[j].Exp + 1;

                            //If hp is zero or below we set hp to 0 and "make" player dead
                            if (game->allPlayers[i].HP <= 0)
                            {
                                printf("%s died!", game->allPlayers[i].name);
                                printf("\n");
                                printf("------------\n");
                                game->allPlayers[i].HP = 0;
                            }
                        }
                        else //Missing attack
                        {
                            printf("Miss!\n");
                            printf("------------\n");
                        }

                        //While attacking method is called, both players get hit so this is just a lazy way of doing that
                        //Same attacking pattern as above
                        printf("%s hit %s!\n", game->allPlayers[i].name, game->allPlayers[j].name);
                        if (rand() % 100 < hitprob) {
                            printf("Hit! ");
                            int dam = game->allPlayers[i].wepDmg;
                            printf("Damage: %d \n", dam);
                            printf("------------\n");
                            game->allPlayers[j].HP = game->allPlayers[j].HP - dam;
                            game->allPlayers[i].Exp = game->allPlayers[i].Exp + 1;
                            if (game->allPlayers[j].HP <= 0)
                            {
                                printf("%s died!", game->allPlayers[j].name);
                                printf("\n");
                                printf("------------\n");
                                game->allPlayers[j].HP = 0;
                            }
                        }
                        else
                        {
                            printf("Miss!\n");
                            printf("------------\n");
                        }
                    }
                    // In case of one player being dead
                    else if (game->allPlayers[i].HP == 0 && game->allPlayers[j].HP > 0)
                    {
                        printf("%s is alredy dead!\n", game->allPlayers[i].name);
                        printf("------------\n");
                    }
                    // For other cases, mainly for both players being dead or in case of target being dead
                    else
                    {
                        printf("Target is dead\n");
                        printf("------------\n");

                    }
                }
                
                
            }
        }
    }

//Sorting players by exp. "Swaping"
void sortPlayers(Game* game)
{
    //temps is a temporary "player"  
    Player temp;
    unsigned j, index;
    for (unsigned int i = 0; i < game->numberOfPlayers; i++)
    {
        
        index = i;
        for (j = i + 1; j < game->numberOfPlayers; j++)
        {
            if (game->allPlayers[index].Exp < game->allPlayers[j].Exp)
            {
                
                index = j;
                temp = game->allPlayers[i];
                game->allPlayers[i] = game->allPlayers[index];
                game->allPlayers[index] = temp;
            }
        }
    }
    
}

//Print method
void printPlayers(Game* game) 
{   
    //Sorting players
    sortPlayers(game);
    //Printing only players that are alive
    for (unsigned int i = 0; i < game->numberOfPlayers; i++)
    {
        if (game->allPlayers[i].HP > 0)
        {
            printf("NAME: %s, ", game->allPlayers[i].name);
            printf("HP: %d, ", game->allPlayers[i].HP);
            printf("WEAPON: %s, ", game->allPlayers[i].weapon);
            printf("DMG: %d, ", game->allPlayers[i].wepDmg);
            printf("Exp: %d", game->allPlayers[i].Exp);
            printf("\n");
        }
    }
    //printing dead players
    for (unsigned int i = 0; i < game->numberOfPlayers; i++)
    {
        if (game->allPlayers[i].HP <= 0)
        {
            printf("NAME: %s, ", game->allPlayers[i].name);
            printf("HP: %d, ", game->allPlayers[i].HP);
            printf("WEAPON: %s, ", game->allPlayers[i].weapon);
            printf("DMG: %d, ", game->allPlayers[i].wepDmg);
            printf("Exp: %d", game->allPlayers[i].Exp);
            printf("\n");
        }
    }

}
//Writing method
int writeString(Game* game, char* name)
{
    FILE* f = fopen(name, "w");
    if (!f) 
    {
        fprintf(stderr, "Opening file failed\n");
        return -1;
        //exit(EXIT_FAILURE);  // ends program immediately (in stdlib)
    }
    
    for (int i = 0; i < game->numberOfPlayers; i++)
    {
        
        fprintf(f, "%s", game->allPlayers[i].name);
        fprintf(f, " ");
        fprintf(f, "%d", game->allPlayers[i].HP);
        fprintf(f, " ");
        fprintf(f, "%s", game->allPlayers[i].weapon);
        fprintf(f, " ");
        fprintf(f, "%d", game->allPlayers[i].wepDmg);
        fprintf(f, " ");
        fprintf(f, "%d", game->allPlayers[i].Exp);
        fprintf(f, "\n");
        
        //fwrite(&(game->allPlayers[i]), sizeof(game->allPlayers[i]), 1, f);
    }

    //if (fwrite != 0)
        printf("contents to file written successfully !\n");
    //else
        //printf("error writing file !\n");
    fclose(f);
    return 0;
}

Game readString(char* nm)
{
    FILE* name;
    //Game newPlayer;
    
    Game newGame; // = calloc(100, sizeof(Game));
    memset(&newGame, 0, sizeof(Game));
    Game newGame2 = newGame;
    
    int i = 0;

    name = fopen(nm, "r");
    if (name == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return newGame;
    }
    fseek(name, 0, SEEK_END); // seek to end of file
    int size = ftell(name); // ask for size of file
    fseek(name, 0, SEEK_SET); // seek back to beginning of file
    
    if (size == 0) return newGame;


    
    
    //memset(newGame2, 0, sizeof(newGame2));
    newGame2.numberOfPlayers= 0;
    
   

    while (feof(name) == 0)
    {
        
        unsigned int number = newGame2.numberOfPlayers + 1;
        newGame2.numberOfPlayers = number;
   
        newGame2.allPlayers = realloc(newGame2.allPlayers, (number + 1) * sizeof(Player));

        int k = fscanf(name, "%s %d %s %d %d", newGame2.allPlayers[i].name, &(newGame2.allPlayers[i].HP), newGame2.allPlayers[i].weapon, &(newGame2.allPlayers[i].wepDmg), &(newGame2.allPlayers[i].Exp));
        
        if (k == EOF)
        {
            break;
        }

        //fread(&Game[i], sizeof(struct Student), 1, name);
        i++;
        
    }
    
    newGame2.allPlayers = realloc(newGame2.allPlayers, (newGame2.numberOfPlayers - 1) * sizeof(Player));
    newGame2.numberOfPlayers = newGame2.numberOfPlayers - 1;
    printf("Done reading.\n");
    fclose(name);
    //free(newGame2);
    return newGame2;
}


//Helper method that free memory
void freeAll(Game* game) {
    if (game->allPlayers) {
        free(game->allPlayers);
    }
}

//main function
int main()
{
    //Creating 
    Game peli;

    //Setting 
    memset(&peli, 0, sizeof(peli));
    peli.numberOfPlayers = 0;

    //Allocating parameter that will be used in sscanf
    char* name1 = malloc(80);
    char* name2 = malloc(80);
    int hp1 = 0;
    int dmg2 = 0;
    char* str = calloc(80, sizeof(char));
    

    //Stop at quit
    while (1)
    {
        fgets(str, 80, stdin); //Getting the input

        if (ferror(stdin))
        {
            free(name1);
            free(name2);
            free(str);
            freeAll(&peli);
            printf("Error. Quitting..");
            return -1;
        }
        else if (feof(stdin))
        {
            
            printf("EOF");
            break;
            /* EOF */
        }

       if (str[0] == 'Q')
        {
            break;
        }

         if (str[0] == 'A') //If A then add
        {
            //If not enough parameters we do not add a player
             if (sscanf(str, "%*c %s %d %s %d", name1, &hp1, name2, &dmg2) == 4) {

                 if (strlen(name1) > 30 || strlen(name2) > 30) // if names are too long 
                 {
                     printf("Names are too long. Quitting..");
                     free(name1);
                     free(name2);
                     free(str);
                     freeAll(&peli);
                     return -1;
                 }

                 addPlayers(&peli, name1, hp1, name2, dmg2);
             }
             else
             {
                 printf("Not enough parameters\n");
                 printf("------------\n");
             }
        }
        else if (str[0] == 'H') //If H then attack
        {
            sscanf(str, "%*c %s %s", name1, name2);

            if (strlen(name1) > 30 || strlen(name2) > 30) // if names are too long
            {
                printf("Names are too long. Quitting..");
                free(name1);
                free(name2);
                free(str);
                freeAll(&peli);
                return -1;
            }

            attack(&peli, name1, name2);
        }
        else if (str[0] == 'L') // Printing
        {
            printPlayers(&peli);
            printf("------------\n");
        }
        else if (str[0] == 'W') // Writing
        {
             if (sscanf(str, "%*c %s", name1) == 1) //Only do if the input is "W txt"
             {
                 writeString(&peli, name1);
                 printf("------------\n");
                 
             }
             
        }
        else if (str[0] == 'O')
        {
             if (sscanf(str, "%*c %s", name1) == 1) //Only do if the input is "W txt"
             {
                 freeAll(&peli);
                 peli = readString(name1);
                 printf("------------\n");
                 
             }
             else
             {
                 free(name1);
                 free(name2);
                 free(str);
                 freeAll(&peli);
                 return -1;
             }
        }
        else // Any other command
        {
            printf("Wrong command.\n");
            printf("------------\n");
        }
    }
    // To free allocated memory
    free(name1);
    free(name2);
    free(str);
    freeAll(&peli);
    printf("End.");
}

