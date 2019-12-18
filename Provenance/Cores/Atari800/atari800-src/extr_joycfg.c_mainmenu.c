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
 int /*<<< orphan*/  BACKGROUND ; 
 size_t JOYSTICKTYPES ; 
 int SelectItem (char*,int*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 char** joysticks ; 
 size_t* joytypes ; 
 int /*<<< orphan*/  setupkeyset (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  testcollisions () ; 

int mainmenu(void)
{
  char joytext[4][80];
  int i,select,key;

  select=0;
  do{
    for (i=0;i<4;i++)
      sprintf(joytext[i],"Joystick %i: %s",i,joysticks[joytypes[i]]);

    key=SelectItem("Select function",&select,BACKGROUND,joytext[0],joytext[1],
               joytext[2],joytext[3],"-",
               "Configure keyset 0","Configure keyset 1",
               "Configure keyset 2","Configure keyset 3","-","Test keyboard collisions",
                "-","Save and exit","Exit without saving",NULL);
    switch(key)
    {
      case 0x14d: /*right*/
        if (select<4)
        {
          joytypes[select]++;
          if (joytypes[select]==JOYSTICKTYPES) joytypes[select]=0;
        }
        break;
      case 0x14b: /*left*/
        if (select<4)
        {
          joytypes[select]--;
          if (joytypes[select]==-1) joytypes[select]=JOYSTICKTYPES-1;
        }
        break;
      case 13: /*enter*/
        if (select<4)
        {
          joytypes[select]++;
          if (joytypes[select]==JOYSTICKTYPES) joytypes[select]=0;
        }else
        if (select<9)
        {
          setupkeyset(select-5);
        }else
        if (select==10)
        {
          testcollisions();
        }
        break;
    }
  }while(key!=27 && !(key==13 && select>=12));
  return (key==13 && select==12); /*Save only when user pressed ENTER on 'Save&Exit' */
}