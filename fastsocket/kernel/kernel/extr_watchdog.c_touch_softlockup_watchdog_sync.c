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
typedef  int __raw_get_cpu_var ;

/* Variables and functions */

void touch_softlockup_watchdog_sync(void)
{
	__raw_get_cpu_var(softlockup_touch_sync) = true;
	__raw_get_cpu_var(watchdog_touch_ts) = 0;
}