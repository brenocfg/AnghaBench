#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int CPU_TSS ; 
 TYPE_1__* cpu_reg_range ; 

__attribute__((used)) static int is_typeflag_valid(unsigned cpu, unsigned flag)
{
	int i;

	/* Standard Registers should be always valid */
	if (flag >= CPU_TSS)
		return 1;

	for (i = 0; i < ARRAY_SIZE(cpu_reg_range); i++) {
		if (cpu_reg_range[i].flag == flag)
			return 1;
	}

	/* Invalid */
	return 0;
}