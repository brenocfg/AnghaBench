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
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long rtc_time () ; 
 unsigned long sn_rtc_cycles_per_second ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void
ia64_sn_udelay (unsigned long usecs)
{
	unsigned long start = rtc_time();
	unsigned long end = start +
			usecs * sn_rtc_cycles_per_second / 1000000;

	while (time_before((unsigned long)rtc_time(), end))
		cpu_relax();
}