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
struct TYPE_2__ {int /*<<< orphan*/  nocancel; scalar_t__ defaultno; } ;

/* Variables and functions */
 scalar_t__ DLG_EXIT_CANCEL ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 TYPE_1__ dialog_vars ; 
 scalar_t__ dlg_ok_buttoncode (int) ; 

int
dlg_defaultno_button(void)
{
    int result = 0;

    if (dialog_vars.defaultno && !dialog_vars.nocancel) {
	while (dlg_ok_buttoncode(result) != DLG_EXIT_CANCEL)
	    ++result;
    }
    DLG_TRACE(("# dlg_defaultno_button() = %d\n", result));
    return result;
}