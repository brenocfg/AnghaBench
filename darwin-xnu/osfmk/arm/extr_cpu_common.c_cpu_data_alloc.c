#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct processor {int dummy; } ;
struct TYPE_5__ {struct processor* cpu_processor; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 TYPE_1__ BootCpuData ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_CPU ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 struct processor* cpu_processor_alloc (scalar_t__) ; 
 int /*<<< orphan*/  cpu_stack_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

cpu_data_t *
cpu_data_alloc(boolean_t is_boot_cpu)
{
	cpu_data_t		*cpu_data_ptr = NULL;

	if (is_boot_cpu)
		cpu_data_ptr = &BootCpuData;
	else {
		if ((kmem_alloc(kernel_map, (vm_offset_t *)&cpu_data_ptr, sizeof(cpu_data_t), VM_KERN_MEMORY_CPU)) != KERN_SUCCESS)
			goto cpu_data_alloc_error;

		bzero((void *)cpu_data_ptr, sizeof(cpu_data_t));

		cpu_stack_alloc(cpu_data_ptr);
	}

	cpu_data_ptr->cpu_processor = cpu_processor_alloc(is_boot_cpu);
	if (cpu_data_ptr->cpu_processor == (struct processor *)NULL)
		goto cpu_data_alloc_error;

	return cpu_data_ptr;

cpu_data_alloc_error:
	panic("cpu_data_alloc() failed\n");
	return (cpu_data_t *)NULL;
}