#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* backtitle; } ;

/* Variables and functions */
 int ERRDISPLAYTOOSMALL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  color_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 TYPE_1__ dlg ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  stdscr ; 

int init_dialog(const char *backtitle)
{
	int height, width;

	initscr();		/* Init curses */
	getmaxyx(stdscr, height, width);
	if (height < 19 || width < 80) {
		endwin();
		return -ERRDISPLAYTOOSMALL;
	}

	dlg.backtitle = backtitle;
	color_setup(getenv("MENUCONFIG_COLOR"));

	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	dialog_clear();

	return 0;
}