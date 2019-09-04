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
typedef  int /*<<< orphan*/  vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  vm_address_t ;
typedef  size_t uint_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  size_t mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  itk_space; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ fileport_invoke (TYPE_1__*,int /*<<< orphan*/ ,int (*) (mach_port_name_t,struct fileglob*,void*),void*,int*) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 scalar_t__ mach_port_names (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vm_map_copy_discard (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyout (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

kern_return_t
fileport_walk(task_t task,
	int (*action)(mach_port_name_t, struct fileglob *, void *arg),
	void *arg)
{
	mach_port_name_t *names;
	mach_msg_type_number_t ncnt, tcnt;
	vm_map_copy_t map_copy_names, map_copy_types;
	vm_map_address_t map_names;
	kern_return_t kr;
	uint_t i;
	int rval;

	/*
	 * mach_port_names returns the 'name' and 'types' in copied-in
	 * form.  Discard 'types' immediately, then copyout 'names'
	 * back into the kernel before walking the array.
	 */

	kr = mach_port_names(task->itk_space,
	    (mach_port_name_t **)&map_copy_names, &ncnt,
	    (mach_port_type_t **)&map_copy_types, &tcnt);
	if (kr != KERN_SUCCESS)
		return (kr);

	vm_map_copy_discard(map_copy_types);

	kr = vm_map_copyout(ipc_kernel_map, &map_names, map_copy_names);
	if (kr != KERN_SUCCESS) {
		vm_map_copy_discard(map_copy_names);
		return (kr);
	}
	names = (mach_port_name_t *)(uintptr_t)map_names;

	for (rval = 0, i = 0; i < ncnt; i++)
		if (fileport_invoke(task, names[i], action, arg,
		    &rval) == KERN_SUCCESS && -1 == rval)
			break;		/* early termination clause */

	vm_deallocate(ipc_kernel_map,
	    (vm_address_t)names, ncnt * sizeof (*names));
	return (KERN_SUCCESS);
}