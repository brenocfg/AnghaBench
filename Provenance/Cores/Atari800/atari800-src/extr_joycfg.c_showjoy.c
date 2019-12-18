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
 scalar_t__ BACKGROUND ; 
 scalar_t__ MENUHEADER ; 
 scalar_t__ MENUITEM ; 
 int /*<<< orphan*/  cprintf (char*,int) ; 
 int /*<<< orphan*/  cputs (char*) ; 
 int /*<<< orphan*/  gotoxy (int,int) ; 
 size_t** keysets ; 
 scalar_t__* pressed ; 
 int /*<<< orphan*/  putch (char) ; 
 int /*<<< orphan*/  textattr (scalar_t__) ; 

void showjoy(int x,int y,int num)
{
  textattr(BACKGROUND+MENUITEM);
  gotoxy(x,y);
  cprintf("Keyset %i",num);
  gotoxy(x+1,y+2);
  cputs("\\ | /");
  gotoxy(x+1,y+3);
  cputs("-   -");
  gotoxy(x+1,y+4);
  cputs("/ | \\");
  textattr(BACKGROUND+MENUHEADER);
  gotoxy(x+3,y+3);putch(pressed[keysets[num][0]]?'@':' ');
  gotoxy(x,y+5);putch(pressed[keysets[num][1]]?'@':' ');
  gotoxy(x+3,y+5);putch(pressed[keysets[num][2]]?'@':' ');
  gotoxy(x+6,y+5);putch(pressed[keysets[num][3]]?'@':' ');
  gotoxy(x,y+3);putch(pressed[keysets[num][4]]?'@':' ');
  gotoxy(x+6,y+3);putch(pressed[keysets[num][5]]?'@':' ');
  gotoxy(x,y+1);putch(pressed[keysets[num][6]]?'@':' ');
  gotoxy(x+3,y+1);putch(pressed[keysets[num][7]]?'@':' ');
  gotoxy(x+6,y+1);putch(pressed[keysets[num][8]]?'@':' ');
}