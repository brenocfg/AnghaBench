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
typedef  char chtype ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  ACS_LLCORNER ; 
 int /*<<< orphan*/  ACS_LRCORNER ; 
 int /*<<< orphan*/  ACS_ULCORNER ; 
 int /*<<< orphan*/  ACS_URCORNER ; 
 int /*<<< orphan*/  ACS_VLINE ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,char) ; 
 char dlg_boxchar (int /*<<< orphan*/ ) ; 
 char dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

void
dlg_draw_box2(WINDOW *win, int y, int x, int height, int width,
	      chtype boxchar, chtype borderchar, chtype borderchar2)
{
    int i, j;
    chtype save = dlg_get_attrs(win);

    dlg_attrset(win, 0);
    for (i = 0; i < height; i++) {
	(void) wmove(win, y + i, x);
	for (j = 0; j < width; j++)
	    if (!i && !j)
		(void) waddch(win, borderchar | dlg_boxchar(ACS_ULCORNER));
	    else if (i == height - 1 && !j)
		(void) waddch(win, borderchar | dlg_boxchar(ACS_LLCORNER));
	    else if (!i && j == width - 1)
		(void) waddch(win, borderchar2 | dlg_boxchar(ACS_URCORNER));
	    else if (i == height - 1 && j == width - 1)
		(void) waddch(win, borderchar2 | dlg_boxchar(ACS_LRCORNER));
	    else if (!i)
		(void) waddch(win, borderchar | dlg_boxchar(ACS_HLINE));
	    else if (i == height - 1)
		(void) waddch(win, borderchar2 | dlg_boxchar(ACS_HLINE));
	    else if (!j)
		(void) waddch(win, borderchar | dlg_boxchar(ACS_VLINE));
	    else if (j == width - 1)
		(void) waddch(win, borderchar2 | dlg_boxchar(ACS_VLINE));
	    else
		(void) waddch(win, boxchar | ' ');
    }
    dlg_attrset(win, save);
}