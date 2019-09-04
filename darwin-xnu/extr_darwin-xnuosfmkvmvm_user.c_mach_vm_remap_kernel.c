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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_inherit_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int VM_FLAGS_USER_REMAP ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_remap (scalar_t__,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_remap_kernel(
	vm_map_t		target_map,
	mach_vm_offset_t	*address,
	mach_vm_size_t	size,
	mach_vm_offset_t	mask,
	int			flags,
	vm_tag_t		tag,
	vm_map_t		src_map,
	mach_vm_offset_t	memory_address,
	boolean_t		copy,
	vm_prot_t		*cur_protection,
	vm_prot_t		*max_protection,
	vm_inherit_t		inheritance)
{
	vm_map_offset_t		map_addr;
	kern_return_t		kr;

	if (VM_MAP_NULL == target_map || VM_MAP_NULL == src_map)
		return KERN_INVALID_ARGUMENT;

	/* filter out any kernel-only flags */
	if (flags & ~VM_FLAGS_USER_REMAP)
		return KERN_INVALID_ARGUMENT;

	map_addr = (vm_map_offset_t)*address;

	kr = vm_map_remap(target_map,
			  &map_addr,
			  size,
			  mask,
			  flags,
			  VM_MAP_KERNEL_FLAGS_NONE,
			  tag,
			  src_map,
			  memory_address,
			  copy,
			  cur_protection,
			  max_protection,
			  inheritance);
	*address = map_addr;
	return kr;
}