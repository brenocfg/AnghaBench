#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int cpu_number; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_5__ {void* cpu_data_paddr; TYPE_1__* cpu_data_vaddr; } ;

/* Variables and functions */
 int CPUWINDOWS_MAX ; 
 TYPE_3__* CpuDataEntries ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kasan_notify_address_nopoison (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ml_vtophys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_cpu_windows_copy_addr (int,int) ; 

kern_return_t
cpu_data_register(cpu_data_t *cpu_data_ptr)
{
	int	cpu = cpu_data_ptr->cpu_number;

#if KASAN
	for (int i = 0; i < CPUWINDOWS_MAX; i++) {
		kasan_notify_address_nopoison(pmap_cpu_windows_copy_addr(cpu, i), PAGE_SIZE);
	}
#endif

	CpuDataEntries[cpu].cpu_data_vaddr = cpu_data_ptr;
	CpuDataEntries[cpu].cpu_data_paddr = (void *)ml_vtophys( (vm_offset_t)cpu_data_ptr);
	return KERN_SUCCESS;

}