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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  NTP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_CALL_SYS_CRITICAL ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  ntp_loop_active ; 
 scalar_t__ ntp_loop_deadline ; 
 scalar_t__ ntp_loop_period ; 
 int /*<<< orphan*/  ntp_loop_update ; 
 int /*<<< orphan*/  timer_call_enter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_ntp_loop(void)
{
	boolean_t enable;

	NTP_LOCK(enable);

	ntp_loop_deadline = mach_absolute_time() + ntp_loop_period;

	if (!timer_call_enter(&ntp_loop_update, ntp_loop_deadline, TIMER_CALL_SYS_CRITICAL)) {
			ntp_loop_active++;
	}

	NTP_UNLOCK(enable);
}