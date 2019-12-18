#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_6__ {scalar_t__ use_shadow; } ;
struct TYPE_5__ {int /*<<< orphan*/ * shadow; } ;
typedef  TYPE_1__ DIALOG_WINDOWS ;

/* Variables and functions */
 int SHADOW_COLS ; 
 int SHADOW_ROWS ; 
 TYPE_4__ dialog_state ; 
 int /*<<< orphan*/  dlg_ctl_size (int,int) ; 
 int /*<<< orphan*/  draw_childs_shadow (TYPE_1__*) ; 
 TYPE_1__* find_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvwin (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  wresize (int /*<<< orphan*/ *,int,int) ; 

void
dlg_move_window(WINDOW *win, int height, int width, int y, int x)
{
    DIALOG_WINDOWS *p;

    if (win != 0) {
	dlg_ctl_size(height, width);

	if ((p = find_window(win)) != 0) {
	    (void) wresize(win, height, width);
	    (void) mvwin(win, y, x);
#ifdef HAVE_COLOR
	    if (p->shadow != 0) {
		if (dialog_state.use_shadow) {
		    (void) mvwin(p->shadow, y + SHADOW_ROWS, x + SHADOW_COLS);
		} else {
		    p->shadow = 0;
		}
	    }
#endif
	    (void) refresh();

#ifdef HAVE_COLOR
	    draw_childs_shadow(p);
#endif
	}
    }
}