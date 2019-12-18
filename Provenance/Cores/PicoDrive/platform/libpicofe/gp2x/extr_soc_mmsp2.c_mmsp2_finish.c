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
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ cpuclk_was_changed ; 
 scalar_t__ gamma_was_changed ; 
 scalar_t__ memdev ; 
 int /*<<< orphan*/ * memregs ; 
 scalar_t__ mixerdev ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int /*<<< orphan*/  pause940 (int) ; 
 int /*<<< orphan*/  reg0910 ; 
 int /*<<< orphan*/  reset940 (int,int) ; 
 int /*<<< orphan*/  set_lcd_gamma_ (int,int /*<<< orphan*/ ) ; 
 scalar_t__ touchdev ; 
 int /*<<< orphan*/  unset_lcd_custom_rate_ () ; 
 int /*<<< orphan*/  unset_ram_timings_ () ; 

void mmsp2_finish(void)
{
	reset940(1, 3);
	pause940(1);

	unset_lcd_custom_rate_();
	if (gamma_was_changed)
		set_lcd_gamma_(100, 0);
	unset_ram_timings_();
	if (cpuclk_was_changed)
		memregs[0x910>>1] = reg0910;

	munmap((void *)memregs, 0x10000);
	close(memdev);
	if (touchdev >= 0)
		close(touchdev);
	if (mixerdev >= 0)
		close(mixerdev);
}