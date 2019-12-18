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
struct TYPE_2__ {int /*<<< orphan*/  nocancel; } ;
typedef  int /*<<< orphan*/  DIALOG_VARS ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ dialog_vars ; 
 int dlg_ok_buttoncode (int) ; 
 int /*<<< orphan*/  dlg_restore_vars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_save_vars (int /*<<< orphan*/ *) ; 

int
dlg_exit_buttoncode(int button)
{
    int result;
    DIALOG_VARS save;

    dlg_save_vars(&save);
    dialog_vars.nocancel = TRUE;

    result = dlg_ok_buttoncode(button);

    dlg_restore_vars(&save);

    return result;
}