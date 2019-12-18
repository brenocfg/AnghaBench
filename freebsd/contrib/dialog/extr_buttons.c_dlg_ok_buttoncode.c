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
struct TYPE_2__ {scalar_t__ help_button; int /*<<< orphan*/  nocancel; scalar_t__ extra_button; int /*<<< orphan*/  nook; } ;

/* Variables and functions */
 int DLG_EXIT_CANCEL ; 
 int DLG_EXIT_ERROR ; 
 int DLG_EXIT_EXTRA ; 
 int DLG_EXIT_HELP ; 
 int DLG_EXIT_OK ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 TYPE_1__ dialog_vars ; 

int
dlg_ok_buttoncode(int button)
{
    int result = DLG_EXIT_ERROR;
    int n = !dialog_vars.nook;

    if (!dialog_vars.nook && (button <= 0)) {
	result = DLG_EXIT_OK;
    } else if (dialog_vars.extra_button && (button == n++)) {
	result = DLG_EXIT_EXTRA;
    } else if (!dialog_vars.nocancel && (button == n++)) {
	result = DLG_EXIT_CANCEL;
    } else if (dialog_vars.help_button && (button == n)) {
	result = DLG_EXIT_HELP;
    }
    DLG_TRACE(("# dlg_ok_buttoncode(%d) = %d\n", button, result));
    return result;
}