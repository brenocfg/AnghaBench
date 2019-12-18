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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int PMU_DRIVER_VERSION ; 
 int PMU_PWR_AC_PRESENT ; 
 int pmu_battery_count ; 
 int pmu_power_flags ; 
 int pmu_version ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
proc_get_info(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	char* p = page;

	p += sprintf(p, "PMU driver version     : %d\n", PMU_DRIVER_VERSION);
	p += sprintf(p, "PMU firmware version   : %02x\n", pmu_version);
	p += sprintf(p, "AC Power               : %d\n",
		((pmu_power_flags & PMU_PWR_AC_PRESENT) != 0) || pmu_battery_count == 0);
	p += sprintf(p, "Battery count          : %d\n", pmu_battery_count);

	return p - page;
}