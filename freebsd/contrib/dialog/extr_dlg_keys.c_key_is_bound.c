#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {TYPE_1__* binding; int /*<<< orphan*/  name; int /*<<< orphan*/ * win; struct TYPE_5__* link; } ;
struct TYPE_4__ {int is_function_key; int curses_key; } ;
typedef  TYPE_2__ LIST_BINDINGS ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_2__* all_bindings ; 
 int /*<<< orphan*/  dlg_strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
key_is_bound(WINDOW *win, const char *name, int curses_key, int function_key)
{
    LIST_BINDINGS *p;

    for (p = all_bindings; p != 0; p = p->link) {
	if (p->win == win && !dlg_strcmp(p->name, name)) {
	    int n;
	    for (n = 0; p->binding[n].is_function_key >= 0; ++n) {
		if (p->binding[n].curses_key == curses_key
		    && p->binding[n].is_function_key == function_key) {
		    return TRUE;
		}
	    }
	}
    }
    return FALSE;
}