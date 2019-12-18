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
typedef  void* vm_map_t ;
typedef  void* task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  cpu_type_t ;
typedef  int /*<<< orphan*/  cpu_subtype_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (void*) ; 
 void* current_task () ; 
 int /*<<< orphan*/  vm_commpage_enter (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_shared_region_enter (void*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_exec(
	vm_map_t	new_map,
	task_t		task,
	boolean_t	is64bit,
	void		*fsroot,
	cpu_type_t	cpu,
	cpu_subtype_t	cpu_subtype)
{
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: task %p: vm_map_exec(%p,%p,%p,0x%x,0x%x): ->\n",
		 (void *)VM_KERNEL_ADDRPERM(current_task()),
		 (void *)VM_KERNEL_ADDRPERM(new_map),
		 (void *)VM_KERNEL_ADDRPERM(task),
		 (void *)VM_KERNEL_ADDRPERM(fsroot),
		 cpu,
		 cpu_subtype));
	(void) vm_commpage_enter(new_map, task, is64bit);
	(void) vm_shared_region_enter(new_map, task, is64bit, fsroot, cpu, cpu_subtype);
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: task %p: vm_map_exec(%p,%p,%p,0x%x,0x%x): <-\n",
		 (void *)VM_KERNEL_ADDRPERM(current_task()),
		 (void *)VM_KERNEL_ADDRPERM(new_map),
		 (void *)VM_KERNEL_ADDRPERM(task),
		 (void *)VM_KERNEL_ADDRPERM(fsroot),
		 cpu,
		 cpu_subtype));
	return KERN_SUCCESS;
}