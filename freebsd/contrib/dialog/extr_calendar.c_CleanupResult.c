#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int /*<<< orphan*/  DIALOG_VARS ;

/* Variables and functions */
 int MAX_DAYS ; 
 int MAX_MONTHS ; 
 char** cached_days ; 
 char** cached_months ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_mouse_free_regions () ; 
 int /*<<< orphan*/  dlg_restore_vars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int
CleanupResult(int code, WINDOW *dialog, char *prompt, DIALOG_VARS * save_vars)
{
    int n;

    if (dialog != 0)
	dlg_del_window(dialog);
    dlg_mouse_free_regions();
    if (prompt != 0)
	free(prompt);
    dlg_restore_vars(save_vars);

    for (n = 0; n < MAX_DAYS; ++n) {
	free(cached_days[n]);
	cached_days[n] = 0;
    }
    for (n = 0; n < MAX_MONTHS; ++n) {
	free(cached_months[n]);
	cached_months[n] = 0;
    }

    return code;
}