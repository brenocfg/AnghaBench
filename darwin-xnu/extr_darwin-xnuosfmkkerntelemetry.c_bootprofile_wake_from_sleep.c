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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TIMER_CALL_SYS_NORMAL ; 
 scalar_t__ bootprofile_interval_abs ; 
 scalar_t__ bootprofile_next_deadline ; 
 int /*<<< orphan*/  bootprofile_timer_call_entry ; 
 scalar_t__ bootprofile_type ; 
 scalar_t__ kBootProfileStartTimerAtWake ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  timer_call_enter_with_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bootprofile_wake_from_sleep(void)
{
	if (bootprofile_type == kBootProfileStartTimerAtWake) {
		bootprofile_next_deadline = mach_absolute_time() + bootprofile_interval_abs;
		timer_call_enter_with_leeway(&bootprofile_timer_call_entry,
									 NULL,
									 bootprofile_next_deadline,
									 0,
									 TIMER_CALL_SYS_NORMAL,
									 FALSE);
	}
}