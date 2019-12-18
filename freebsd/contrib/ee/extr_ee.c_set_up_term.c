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
 int /*<<< orphan*/  A_NC_BIG5 ; 
 int COLS ; 
 int /*<<< orphan*/  CONTROL_KEYS ; 
 scalar_t__ FALSE ; 
 int LINES ; 
 scalar_t__ TRUE ; 
 void* com_win ; 
 scalar_t__ curses_initialized ; 
 scalar_t__ ee_chinese ; 
 void* help_win ; 
 int /*<<< orphan*/  idlok (void*,scalar_t__) ; 
 int /*<<< orphan*/  info_type ; 
 void* info_win ; 
 scalar_t__ info_window ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (void*,scalar_t__) ; 
 int last_col ; 
 int last_line ; 
 int local_COLS ; 
 int local_LINES ; 
 int /*<<< orphan*/  nc_setattrib (int /*<<< orphan*/ ) ; 
 void* newwin (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  paint_info_win () ; 
 int /*<<< orphan*/  raw () ; 
 int /*<<< orphan*/  savetty () ; 
 void* stdscr ; 
 void* text_win ; 
 int /*<<< orphan*/  werase (void*) ; 
 int /*<<< orphan*/  wrefresh (void*) ; 

void 
set_up_term()		/* set up the terminal for operating with ae	*/
{
	if (!curses_initialized)
	{
		initscr();
		savetty();
		noecho();
		raw();
		nonl();
		curses_initialized = TRUE;
	}

	if (((LINES > 15) && (COLS >= 80)) && info_window)
		last_line = LINES - 8;
	else
	{
		info_window = FALSE;
		last_line = LINES - 2;
	}

	idlok(stdscr, TRUE);
	com_win = newwin(1, COLS, (LINES - 1), 0);
	keypad(com_win, TRUE);
	idlok(com_win, TRUE);
	wrefresh(com_win);
	if (!info_window)
		text_win = newwin((LINES - 1), COLS, 0, 0);
	else
		text_win = newwin((LINES - 7), COLS, 6, 0);
	keypad(text_win, TRUE);
	idlok(text_win, TRUE);
	wrefresh(text_win);
	help_win = newwin((LINES - 1), COLS, 0, 0);
	keypad(help_win, TRUE);
	idlok(help_win, TRUE);
	if (info_window)
	{
		info_type = CONTROL_KEYS;
		info_win = newwin(6, COLS, 0, 0);
		werase(info_win);
		paint_info_win();
	}

	last_col = COLS - 1;
	local_LINES = LINES;
	local_COLS = COLS;

#ifdef NCURSE
	if (ee_chinese)
		nc_setattrib(A_NC_BIG5);
#endif /* NCURSE */

}