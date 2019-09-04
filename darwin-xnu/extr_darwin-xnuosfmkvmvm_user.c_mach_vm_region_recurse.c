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
typedef  int /*<<< orphan*/  vm_region_submap_info_64_t ;
typedef  scalar_t__ vm_region_recurse_info_t ;
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_region_recurse_64 (scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_vm_region_recurse(
	vm_map_t			map,
	mach_vm_address_t		*address,
	mach_vm_size_t		*size,
	uint32_t			*depth,
	vm_region_recurse_info_t	info,
	mach_msg_type_number_t 	*infoCnt)
{
	vm_map_address_t	map_addr;
	vm_map_size_t		map_size;
	kern_return_t		kr;

	if (VM_MAP_NULL == map)
		return KERN_INVALID_ARGUMENT;

	map_addr = (vm_map_address_t)*address;
	map_size = (vm_map_size_t)*size;

	kr = vm_map_region_recurse_64(
			map,
			&map_addr,
			&map_size,
			depth,
			(vm_region_submap_info_64_t)info,
			infoCnt);

	*address = map_addr;
	*size = map_size;
	return kr;
}