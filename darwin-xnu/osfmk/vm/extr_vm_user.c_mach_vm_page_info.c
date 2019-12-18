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
typedef  int /*<<< orphan*/  vm_page_info_t ;
typedef  int /*<<< orphan*/  vm_page_info_flavor_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_page_info (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_vm_page_info(
	vm_map_t		map,
	mach_vm_address_t	address,
	vm_page_info_flavor_t	flavor,
	vm_page_info_t		info,
	mach_msg_type_number_t	*count)
{
	kern_return_t	kr;

	if (map == VM_MAP_NULL) {
		return KERN_INVALID_ARGUMENT;
	}

	kr = vm_map_page_info(map, address, flavor, info, count);
	return kr;
}