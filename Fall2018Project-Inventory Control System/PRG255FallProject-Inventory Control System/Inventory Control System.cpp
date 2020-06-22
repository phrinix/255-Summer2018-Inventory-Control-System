#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>


typedef struct {
	char name[20];
	double cost ;
	int quanity ;
	double itemProfit ;
	double totalProfit ;
} control ;

void caseA();
void caseB();
void caseC();
void caseD();
void caseE();

int main ()
{
	control inventory;
	char index ;
	do{

	printf("\na) Show the names and number of each item in stock including the cost of\n   each item and total value of each item in stock.\n");
	printf("b) Show the number of units sold each time, the profit for each item in stock\n   and the total store profit\n");
	printf("c) Allow the owner to order more of existing items\n");
	printf("d) Allow the owner to order new items\n");
	printf("e) Allow the owner to enter the sale of items\n");
	printf("f) Quit\n");
	printf("To chose a function,enter its letter label;\n");
	scanf(" %c",&index);
	switch (index) {
	case 'a':
		printf("Item Number\t Item Name\t Number\t Unit Cost\t Value\n");
		caseA();
		break;
	case 'b':
		printf("Item Number\t Item Name\t Number Sold\t Item Profit\n");
		caseB();
		break;
	case 'c':
		caseC();
		break;
	case 'd':
		caseD();
		break;
	case 'e':
		caseE();
		break;
	case 'f':
		printf("\nThanks");
		break;
	default:
		printf("\nERROR---Enter again\n");
		break;
	};
	} while (index != 'f');
	getch();
	return (0);
}
void caseA(){
	FILE *fileP = fopen("data.txt","r+b");
	control updates;
	int index = 0 ;
	double value ;

	while(fread(&updates,sizeof(updates),1,fileP) == 1)
	{
		value = updates.quanity * updates.cost ;
		printf("%d\t\t %s\t %d\t $%.2lf\t $%.2lf\n\n",(index+1),updates.name,updates.quanity,updates.cost,value);
		index ++ ;
	}
	fclose(fileP);
}
void caseB(){
	FILE *fileP = fopen("data.txt","r+b");
	control updates;
	int index = 0 ;
	double number ;

	while(fread(&updates,sizeof(updates),1,fileP) == 1)
	{
		number = updates.itemProfit / (updates.cost/2) ;
		printf("%d\t\t %s\t\t $%.0lf\t $%.2lf\n\n",(index+1),updates.name,number,updates.itemProfit);
		index ++ ;
	}
	fclose(fileP);
}
void caseC(){
	FILE *fileP = fopen("data.txt","r+b");
	control updates;
	int index ;
	char name[20];

	updates.totalProfit = 0;

	printf("\nEnter part name : ");
	scanf("%s",name);
	fseek(fileP, 0,SEEK_SET);
	while ((index = fread(&updates, sizeof(control),1,fileP)) == 1) {
		if (strcmp(name,updates.name) == 0) break ;
	} 

	printf("Enter the quantity = ");
	scanf("%d",&index);
	updates.quanity = updates.quanity + index ;

	fseek(fileP,-(long)sizeof(control),SEEK_CUR);
	fwrite(&updates, sizeof(control),1,fileP);

	fclose(fileP);
}
void caseD(){
	FILE *fileP = fopen("data.txt","a+b");
	control updates;

	char ch[2];
	do {
		printf("\nEnter the name of Item :");
		gets(updates.name);
		gets(updates.name);
		printf("Enter the unit cost : $ ");
		scanf("%lf",&updates.cost);
		printf("Enter the quantity :");
		scanf("%d",&updates.quanity);
		updates.itemProfit = 0 ;
		fseek(fileP, 0, SEEK_END);
		fwrite(&updates,sizeof(updates),1,fileP);
		printf("Add more parts (y/n)? => ");
	}while (getche() == 'y');
	fclose(fileP);
}
void caseE(){
	FILE *fileP = fopen("data.txt","r+b");
	control updates;
	int index ;
	char name[20];

	updates.totalProfit = 0;

	printf("\nEnter part name : ");
	scanf("%s",name);
	fseek(fileP, 0,SEEK_SET);
	while ((index = fread(&updates, sizeof(control),1,fileP)) == 1) {
		if (strcmp(name, updates.name) == 0) break ;
	} 

	printf("Enter number of Item sold = ");
	scanf("%d",&index);
	updates.itemProfit = index * (updates.cost / 2);
	updates.totalProfit += updates.itemProfit ;
	updates.quanity = updates.quanity - index ;
	fseek(fileP,-(long)sizeof(control),SEEK_CUR);
	fwrite(&updates, sizeof(control),1,fileP);

	fclose(fileP);
}