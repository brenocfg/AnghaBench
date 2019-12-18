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
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  COMMAND_GLOBAL ; 
 int /*<<< orphan*/  PDC_CHASSIS_DIRECT_SHUTDOWN ; 
 scalar_t__ ftc_bitmap ; 
 int /*<<< orphan*/  gsc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_chassis_send_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_do_firm_test_reset (scalar_t__) ; 
 int /*<<< orphan*/  pdc_do_reset () ; 

void machine_restart(char *cmd)
{
#ifdef FASTBOOT_SELFTEST_SUPPORT
	/*
	 ** If user has modified the Firmware Selftest Bitmap,
	 ** run the tests specified in the bitmap after the
	 ** system is rebooted w/PDC_DO_RESET.
	 **
	 ** ftc_bitmap = 0x1AUL "Skip destructive memory tests"
	 **
	 ** Using "directed resets" at each processor with the MEM_TOC
	 ** vector cleared will also avoid running destructive
	 ** memory self tests. (Not implemented yet)
	 */
	if (ftc_bitmap) {
		pdc_do_firm_test_reset(ftc_bitmap);
	}
#endif
	/* set up a new led state on systems shipped with a LED State panel */
	pdc_chassis_send_status(PDC_CHASSIS_DIRECT_SHUTDOWN);
	
	/* "Normal" system reset */
	pdc_do_reset();

	/* Nope...box should reset with just CMD_RESET now */
	gsc_writel(CMD_RESET, COMMAND_GLOBAL);

	/* Wait for RESET to lay us to rest. */
	while (1) ;

}