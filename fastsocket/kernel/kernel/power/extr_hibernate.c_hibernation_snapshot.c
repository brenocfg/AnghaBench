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
 int /*<<< orphan*/  PMSG_FREEZE ; 
 int /*<<< orphan*/  PMSG_RECOVER ; 
 int /*<<< orphan*/  PMSG_RESTORE ; 
 int /*<<< orphan*/  PMSG_THAW ; 
 int /*<<< orphan*/  TEST_DEVICES ; 
 int create_image (int) ; 
 int /*<<< orphan*/  dpm_resume_end (int /*<<< orphan*/ ) ; 
 int dpm_suspend_start (int /*<<< orphan*/ ) ; 
 int hibernate_preallocate_memory () ; 
 scalar_t__ hibernation_test (int /*<<< orphan*/ ) ; 
 scalar_t__ in_suspend ; 
 int platform_begin (int) ; 
 int /*<<< orphan*/  platform_end (int) ; 
 int /*<<< orphan*/  platform_recover (int) ; 
 int /*<<< orphan*/  pm_restore_gfp_mask () ; 
 int /*<<< orphan*/  pm_restrict_gfp_mask () ; 
 int /*<<< orphan*/  resume_console () ; 
 int /*<<< orphan*/  suspend_console () ; 
 int /*<<< orphan*/  swsusp_free () ; 

int hibernation_snapshot(int platform_mode)
{
	int error;

	error = platform_begin(platform_mode);
	if (error)
		return error;

	/* Preallocate image memory before shutting down devices. */
	error = hibernate_preallocate_memory();
	if (error)
		goto Close;

	suspend_console();
	pm_restrict_gfp_mask();
	error = dpm_suspend_start(PMSG_FREEZE);
	if (error)
		goto Recover_platform;

	if (hibernation_test(TEST_DEVICES))
		goto Recover_platform;

	error = create_image(platform_mode);
	/*
	 * Control returns here (1) after the image has been created or the
	 * image creation has failed and (2) after a successful restore.
	 */

 Resume_devices:
	/* We may need to release the preallocated image pages here. */
	if (error || !in_suspend)
		swsusp_free();

	dpm_resume_end(in_suspend ?
		(error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE);

	if (error || !in_suspend)
		pm_restore_gfp_mask();

	resume_console();
 Close:
	platform_end(platform_mode);
	return error;

 Recover_platform:
	platform_recover(platform_mode);
	goto Resume_devices;
}