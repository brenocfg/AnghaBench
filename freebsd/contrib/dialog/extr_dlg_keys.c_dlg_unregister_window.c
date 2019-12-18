#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {scalar_t__ is_function_key; struct TYPE_4__* binding; struct TYPE_4__* link; int /*<<< orphan*/ * win; } ;
typedef  TYPE_1__ LIST_BINDINGS ;

/* Variables and functions */
 TYPE_1__* all_bindings ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dlg_unregister_window(WINDOW *win)
{
    LIST_BINDINGS *p, *q;

    for (p = all_bindings, q = 0; p != 0; p = p->link) {
	if (p->win == win) {
	    if (q != 0) {
		q->link = p->link;
	    } else {
		all_bindings = p->link;
	    }
	    /* the user-defined and buttons-bindings all are length=1 */
	    if (p->binding[1].is_function_key < 0)
		free(p->binding);
	    free(p);
	    dlg_unregister_window(win);
	    break;
	}
	q = p;
    }
}