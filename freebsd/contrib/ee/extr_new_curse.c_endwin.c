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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  curscr ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  virtual_scr ; 

void 
endwin()		/* end windows					*/
{
	keypad(stdscr, FALSE);
	initialized = FALSE;
	delwin(curscr);
	delwin(virtual_scr);
	delwin(stdscr);
#ifndef SYS5
{
	int old_arg, value;
/*	old_arg = fcntl(0, F_GETFL, 0);
	value = fcntl(0, F_SETFL, old_arg & ~FNDELAY);*/
}
#endif
}