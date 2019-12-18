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

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int LINES ; 
 int MARGIN ; 
 char border_attr ; 
 int /*<<< orphan*/  copywin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 char dialog_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  dlg_boxchar (int /*<<< orphan*/ ) ; 
 int dlg_count_columns (char const*) ; 
 int /*<<< orphan*/  dlg_print_autowrap (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * newwin (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char position_indicator_attr ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wbkgdset (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

int
dlg_print_scrolled(WINDOW *win,
		   const char *prompt,
		   int offset,
		   int height,
		   int width,
		   int pauseopt)
{
    int oldy, oldx;
    int last = 0;

    (void) pauseopt;		/* used only for ncurses */

    getyx(win, oldy, oldx);
#ifdef NCURSES_VERSION
    if (pauseopt) {
	int wide = width - (2 * MARGIN);
	int high = LINES;
	int y, x;
	int len;
	int percent;
	WINDOW *dummy;
	char buffer[5];

#if defined(NCURSES_VERSION_PATCH) && NCURSES_VERSION_PATCH >= 20040417
	/*
	 * If we're not limited by the screensize, allow text to possibly be
	 * one character per line.
	 */
	if ((len = dlg_count_columns(prompt)) > high)
	    high = len;
#endif
	dummy = newwin(high, width, 0, 0);
	if (dummy == 0) {
	    dlg_attrset(win, dialog_attr);
	    dlg_print_autowrap(win, prompt, height + 1 + (3 * MARGIN), width);
	    last = 0;
	} else {
	    wbkgdset(dummy, dialog_attr | ' ');
	    dlg_attrset(dummy, dialog_attr);
	    werase(dummy);
	    dlg_print_autowrap(dummy, prompt, high, width);
	    getyx(dummy, y, x);
	    (void) x;

	    copywin(dummy,	/* srcwin */
		    win,	/* dstwin */
		    offset + MARGIN,	/* sminrow */
		    MARGIN,	/* smincol */
		    MARGIN,	/* dminrow */
		    MARGIN,	/* dmincol */
		    height,	/* dmaxrow */
		    wide,	/* dmaxcol */
		    FALSE);

	    delwin(dummy);

	    /* if the text is incomplete, or we have scrolled, show the percentage */
	    if (y > 0 && wide > 4) {
		percent = (int) ((height + offset) * 100.0 / y);
		if (percent < 0)
		    percent = 0;
		if (percent > 100)
		    percent = 100;
		if (offset != 0 || percent != 100) {
		    dlg_attrset(win, position_indicator_attr);
		    (void) wmove(win, MARGIN + height, wide - 4);
		    (void) sprintf(buffer, "%d%%", percent);
		    (void) waddstr(win, buffer);
		    if ((len = (int) strlen(buffer)) < 4) {
			dlg_attrset(win, border_attr);
			whline(win, dlg_boxchar(ACS_HLINE), 4 - len);
		    }
		}
	    }
	    last = (y - height);
	}
    } else
#endif
    {
	(void) offset;
	dlg_attrset(win, dialog_attr);
	dlg_print_autowrap(win, prompt, height + 1 + (3 * MARGIN), width);
	last = 0;
    }
    wmove(win, oldy, oldx);
    return last;
}