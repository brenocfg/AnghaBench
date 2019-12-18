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
typedef  scalar_t__ vm_purgable_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_PURGABLE_SET_STATE_FROM_KERNEL ; 
 int /*<<< orphan*/  memory_entry_purgeable_control_internal (int /*<<< orphan*/ ,scalar_t__,int*) ; 

kern_return_t
mach_memory_entry_purgable_control(
	ipc_port_t	entry_port,
	vm_purgable_t	control,
	int		*state)
{
	if (control == VM_PURGABLE_SET_STATE_FROM_KERNEL) {
		/* not allowed from user-space */
		return KERN_INVALID_ARGUMENT;
	}

	return memory_entry_purgeable_control_internal(entry_port, control, state);
}