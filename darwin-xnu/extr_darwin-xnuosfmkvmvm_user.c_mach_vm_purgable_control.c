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
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 scalar_t__ VM_MAP_NULL ; 
 scalar_t__ VM_PURGABLE_SET_STATE_FROM_KERNEL ; 
 int /*<<< orphan*/  vm_map_purgable_control (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  vm_map_trunc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_purgable_control(
	vm_map_t		map,
	mach_vm_offset_t	address,
	vm_purgable_t		control,
	int			*state)
{
	if (VM_MAP_NULL == map)
		return KERN_INVALID_ARGUMENT;

	if (control == VM_PURGABLE_SET_STATE_FROM_KERNEL) {
		/* not allowed from user-space */
		return KERN_INVALID_ARGUMENT;
	}

	return vm_map_purgable_control(map,
				       vm_map_trunc_page(address, PAGE_MASK),
				       control,
				       state);
}