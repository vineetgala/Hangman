#pragma large
#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions
sbit LED=P1^7;

//Main function
void main(void)
{
	//ch - receives character from PC via UART
	//i,j - loop variables/counters
	//score - counts number of correct guesses for a word
	//mistakes - counts number of incorrect letters entered so far
	//found - used as a flag to show if a letter has been found in the word
	//words[][] - used to store list of words
	//len[] - used to store the length of each word (4/5/6)
	//letters - used to check if a letter has already been input previously
	//If a user inputs the same letter again  for a word, my code ignores it - correct or incorrect
	unsigned char ch=0,i,j,score=6,mistakes=0,found=0;
	code unsigned char words[][6]={"mini",
	"micro",
	"micron",
	"root",
	"pizza",
	"hostel",
	"heat",
	"short",
	"ground",
	"test",
	"house",
	"county",
	"shoe",
	"socks",
	"drinks",
	"food",
	"water",
	"orange",
	"drop",
	"hairy",
	"singer",
	"film",
	"sound",
	"double",
	"wall",
	"steel",
	"travel",
	"bank",
	"fixed",
	"prince",
	"king",
	"queen",
	"bishop",
	"pawn",
	"chess",
	"knight",
	"rook",
	"check",
	"winner",
	"bike",
	"cycle",
	"runner",
	"swim",
	"plant",
	"fruits",
	"root",
	"light",
	"mirror",
	"pick",
	"proof",
	"bottle",
	"ship",
	"fight",
	"battle",
	"fort",
	"mount",
	"braces",
	"spot",
	"board",
	"sports",
	"real",
	"truth",
	"really",
	"open",
	"close",
	"outlet",
	"shop",
	"flyer",
	"window",
	"safe",
	"email",
	"search",
	"here",
	"flash",
	"string",
	"tool",
	"debug",
	"ignore",
	"warn",
	"build",
	"serial",
	"true",
	"catch",
	"target",
	"hang",
	"hello",
	"wonder",
	"year",
	"right",
	"tactic",
	"turn",
	"false",
	"coding",
	"game",
	"group",
	"source",
	"help",
	"start",
	"object",
	"real"};
	unsigned char len[100];
	unsigned char letters[26];
	//Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	for(i=0;i<100;i++)
		len[i]=4+(i%3);
	//Call initialization functions
	lcd_init();
	uart_init();
	for(j=0;j<100;j++)
	{
		for(i=0;i<26;i++)
			letters[i]=0;
		lcd_cmd(0x01);
		lcd_cmd(0x85);
		for(i=0;i<len[j];i++)
			lcd_write_char('_');
		lcd_cmd(0x0C1);
		lcd_write_string("Incorrect = 0");
		score = len[j];
		mistakes = 0;
	while((mistakes<6)&(score>0))
	{
			//Receive a character
			ch = receive_char();
			found=0;
			if(letters[(ch-'a')]==0)
			{
				letters[(ch-'a')]=1;
				for(i=0;i<6;i++)
				{
					if(words[j][i]==ch)
					{
						found=1;
						lcd_cmd(0x85+i);
						lcd_write_char(ch);
						score--;
					}
				}
				if(found==0)
					mistakes++;
			}	
			lcd_cmd(0x0CD);
			lcd_write_char(mistakes+48);
	}
	msdelay(500);
	lcd_cmd(0x01);
	lcd_cmd(0x84);
	if(score==0)
		lcd_write_string("You Win!");
	else
		lcd_write_string("You Lose");
	msdelay(2000);
	}
}
