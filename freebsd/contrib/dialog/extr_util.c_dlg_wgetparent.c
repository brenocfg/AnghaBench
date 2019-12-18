#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {TYPE_1__* all_subwindows; } ;
struct TYPE_3__ {int /*<<< orphan*/ * normal; int /*<<< orphan*/ * shadow; struct TYPE_3__* next; } ;
typedef  TYPE_1__ DIALOG_WINDOWS ;

/* Variables and functions */
 TYPE_2__ dialog_state ; 

WINDOW *
dlg_wgetparent(WINDOW *win)
{
#undef wgetparent
    WINDOW *result = 0;
    DIALOG_WINDOWS *p;

    for (p = dialog_state.all_subwindows; p != 0; p = p->next) {
	if (p->shadow == win) {
	    result = p->normal;
	    break;
	}
    }
    return result;
}