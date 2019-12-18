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
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int /*<<< orphan*/  PANEL ;

/* Variables and functions */
 size_t DIALOG_MENU_FORE ; 
 int /*<<< orphan*/  F_BACK ; 
 int /*<<< orphan*/  F_EXIT ; 
 int /*<<< orphan*/  F_HELP ; 
#define  KEY_DOWN 135 
#define  KEY_END 134 
 int KEY_F (int /*<<< orphan*/ ) ; 
#define  KEY_HOME 133 
#define  KEY_LEFT 132 
#define  KEY_NPAGE 131 
#define  KEY_PPAGE 130 
#define  KEY_RIGHT 129 
#define  KEY_UP 128 
 size_t SCROLLWIN_BOX ; 
 size_t SCROLLWIN_HEADING ; 
 size_t SCROLLWIN_TEXT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * attributes ; 
 int /*<<< orphan*/  box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copywin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_window (int /*<<< orphan*/ *,char const*) ; 
 char* get_line (char const*,int) ; 
 int get_line_length (char const*) ; 
 int get_line_no (char const*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/ * new_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newpad (int,int) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  print_in_middle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_all_windows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void show_scroll_win(WINDOW *main_window,
		const char *title,
		const char *text)
{
	int res;
	int total_lines = get_line_no(text);
	int x, y, lines, columns;
	int start_x = 0, start_y = 0;
	int text_lines = 0, text_cols = 0;
	int total_cols = 0;
	int win_cols = 0;
	int win_lines = 0;
	int i = 0;
	WINDOW *win;
	WINDOW *pad;
	PANEL *panel;

	getmaxyx(stdscr, lines, columns);

	/* find the widest line of msg: */
	total_lines = get_line_no(text);
	for (i = 0; i < total_lines; i++) {
		const char *line = get_line(text, i);
		int len = get_line_length(line);
		total_cols = max(total_cols, len+2);
	}

	/* create the pad */
	pad = newpad(total_lines+10, total_cols+10);
	(void) wattrset(pad, attributes[SCROLLWIN_TEXT]);
	fill_window(pad, text);

	win_lines = min(total_lines+4, lines-2);
	win_cols = min(total_cols+2, columns-2);
	text_lines = max(win_lines-4, 0);
	text_cols = max(win_cols-2, 0);

	/* place window in middle of screen */
	y = (lines-win_lines)/2;
	x = (columns-win_cols)/2;

	win = newwin(win_lines, win_cols, y, x);
	keypad(win, TRUE);
	/* show the help in the help window, and show the help panel */
	(void) wattrset(win, attributes[SCROLLWIN_BOX]);
	box(win, 0, 0);
	(void) wattrset(win, attributes[SCROLLWIN_HEADING]);
	mvwprintw(win, 0, 3, " %s ", title);
	panel = new_panel(win);

	/* handle scrolling */
	do {

		copywin(pad, win, start_y, start_x, 2, 2, text_lines,
				text_cols, 0);
		print_in_middle(win,
				text_lines+2,
				0,
				text_cols,
				"<OK>",
				attributes[DIALOG_MENU_FORE]);
		wrefresh(win);

		res = wgetch(win);
		switch (res) {
		case KEY_NPAGE:
		case ' ':
		case 'd':
			start_y += text_lines-2;
			break;
		case KEY_PPAGE:
		case 'u':
			start_y -= text_lines+2;
			break;
		case KEY_HOME:
			start_y = 0;
			break;
		case KEY_END:
			start_y = total_lines-text_lines;
			break;
		case KEY_DOWN:
		case 'j':
			start_y++;
			break;
		case KEY_UP:
		case 'k':
			start_y--;
			break;
		case KEY_LEFT:
		case 'h':
			start_x--;
			break;
		case KEY_RIGHT:
		case 'l':
			start_x++;
			break;
		}
		if (res == 10 || res == 27 || res == 'q' ||
			res == KEY_F(F_HELP) || res == KEY_F(F_BACK) ||
			res == KEY_F(F_EXIT))
			break;
		if (start_y < 0)
			start_y = 0;
		if (start_y >= total_lines-text_lines)
			start_y = total_lines-text_lines;
		if (start_x < 0)
			start_x = 0;
		if (start_x >= total_cols-text_cols)
			start_x = total_cols-text_cols;
	} while (res);

	del_panel(panel);
	delwin(win);
	refresh_all_windows(main_window);
}