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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  cpu_machine_init () ; 
 int cpu_number () ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 

kern_return_t
cpu_start(int cpu)
{
	kprintf("cpu_start() cpu: %d\n", cpu);
	if (cpu == cpu_number()) {
		cpu_machine_init();
		return KERN_SUCCESS;
	} else {
#if     __ARM_SMP__
		cpu_data_t	*cpu_data_ptr;
		thread_t	first_thread;

		cpu_data_ptr = CpuDataEntries[cpu].cpu_data_vaddr;
		cpu_data_ptr->cpu_reset_handler = (vm_offset_t) start_cpu_paddr;

		cpu_data_ptr->cpu_pmap_cpu_data.cpu_user_pmap = NULL;

		if (cpu_data_ptr->cpu_processor->next_thread != THREAD_NULL)
			first_thread = cpu_data_ptr->cpu_processor->next_thread;
		else
			first_thread = cpu_data_ptr->cpu_processor->idle_thread;
		cpu_data_ptr->cpu_active_thread = first_thread;
		first_thread->machine.CpuDatap = cpu_data_ptr;

		flush_dcache((vm_offset_t)&CpuDataEntries[cpu], sizeof(cpu_data_entry_t), FALSE);
		flush_dcache((vm_offset_t)cpu_data_ptr, sizeof(cpu_data_t), FALSE);
		(void) PE_cpu_start(cpu_data_ptr->cpu_id, (vm_offset_t)NULL, (vm_offset_t)NULL);
		return KERN_SUCCESS;
#else
		return KERN_FAILURE;
#endif
	}
}