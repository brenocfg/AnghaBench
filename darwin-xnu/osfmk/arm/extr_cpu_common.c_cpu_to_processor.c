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
typedef  int /*<<< orphan*/ * processor_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cpu_processor; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 TYPE_1__* cpu_datap (int) ; 

processor_t
cpu_to_processor(int cpu)
{
	cpu_data_t *cpu_data = cpu_datap(cpu);
	if (cpu_data != NULL)
		return cpu_data->cpu_processor;
	else
		return NULL;
}