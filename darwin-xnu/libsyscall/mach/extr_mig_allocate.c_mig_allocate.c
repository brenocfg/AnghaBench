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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_address_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int TRUE ; 
 int VM_MAKE_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MEMORY_MACH_MSG ; 
 int /*<<< orphan*/  mach_task_self_ ; 
 scalar_t__ vm_allocate (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 

void
mig_allocate(vm_address_t *addr_p, vm_size_t size)
{
	if (vm_allocate(mach_task_self_,
			addr_p,
			size,
			VM_MAKE_TAG(VM_MEMORY_MACH_MSG)|TRUE)
	    != KERN_SUCCESS)
		*addr_p = 0;
}