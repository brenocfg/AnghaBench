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
 int /*<<< orphan*/  Screen (char*,scalar_t__) ; 
 scalar_t__ TITLE ; 
 int /*<<< orphan*/  _NOCURSOR ; 
 int /*<<< orphan*/  _NORMALCURSOR ; 
 int /*<<< orphan*/  _set_screen_lines (int) ; 
 int /*<<< orphan*/  _setcursortype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clrscr () ; 
 int mainmenu () ; 
 int /*<<< orphan*/  read_config () ; 
 int /*<<< orphan*/  save_config () ; 
 int /*<<< orphan*/  textattr (int) ; 
 int /*<<< orphan*/  window (int,int,int,int) ; 

int main()
{
  int ok;

  read_config();
  _set_screen_lines(25);
  _setcursortype(_NOCURSOR);

  Screen("Joystick configuration utility for Atari 800 emulator",BACKGROUND+TITLE);
  ok=mainmenu();

  window(1,1,80,25);
  textattr(0xf);
  clrscr();
  _setcursortype(_NORMALCURSOR);

  if (ok) save_config();

  return 0;
}