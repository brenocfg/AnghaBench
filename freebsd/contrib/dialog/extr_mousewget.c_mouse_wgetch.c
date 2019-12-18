#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int code; int x; int y; int X; int step_x; int mode; } ;
typedef  TYPE_1__ mseRegion ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_7__ {int y; int x; } ;
typedef  TYPE_2__ MEVENT ;

/* Variables and functions */
 int DLGK_MOUSE (int) ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 scalar_t__ ERR ; 
 int FALSE ; 
 int KEY_MOUSE ; 
 int TRUE ; 
 int /*<<< orphan*/  beep () ; 
 int dlg_getc (int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* dlg_mouse_bigregion (int,int) ; 
 TYPE_1__* dlg_mouse_region (int,int) ; 
 scalar_t__ getbegx (int /*<<< orphan*/ *) ; 
 scalar_t__ getbegy (int /*<<< orphan*/ *) ; 
 scalar_t__ getmouse (TYPE_2__*) ; 

__attribute__((used)) static int
mouse_wgetch(WINDOW *win, int *fkey, bool ignore_errs)
{
    int mouse_err = FALSE;
    int key;

    do {

	key = dlg_getc(win, fkey);

#if USE_MOUSE

	mouse_err = FALSE;
	if (key == KEY_MOUSE) {
	    MEVENT event;
	    mseRegion *p;

	    if (getmouse(&event) != ERR) {
		DLG_TRACE(("# mouse-click abs %d,%d (rel %d,%d)\n",
			   event.y, event.x,
			   event.y - getbegy(win),
			   event.x - getbegx(win)));
		if ((p = dlg_mouse_region(event.y, event.x)) != 0) {
		    key = DLGK_MOUSE(p->code);
		} else if ((p = dlg_mouse_bigregion(event.y, event.x)) != 0) {
		    int x = event.x - p->x;
		    int y = event.y - p->y;
		    int row = (p->X - p->x) / p->step_x;

		    key = -(p->code);
		    switch (p->mode) {
		    case 1:	/* index by lines */
			key += y;
			break;
		    case 2:	/* index by columns */
			key += (x / p->step_x);
			break;
		    default:
		    case 3:	/* index by cells */
			key += (x / p->step_x) + (y * row);
			break;
		    }
		} else {
		    (void) beep();
		    mouse_err = TRUE;
		}
	    } else {
		(void) beep();
		mouse_err = TRUE;
	    }
	}
#endif

    } while (ignore_errs && mouse_err);

    return key;
}