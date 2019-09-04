#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_4__ {scalar_t__ excepstack_top; scalar_t__ intstack_top; int /*<<< orphan*/  cpu_processor; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 TYPE_1__ BootCpuData ; 
 scalar_t__ EXCEPSTACK_SIZE ; 
 scalar_t__ INTSTACK_SIZE ; 
 int /*<<< orphan*/  cpu_processor_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kfree (void*,scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
cpu_data_free(cpu_data_t *cpu_data_ptr)
{
        if (cpu_data_ptr == &BootCpuData)
                return;

	cpu_processor_free( cpu_data_ptr->cpu_processor);
	kfree( (void *)(cpu_data_ptr->intstack_top - INTSTACK_SIZE), INTSTACK_SIZE);
	kfree( (void *)(cpu_data_ptr->excepstack_top - EXCEPSTACK_SIZE), EXCEPSTACK_SIZE);
	kmem_free(kernel_map, (vm_offset_t)cpu_data_ptr, sizeof(cpu_data_t));
}