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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ battdev ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ memdev ; 
 int* memregl ; 
 scalar_t__ memregs ; 
 scalar_t__ mixerdev ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int /*<<< orphan*/  restore_multiple_regs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * saved_video_regs ; 
 int /*<<< orphan*/  timer_cleanup () ; 
 int /*<<< orphan*/  unset_ram_timings () ; 

void pollux_finish(void)
{
	timer_cleanup();

	unset_ram_timings();

	restore_multiple_regs(0x4058, saved_video_regs[0],
		ARRAY_SIZE(saved_video_regs[0]));
	restore_multiple_regs(0x4458, saved_video_regs[1],
		ARRAY_SIZE(saved_video_regs[1]));
	memregl[0x4058>>2] |= 0x10;
	memregl[0x4458>>2] |= 0x10;

	if (battdev >= 0)
		close(battdev);
	if (mixerdev >= 0)
		close(mixerdev);
	munmap((void *)memregs, 0x20000);
	close(memdev);
}