#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_4__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {int /*<<< orphan*/ * cpu_nested_pmap; } ;
struct TYPE_12__ {int /*<<< orphan*/  cpu_id; TYPE_4__* cpu_active_thread; TYPE_2__* cpu_processor; TYPE_1__ cpu_pmap_cpu_data; scalar_t__ cpu_reset_handler; } ;
typedef  TYPE_5__ cpu_data_t ;
typedef  int /*<<< orphan*/  cpu_data_entry_t ;
struct TYPE_13__ {TYPE_5__* cpu_data_vaddr; } ;
struct TYPE_10__ {TYPE_5__* CpuDatap; } ;
struct TYPE_11__ {TYPE_3__ machine; } ;
struct TYPE_9__ {scalar_t__ next_thread; TYPE_4__* idle_thread; } ;

/* Variables and functions */
 TYPE_7__* CpuDataEntries ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PE_cpu_start (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  configure_coresight_registers (TYPE_5__*) ; 
 int /*<<< orphan*/  cpu_machine_init () ; 
 int cpu_number () ; 
 int /*<<< orphan*/  flush_dcache (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 scalar_t__ start_cpu_paddr ; 

kern_return_t
cpu_start(int cpu)
{
	cpu_data_t *cpu_data_ptr = CpuDataEntries[cpu].cpu_data_vaddr;

	kprintf("cpu_start() cpu: %d\n", cpu);

	if (cpu == cpu_number()) {
		cpu_machine_init();
		configure_coresight_registers(cpu_data_ptr);
	} else {
		thread_t first_thread;

		cpu_data_ptr->cpu_reset_handler = (vm_offset_t) start_cpu_paddr;

		cpu_data_ptr->cpu_pmap_cpu_data.cpu_nested_pmap = NULL;

		if (cpu_data_ptr->cpu_processor->next_thread != THREAD_NULL)
			first_thread = cpu_data_ptr->cpu_processor->next_thread;
		else
			first_thread = cpu_data_ptr->cpu_processor->idle_thread;
		cpu_data_ptr->cpu_active_thread = first_thread;
		first_thread->machine.CpuDatap = cpu_data_ptr;

		configure_coresight_registers(cpu_data_ptr);

		flush_dcache((vm_offset_t)&CpuDataEntries[cpu], sizeof(cpu_data_entry_t), FALSE);
		flush_dcache((vm_offset_t)cpu_data_ptr, sizeof(cpu_data_t), FALSE);
		(void) PE_cpu_start(cpu_data_ptr->cpu_id, (vm_offset_t)NULL, (vm_offset_t)NULL);
	}

	return KERN_SUCCESS;
}