/************************************************************************/
/* 
File name: Blackjack.cpp
Description: This cpp is simple poker game -- 21point.
Author: sjtu-XutongLu
Date: 2015-4-1  

Additional explain: To avoid the imprecise double type's calculation,
	I make it to 42 point game but it was concealed from the player.
*/
/************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int Deal(bool card[][13], int Array[]);
/*  This function simulates a licensing procedure.
It receives a bool type array(means whether the poker was used already) 
and a int type array(means the poker computer/player has got)
It returns a card point and memories the card computer/player has got. */

void PrintCard(int Array[]);
/*  This function print the card computer/player has got.
It receives a int type array(means the poker computer/player has got) */

void Reset(bool card[][13], int user_card[], int computer_card[]);
/*  This function simulates shuffling poker.
It receives a bool type array(means whether the poker was used already) 
and two int type arrays(means the poker computer and player has got),
then it reset them. */

char CheckInput();
/*  This function is to do error detection.
It got user input and give warning message 
till it returns the right input.*/

int main(){
	srand((unsigned)time(NULL));
	const int MAX_POINT = 42;
	bool card[4][13] = {0};
	int user_card[21] = {0};
	int computer_card[21] = {0};
	int user_point = 0, computer_point = 0, computer_card_number = 0, user_card_number = 0;
	char check_card(0), check_game(0);

	do {
		// shuffle poker
		Reset(card, user_card, computer_card);
		user_point = 0, computer_point = 0,check_card = 0,check_game = 0;

		// get two cards
		cout<<"Player \nCard for player\n";
		user_point += Deal(card,user_card);
		user_point += Deal(card,user_card);
		cout<<"Player get card:  ";
		PrintCard(user_card);

		// ask player whether needs more card and check if player loses.
		cout<<"\nNeed one more card?(y/n): ";
		check_card = CheckInput();
		while(check_card == 'y' || check_card == 'Y'){
			user_point += Deal(card,user_card);
			cout<<"\nOne more card:  ";
			PrintCard(user_card);

			if(user_point > MAX_POINT) {
				cout<<"\nYou lose";
				cout<<"\nPlay again?";
				check_game = CheckInput();
				break;
			}
			cout<<"\nNeed one more card?(y/n):  ";
			check_card = CheckInput();
		}
		if(check_game == 'y' || check_game == 'Y') continue;
		if(check_game == 'n' || check_game == 'N') break;

		// computer's poker time 
		cout<<"Computer \nCard for computer\n";
		computer_point += Deal(card,computer_card);
		computer_point += Deal(card,computer_card);
		cout<<"Computer get card:  ";
		PrintCard(computer_card);
		while(computer_point <= user_point){
			computer_point += Deal(card,computer_card);
			cout<<"\nOne more card:  ";
			PrintCard(computer_card);

			//check if computer lose or win
			if(computer_point > MAX_POINT) {
				cout<<"\nYou win";
				cout<<"\nPlay again?";
				check_game = CheckInput();
				break;
			}
			if(computer_point == user_point){
				for(int i = 0; user_card[i] != 0; ++i){computer_card_number += 1;}
				for(int i = 0; computer_card[i] != 0; ++i){computer_card_number += 1;}
				if(computer_card_number == user_card_number){
					cout<<"Draw";
					cout<<"\nPlay again?";
					check_game = CheckInput();
					break;
				}
				else{
					if(computer_card_number>user_card_number) cout<<"\nYou lose";
					else cout<<"\nYou win";
					cout<<"\nPlay again?";
					check_game = CheckInput();
					break;
				}
			}
			if(computer_point > user_point){
				cout<<"\n You lose";
				cout<<"\nPlay again?";
				check_game = CheckInput();
				break;
			}
		}
		if(check_game == 'y' || check_game == 'Y') continue;
		if(check_game == 'n' || check_game == 'N') break;
	} while (check_game == 'y' || check_game == 'Y');

	system("pause");
	return 0;
}

int Deal(bool card[][13], int Array[]){
	int card_color = 0, card_point = 0;
	int point = 0;
	do {
		card_color = rand()%4;
		card_point = rand()%13;
	} while (card[card_color][card_point]);
	card[card_color][card_point] = 1;

	for(int i = 0; i < 21; ++i){
		if(Array[i]==0){
			Array[i] = (card_point+1)*10 + (card_color+1);
			break;
		}
	}
	if(card_point>=10){point = 1;}
	else point = 2*(card_point+1);

	return point;
}

void PrintCard(int Array[]){
	for(int i = 0; Array[i]!=0; ++i){
		switch(Array[i]%10){
			case 1:cout<<"spade ";break;
			case 2:cout<<"club ";break;
			case 3:cout<<"heart ";break;
			case 4:cout<<"diamond ";break;
		}
		switch(Array[i]/10){
			case 1:cout<<'A'<<' ';break;
			case 11:cout<<'J'<<' ';break;
			case 12:cout<<'Q'<<' ';break;
			case 13:cout<<'K'<<' ';break;
			default:cout<<Array[i]/10<<' ';break;
		}
	}
}

void Reset(bool card[][13], int user_card[], int computer_card[]){
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 13; ++j){
			card[i][j] = 0;
		}
	}
	for(int i = 0; i < 21; ++i){
		user_card[i] = 0;
		computer_card[i] = 0;
	}
}

char CheckInput(){
	string str;
	char ch;
	do {
		try{
			cin>>str;
			cin.sync();
			if(str != "y"&&str!="Y"&&str!="n"&&str!="N"){
				throw 1;
			}
		}
		catch(int){
			cout<<"Please enter again!('n'/'N'/'y'/'Y'): ";
			continue;
		}
		break;
	} while (true);
	ch = str[0];
	return ch;
}