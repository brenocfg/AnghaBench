#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  SIFC_4PLAYER 138 
#define  SIFC_ARKANOID 137 
#define  SIFC_FKB 136 
#define  SIFC_FTRAINERA 135 
#define  SIFC_FTRAINERB 134 
#define  SIFC_HYPERSHOT 133 
#define  SIFC_MAHJONG 132 
#define  SIFC_NONE 131 
#define  SIFC_OEKAKIDS 130 
#define  SIFC_QUIZKING 129 
#define  SIFC_SHADOW 128 
 int* UsrInputType ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void FCExp(char *text)
{
        static char *fccortab[11]={"none","arkanoid","shadow","4player","fkb","hypershot",
                        "mahjong","quizking","ftrainera","ftrainerb","oekakids"};
           
        static int fccortabi[11]={SIFC_NONE,SIFC_ARKANOID,SIFC_SHADOW,
                                 SIFC_4PLAYER,SIFC_FKB,SIFC_HYPERSHOT,SIFC_MAHJONG,SIFC_QUIZKING,
                                 SIFC_FTRAINERA,SIFC_FTRAINERB,SIFC_OEKAKIDS};
	int y;
	for(y=0;y<11;y++)
	 if(!strcmp(fccortab[y],text))
	  UsrInputType[2]=fccortabi[y];
}