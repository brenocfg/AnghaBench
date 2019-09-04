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
typedef  int /*<<< orphan*/  vm_region_info_t ;
typedef  int /*<<< orphan*/  vm_region_flavor_t ;
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_REGION_BASIC_INFO ; 
 int /*<<< orphan*/  VM_REGION_BASIC_INFO_64 ; 
 int /*<<< orphan*/  vm_map_region (scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
mach_vm_region(
	vm_map_t		 map,
	mach_vm_offset_t	*address,		/* IN/OUT */
	mach_vm_size_t	*size,			/* OUT */
	vm_region_flavor_t	 flavor,		/* IN */
	vm_region_info_t	 info,			/* OUT */
	mach_msg_type_number_t	*count,			/* IN/OUT */
	mach_port_t		*object_name)		/* OUT */
{
	vm_map_offset_t 	map_addr;
	vm_map_size_t 		map_size;
	kern_return_t		kr;

	if (VM_MAP_NULL == map)
		return KERN_INVALID_ARGUMENT;

	map_addr = (vm_map_offset_t)*address;
	map_size = (vm_map_size_t)*size;

	/* legacy conversion */
	if (VM_REGION_BASIC_INFO == flavor)
		flavor = VM_REGION_BASIC_INFO_64;

	kr = vm_map_region(map,
			   &map_addr, &map_size,
			   flavor, info, count,
			   object_name);

	*address = map_addr;
	*size = map_size;
	return kr;
}