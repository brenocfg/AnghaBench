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
struct TYPE_2__ {int default_button; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 TYPE_1__ dialog_vars ; 
 int dlg_ok_buttoncode (int) ; 

int
dlg_default_button(void)
{
    int i, n;
    int result = 0;

    if (dialog_vars.default_button >= 0) {
	for (i = 0; (n = dlg_ok_buttoncode(i)) >= 0; i++) {
	    if (n == dialog_vars.default_button) {
		result = i;
		break;
	    }
	}
    }
    DLG_TRACE(("# dlg_default_button() = %d\n", result));
    return result;
}