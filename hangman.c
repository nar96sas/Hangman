#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char word[20]; // Mảng lưu chữ trong file word.txt
int flip[20]; // từ nào đã đoán đúng
char miss[20]; // Mảng lưu chữ đoán sai
///////////////////////////////////////////////////////////////////////////////
void menu()
{
    int i;
    printf("\n\n\n");
    printf("   00    00     000     000   00  000000   000      000    000    000   00 \n");
    printf("   00    00    00 00    0000  00 00        0000    0000   00 00   0000  00 \n");
    printf("   00000000   00   00   00 00 00 00   0000 00 00  00 00  00   00  00 00 00 \n");
    printf("   00    00  000000000  00  0000 00    00  00  0000  00 000000000 00  0000 \n");
    printf("   00    00  00     00  00   000  0000000  00   00   00 00     00 00   000 \n");

    printf("\n \n \t\t\t");
    for(i=0;i<20;i++)
        printf("*");
    printf("\n");
    printf("\t\t\t*                  * \n");
    printf("\t\t\t*    1.1 PLAYER    * \n");
    printf("\t\t\t*    2.2 PLAYER    * \n");
    printf("\t\t\t*    3.QUIT        * \n");
    printf("\t\t\t*                  * \n");
    printf("\t\t\t");
    for(i=0;i<20;i++)
        printf("*");
    printf("\n");
    printf("\t\t\tSelect : ");
}
//////////////////////////Tính số hàng trong file để random/////////////////////////////////////////
int count_ligne(char a[],char *word_guess)
{
    int l=0;
    FILE *fword = fopen("word.txt","r");
    // Tính số hàng trong file
    while (fgets(a,2,fword))
    {
        word_guess = a;
        if (*word_guess == '\n')
            l++;
    }
    fclose(fword);
    return l;
}
//////////////////////////////Lấy từ vừa random và khởi tạo hai mảng flip,word///////////////////////////////////////
int get_word_guess(char a[],char *word_guess,int ligne_random,char word[],int l_word)
{
    int ligne = 0,i=0;
    l_word = 0;
    FILE *fword = fopen("word.txt","r");

    while (fgets(a,2,fword))
    {
        word_guess = a;
        // Xong một dòng
        if (*word_guess == '\n')
        {
            ligne++;
            continue;
        }
        // Lấy từ tại dòng đã random
        if (ligne == ligne_random)
        {
            word[i] = *word_guess;
            flip[i] = 0; //Khởi tạo mảng tữ đã đoán đúng
            l_word++;
            i++;
        }
    }

    fclose(fword);
    return l_word;
}
///////////////////////////In từ để đoán//////////////////////////////////////////
void print_guess(int l_word)
{
    int i;
    for (i=0;i<l_word;i++)
        if (flip[i] == 0)
            printf("_ ");
        else printf("%c ",word[i]);
}
///////////////////////////Kiểm tra từ vừa đoán/////////////////////////////////////
int check_lettre(int l_word,char res)
{
    int i;
    int egal = 0;
    for(i=0;i<l_word;i++)
        if (res == word[i] && flip[i] == 0) //Tu` da~ doan' r cung~ tinh' sai
        {
            flip[i] = 1;
            egal = 1;
        }
        else if (res == word[i] && flip[i] == 1)
        	egal = 2;
    return egal;
}
//////////////////////////////In khung////////////////////////////////////
void print_prison()
{
    int i,j;
    for(i=0;i<12;i++)
    {
        printf("\t");
        for(j=0;j<25;j++)
            if (i==0 || j==0 || j==24)
                printf("*");
            else printf(" ");
        if (i != 11) printf("\n");
    }
}
//////////////////////////Vẽ hangman//////////////////////////////////////
void print_gallows(int end)
{
    int i;
    if (end == 0)
        print_prison();

    if (end >= 1)
    {
        printf("\t");
        for(i=0;i<25;i++) printf("*"); printf("\n");
        printf("\t*\t   ---  \t*\n");
        printf("\t*\t  |o o| \t*\n");
        printf("\t*\t  | ^ | \t*\n");
        printf("\t*\t   ---  \t*");
        if (end == 1)
            for(i=0;i<7;i++)
                printf(" \n\t*\t        \t*");
    }
    if (end == 2)
    {
        printf("\n\t*\t    |   \t*\n");
        printf("\t*\t    |   \t*\n");
        printf("\t*\t    |   \t*\n");
        printf("\t*\t    |   \t*");
        for(i=0;i<3;i++)
            printf(" \n\t*\t        \t*");
    }
    if (end == 3)
    {
        printf("\n\t*\t   _|   \t*\n");
        printf("\t*\t  | |   \t*\n");
        printf("\t*\t |  |   \t*\n");
        printf("\t*\t    |   \t*");
        for(i=0;i<3;i++)
            printf(" \n\t*\t        \t*");
    }
    if (end >= 4)
    {
        if (end == 7)
        {
            printf("\n\t");
            for (i=0;i<25;i++)
            {
                printf("=");
            }
            printf("\n");
        }
        else
            printf("\n\t*\t   _|_   \t*\n");
        printf("\t*\t  | | |  \t*\n");
        printf("\t*\t |  |  | \t*\n");
        printf("\t*\t    |    \t*");
        if (end == 4)
            for(i=0;i<3;i++)
                printf(" \n\t*\t        \t*");
    }
    if (end == 5)
    {
        printf("\n\t*\t   |    \t*\n");
        printf("\t*\t  |     \t*\n");
        printf("\t*\t |      \t*");
    }
    if (end >= 6)
    {
        printf("\n\t*\t   | |  \t*\n");
        printf("\t*\t  |   | \t*\n");
        printf("\t*\t |     |\t*");
    }

    printf("\n\t");
    for(i=0;i<25;i++) printf("*"); printf("\n");
}
/////////////////////////Kiểm tra đã hết game chưa////////////////////////////////////////
int check_correct(int l_word)
{
    int i;
    for (i=0;i<l_word;i++)
        if (flip[i] == 0)
            return 0;
    return 1;
}
///////////////////////////////In từ đoán sai//////////////////////////////
void print_misses(int i)
{
    int j;
    for (j=0;j<i;j++)
        printf("%c ",miss[j]);
}
//////////////////////////////Hiện kết quả/////////////////////////////////
void solution(int l_word)
{
    int i;
    for (i=0;i<l_word;i++)
        flip[i] = 1;
    printf("\t\tThe correct word is:\n\n");
    printf("\t\t>>>>>> "); print_guess(l_word); printf("<<<<<<");
    printf("\n");
}
/////////////////////////////Menu chọn////////////////////////////////
void menu_play()
{
    printf("\n___________________________");
    printf("\n\n\t1.Guess");
    printf("\n\t2.Solution = Surrender");
    printf("\n\t3.New");
    printf("\n\t4.Menu");
    printf("\n\tSelect: ");
}
//////////////////////////Vòng lặp chính của trò chơi///////////////////////////////////
int play_loop(int player)
{
    char a[100],*word_guess,res;
    int ligne, ligne_random, l_word=0, end=0,select,i=0;
    if (player == 1) // 1 player
    {
        ligne = count_ligne(a,word_guess);
        srand(time(NULL));
        ligne_random = rand()%ligne+0;  //Chọn 1 hàng ngẫu nhiên trong file
        l_word = get_word_guess(a,word_guess,ligne_random,word,l_word);
    }
    else // 2 player
    {
        system("cls");
        do {
            printf("\n\n\n\t\tPlayer1 enter a word ! (more than 2 letters) : \n");
            printf("\t\t");scanf("%s",&a);

            for (i=0;a[i]!= '\0' ; i++)
                l_word++;
            if (l_word < 2) printf("\n\t\tWrong type ! Enter again");
        } while (l_word < 2);
        for (i=0;a[i]!= '\0' ; i++)
        {
            word[i] = a[i];
            flip[i] = 0;
        }
    }
    do
    {
        system("cls");
        print_gallows(end);
        printf("\n\t");print_guess(l_word);
        printf("\n\n\tMisses: "); print_misses(i);
        if (check_correct(l_word) == 1) break; //Kết thúc game
        if (end < 7)
        {
            menu_play();
            scanf("%d",&select);
            switch(select)
            {
                case 1:
                    printf("\n\n\tGuess a letter! : ");
                    scanf("%s",&res);
                    if(check_lettre(l_word,res) == 0)
                    {
                        end++;
                        miss[i] = res;
                        i++;
                    }
                    else if (check_lettre(l_word,res) == 2)
                    	end++;
                    break;
                case 2:
                    end = 7;
                    break;
                case 3:
                    play_loop(player);
                    return 0;
                    break;
                case 4:
                    return 0;
            }
        }
        else break;
    } while(end < 8);
    // Hiện kết quả
    system("cls");
    print_gallows(end);
    if (check_correct(l_word)==1)
    {
        printf("\n\n\n\t\tYou WIN ! \n");
        solution(l_word);
    }
    else
    {
        printf("\n\n\n\t\tYou LOSE ! \n");
        solution(l_word);
    }
    printf("\n\t\t1.New \t2.Quit \t3.Menu\n");
    printf("\t\tSelect : ");
    scanf("%d",&select);
    switch(select)
    {
        case 1:
            play_loop(player);
            return 0;
            break;
        case 2:
            break;
        case 3:
            return 0;
    }
    return 1;
}
///////////////////////////////////////////////////////////////////
int main()
{
    int select,exit=0;

    do
    {
        system("cls");
        menu();
        scanf("%d",&select);
        switch(select)
        {
            case 1:
                exit = play_loop(1);
                break;
            case 2:
                exit = play_loop(2);
                break;
            case 3:
                return 0;
        }
    }while(exit == 0);
    return 0;
}
