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
typedef  char chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_2__ {scalar_t__ insecure; } ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 char TAB ; 
 char UCH (char const) ; 
 int /*<<< orphan*/  compute_edit_offset (char const*,int,int,int*,int*) ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,char) ; 
 int dlg_count_wchars (char const*) ; 
 int* dlg_index_columns (char const*) ; 
 int* dlg_index_wchars (char const*) ; 
 int /*<<< orphan*/  getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
dlg_show_string(WINDOW *win,
		const char *string,	/* string to display (may be multibyte) */
		int chr_offset,	/* character (not bytes) offset */
		chtype attr,	/* window-attributes */
		int y_base,	/* beginning row on screen */
		int x_base,	/* beginning column on screen */
		int x_last,	/* number of columns on screen */
		bool hidden,	/* if true, do not echo */
		bool force)	/* if true, force repaint */
{
    x_last = MIN(x_last + x_base, getmaxx(win)) - x_base;

    if (hidden && !dialog_vars.insecure) {
	if (force) {
	    (void) wmove(win, y_base, x_base);
	    wrefresh(win);
	}
    } else {
	const int *cols = dlg_index_columns(string);
	const int *indx = dlg_index_wchars(string);
	int limit = dlg_count_wchars(string);

	int i, j, k;
	int input_x;
	int scrollamt;

	compute_edit_offset(string, chr_offset, x_last, &input_x, &scrollamt);

	dlg_attrset(win, attr);
	(void) wmove(win, y_base, x_base);
	for (i = scrollamt, k = 0; i < limit && k < x_last; ++i) {
	    int check = cols[i + 1] - cols[scrollamt];
	    if (check <= x_last) {
		for (j = indx[i]; j < indx[i + 1]; ++j) {
		    chtype ch = UCH(string[j]);
		    if (hidden && dialog_vars.insecure) {
			waddch(win, '*');
		    } else if (ch == TAB) {
			int count = cols[i + 1] - cols[i];
			while (--count >= 0)
			    waddch(win, ' ');
		    } else {
			waddch(win, ch);
		    }
		}
		k = check;
	    } else {
		break;
	    }
	}
	while (k++ < x_last)
	    waddch(win, ' ');
	(void) wmove(win, y_base, x_base + input_x);
	wrefresh(win);
    }
}