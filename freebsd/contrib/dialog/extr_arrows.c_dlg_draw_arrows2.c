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
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_2__ {scalar_t__ title; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_DARROW ; 
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  ACS_UARROW ; 
 int FALSE ; 
 int /*<<< orphan*/  KEY_NPAGE ; 
 int /*<<< orphan*/  KEY_PPAGE ; 
 int MARGIN ; 
 int /*<<< orphan*/  ON_LEFT ; 
 int TRUE ; 
 int /*<<< orphan*/  add_acs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  darrow_attr ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_boxchar (int /*<<< orphan*/ ) ; 
 int dlg_count_columns (scalar_t__) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int getbegy (int /*<<< orphan*/ *) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  merge_colors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_mkbutton (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stdscr ; 
 int /*<<< orphan*/  uarrow_attr ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wgetparent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
dlg_draw_arrows2(WINDOW *win,
		 int top_arrow,
		 int bottom_arrow,
		 int x,
		 int top,
		 int bottom,
		 chtype attr,
		 chtype borderattr)
{
    chtype save = dlg_get_attrs(win);
    int cur_x, cur_y;
    int limit_x = getmaxx(win);
    bool draw_top = TRUE;
    bool is_toplevel = (wgetparent(win) == stdscr);

    getyx(win, cur_y, cur_x);

    /*
     * If we're drawing a centered title, do not overwrite with the arrows.
     */
    if (dialog_vars.title && is_toplevel && (top - getbegy(win)) < MARGIN) {
	int have = (limit_x - dlg_count_columns(dialog_vars.title)) / 2;
	int need = x + 5;
	if (need > have)
	    draw_top = FALSE;
    }

    if (draw_top) {
	(void) wmove(win, top, x);
	if (top_arrow) {
	    dlg_attrset(win, merge_colors(uarrow_attr, attr));
	    (void) add_acs(win, ACS_UARROW);
	    (void) waddstr(win, "(-)");
	} else {
	    dlg_attrset(win, attr);
	    (void) whline(win, dlg_boxchar(ACS_HLINE), ON_LEFT);
	}
    }
    mouse_mkbutton(top, x - 1, 6, KEY_PPAGE);

    (void) wmove(win, bottom, x);
    if (bottom_arrow) {
	dlg_attrset(win, merge_colors(darrow_attr, borderattr));
	(void) add_acs(win, ACS_DARROW);
	(void) waddstr(win, "(+)");
    } else {
	dlg_attrset(win, borderattr);
	(void) whline(win, dlg_boxchar(ACS_HLINE), ON_LEFT);
    }
    mouse_mkbutton(bottom, x - 1, 6, KEY_NPAGE);

    (void) wmove(win, cur_y, cur_x);
    wrefresh(win);

    dlg_attrset(win, save);
}