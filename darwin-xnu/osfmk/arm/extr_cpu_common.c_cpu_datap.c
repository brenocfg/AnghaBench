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
typedef  int /*<<< orphan*/  cpu_data_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cpu_data_vaddr; } ;

/* Variables and functions */
 TYPE_1__* CpuDataEntries ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  assert (int) ; 

cpu_data_t *
cpu_datap(int cpu)
{
	assert(cpu < MAX_CPUS);
	return (CpuDataEntries[cpu].cpu_data_vaddr);
}