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
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  cpu_machine_init () ; 
 int cpu_number () ; 
 scalar_t__ intel_startCPU (int) ; 
 scalar_t__ intel_startCPU_fast (int) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 

kern_return_t
cpu_start(
	int cpu)
{
	kern_return_t		ret;

	if (cpu == cpu_number()) {
		cpu_machine_init();
		return KERN_SUCCESS;
	}

	/*
	 * Try to bring the CPU back online without a reset.
	 * If the fast restart doesn't succeed, fall back to
	 * the slow way.
	 */
	ret = intel_startCPU_fast(cpu);
	if (ret != KERN_SUCCESS) {
		/*
		 * Should call out through PE.
		 * But take the shortcut here.
		 */
		ret = intel_startCPU(cpu);
	}

	if (ret != KERN_SUCCESS)
		kprintf("cpu: cpu_start(%d) returning failure!\n", cpu);

	return(ret);
}