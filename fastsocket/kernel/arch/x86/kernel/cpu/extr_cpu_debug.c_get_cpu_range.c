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
struct TYPE_2__ {unsigned int flag; unsigned int min; unsigned int max; } ;

/* Variables and functions */
 TYPE_1__* cpu_reg_range ; 

__attribute__((used)) static unsigned get_cpu_range(unsigned cpu, unsigned *min, unsigned *max,
			      int index, unsigned flag)
{
	if (cpu_reg_range[index].flag == flag) {
		*min = cpu_reg_range[index].min;
		*max = cpu_reg_range[index].max;
	} else
		*max = 0;

	return *max;
}