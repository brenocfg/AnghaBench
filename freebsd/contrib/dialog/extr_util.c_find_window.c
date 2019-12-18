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
struct TYPE_5__ {TYPE_1__* all_windows; } ;
struct TYPE_4__ {int /*<<< orphan*/ * normal; struct TYPE_4__* next; } ;
typedef  TYPE_1__ DIALOG_WINDOWS ;

/* Variables and functions */
 TYPE_3__ dialog_state ; 

__attribute__((used)) static DIALOG_WINDOWS *
find_window(WINDOW *win)
{
    DIALOG_WINDOWS *result = 0;
    DIALOG_WINDOWS *p;

    for (p = dialog_state.all_windows; p != 0; p = p->next) {
	if (p->normal == win) {
	    result = p;
	    break;
	}
    }
    return result;
}