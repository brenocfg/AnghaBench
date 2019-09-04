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
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  vm_machine_attribute_val_t ;
typedef  int /*<<< orphan*/  vm_machine_attribute_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_machine_attribute (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_machine_attribute(
	vm_map_t			map,
	mach_vm_address_t		addr,
	mach_vm_size_t		size,
	vm_machine_attribute_t	attribute,
	vm_machine_attribute_val_t* value)		/* IN/OUT */
{
	if ((map == VM_MAP_NULL) || (addr + size < addr))
		return(KERN_INVALID_ARGUMENT);

	if (size == 0)
		return KERN_SUCCESS;

	return vm_map_machine_attribute(
		map, 
		vm_map_trunc_page(addr,
				  VM_MAP_PAGE_MASK(map)),
		vm_map_round_page(addr+size,
				  VM_MAP_PAGE_MASK(map)),
		attribute,
		value);
}