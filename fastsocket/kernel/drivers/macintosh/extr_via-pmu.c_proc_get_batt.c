#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int flags; int charge; int max_charge; int amperage; int voltage; int time_remaining; } ;

/* Variables and functions */
 TYPE_1__* pmu_batteries ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int
proc_get_batt(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	long batnum = (long)data;
	char *p = page;
	
	p += sprintf(p, "\n");
	p += sprintf(p, "flags      : %08x\n",
		pmu_batteries[batnum].flags);
	p += sprintf(p, "charge     : %d\n",
		pmu_batteries[batnum].charge);
	p += sprintf(p, "max_charge : %d\n",
		pmu_batteries[batnum].max_charge);
	p += sprintf(p, "current    : %d\n",
		pmu_batteries[batnum].amperage);
	p += sprintf(p, "voltage    : %d\n",
		pmu_batteries[batnum].voltage);
	p += sprintf(p, "time rem.  : %d\n",
		pmu_batteries[batnum].time_remaining);

	return p - page;
}