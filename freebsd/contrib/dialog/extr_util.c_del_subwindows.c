#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {TYPE_1__* all_subwindows; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  shadow; int /*<<< orphan*/ * normal; } ;
typedef  TYPE_1__ DIALOG_WINDOWS ;

/* Variables and functions */
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 TYPE_3__ dialog_state ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
del_subwindows(WINDOW *parent)
{
    DIALOG_WINDOWS *p = dialog_state.all_subwindows;
    DIALOG_WINDOWS *q = 0;
    DIALOG_WINDOWS *r;

    while (p != 0) {
	if (p->normal == parent) {
	    delwin(p->shadow);
	    r = p->next;
	    if (q == 0) {
		dialog_state.all_subwindows = r;
	    } else {
		q->next = r;
	    }
	    free(p);
	    p = r;
	} else {
	    q = p;
	    p = p->next;
	}
    }
}