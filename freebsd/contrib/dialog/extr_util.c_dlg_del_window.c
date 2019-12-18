#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {scalar_t__ getc_callbacks; TYPE_1__* all_windows; } ;
struct TYPE_7__ {scalar_t__ keep_window; } ;
struct TYPE_6__ {scalar_t__ shadow; int /*<<< orphan*/ * normal; struct TYPE_6__* next; } ;
typedef  TYPE_1__ DIALOG_WINDOWS ;

/* Variables and functions */
 int /*<<< orphan*/  del_subwindows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 TYPE_5__ dialog_state ; 
 TYPE_4__ dialog_vars ; 
 int /*<<< orphan*/  dlg_unregister_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doupdate () ; 
 int /*<<< orphan*/  erase_childs_shadow (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ *) ; 

void
dlg_del_window(WINDOW *win)
{
    DIALOG_WINDOWS *p, *q, *r;

    /*
     * If --keep-window was set, do not delete/repaint the windows.
     */
    if (dialog_vars.keep_window)
	return;

    /* Leave the main window untouched if there are no background windows.
     * We do this so the current window will not be cleared on exit, allowing
     * things like the infobox demo to run without flicker.
     */
    if (dialog_state.getc_callbacks != 0) {
	touchwin(stdscr);
	wnoutrefresh(stdscr);
    }

    for (p = dialog_state.all_windows, q = r = 0; p != 0; r = p, p = p->next) {
	if (p->normal == win) {
	    q = p;		/* found a match - should be only one */
	    if (r == 0) {
		dialog_state.all_windows = p->next;
	    } else {
		r->next = p->next;
	    }
	} else {
	    if (p->shadow != 0) {
		touchwin(p->shadow);
		wnoutrefresh(p->shadow);
	    }
	    touchwin(p->normal);
	    wnoutrefresh(p->normal);
	}
    }

    if (q) {
	if (dialog_state.all_windows != 0)
	    erase_childs_shadow(q);
	del_subwindows(q->normal);
	dlg_unregister_window(q->normal);
	delwin(q->normal);
	free(q);
    }
    doupdate();
}