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
 int /*<<< orphan*/  clock_update_calendar () ; 
 int /*<<< orphan*/  refresh_ntp_loop () ; 

__attribute__((used)) static void
ntp_loop_update_call(void)
{
	boolean_t enable;

	NTP_LOCK(enable);

	/*
	 * Update the scale factor used by clock_calend.
	 * NOTE: clock_update_calendar will call ntp_update_second to compute the next adjustment.
	 */
	clock_update_calendar();

	refresh_ntp_loop();

	NTP_UNLOCK(enable);
}