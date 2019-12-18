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
 int* buffer ; 
 int /*<<< orphan*/  clreol () ; 
 int /*<<< orphan*/  clrscr () ; 
 int /*<<< orphan*/  cputs (char*) ; 
 int /*<<< orphan*/  gotoxy (int,int) ; 
 int hi ; 
 scalar_t__ kbhit () ; 
 int /*<<< orphan*/  key_done () ; 
 int /*<<< orphan*/  key_init () ; 
 char** keynames ; 
 int lo ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

int choosekey(char *title,int oldval)
{
  char msg[80];
  int lastkey;
  int newval;
  int bad;

  clrscr();
  sprintf(msg,"Press key for %s",title);
  gotoxy((78-strlen(msg))/2,8);
  cputs(msg);
  gotoxy(34,9);
  cputs("(ESC=none)");
  sprintf(msg,"Current setting: %s",keynames[oldval]);
  gotoxy((78-strlen(msg))/2,11);
  cputs(msg);
  while (kbhit());
  key_init();

  do{
    while (hi==lo);
    lastkey=buffer[lo++];
    if (lo==100) lo=0;
    /*do not allow F1-F12, Pause, PrintScreen or Scrollock */
    bad=(lastkey>=59 && lastkey<=68) || lastkey==87 || lastkey==88 || lastkey==167
        || lastkey==183 || lastkey==70 || lastkey==197;
  }while ((lastkey&0xff00) || *keynames[lastkey&0xff]=='?' || *keynames[lastkey&0xff]=='#' || bad);
  newval=lastkey&0xff;
  if (newval==1) newval=255;
  sprintf(msg,"Current setting: %s",keynames[newval]);
  gotoxy(1,11);
  clreol();
  gotoxy((78-strlen(msg))/2,11);
  cputs(msg);
  /*wait until key is depressed*/
  do{
    while (hi==lo);
    lastkey=buffer[lo++];
    if (lo==100) lo=0;
  }while(!(lastkey&0xff00));
  key_done();
  return newval;
}