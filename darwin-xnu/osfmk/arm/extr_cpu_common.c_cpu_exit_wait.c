#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cpu_sleep_token; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_4__ {TYPE_1__* cpu_data_vaddr; } ;

/* Variables and functions */
 unsigned int volatile ARM_CPU_ON_SLEEP_PATH ; 
 TYPE_2__* CpuDataEntries ; 
 int master_cpu ; 

void
cpu_exit_wait(int cpu)
{
	if ( cpu != master_cpu) {
		cpu_data_t	*cpu_data_ptr;

		cpu_data_ptr = CpuDataEntries[cpu].cpu_data_vaddr;
		while (!((*(volatile unsigned int*)&cpu_data_ptr->cpu_sleep_token) == ARM_CPU_ON_SLEEP_PATH)) {};
	}
}