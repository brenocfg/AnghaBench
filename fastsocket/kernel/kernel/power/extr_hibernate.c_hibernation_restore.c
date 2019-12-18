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

/* Variables and functions */
 int /*<<< orphan*/  PMSG_QUIESCE ; 
 int /*<<< orphan*/  PMSG_RECOVER ; 
 int /*<<< orphan*/  dpm_resume_end (int /*<<< orphan*/ ) ; 
 int dpm_suspend_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_prepare_console () ; 
 int /*<<< orphan*/  pm_restore_console () ; 
 int /*<<< orphan*/  pm_restore_gfp_mask () ; 
 int /*<<< orphan*/  pm_restrict_gfp_mask () ; 
 int /*<<< orphan*/  resume_console () ; 
 int resume_target_kernel (int) ; 
 int /*<<< orphan*/  suspend_console () ; 

int hibernation_restore(int platform_mode)
{
	int error;

	pm_prepare_console();
	suspend_console();
	pm_restrict_gfp_mask();
	error = dpm_suspend_start(PMSG_QUIESCE);
	if (!error) {
		error = resume_target_kernel(platform_mode);
		dpm_resume_end(PMSG_RECOVER);
	}
	pm_restore_gfp_mask();
	resume_console();
	pm_restore_console();
	return error;
}