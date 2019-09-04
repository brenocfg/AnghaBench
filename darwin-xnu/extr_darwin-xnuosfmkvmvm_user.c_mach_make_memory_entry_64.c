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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  memory_object_size_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int MAP_MEM_FLAGS_MASK ; 
 int MAP_MEM_FLAGS_USER ; 
 int /*<<< orphan*/  mach_make_memory_entry_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
mach_make_memory_entry_64(
	vm_map_t		target_map,
	memory_object_size_t	*size,
	memory_object_offset_t offset,
	vm_prot_t		permission,
	ipc_port_t		*object_handle,
	ipc_port_t		parent_handle)
{
	if ((permission & MAP_MEM_FLAGS_MASK) & ~MAP_MEM_FLAGS_USER) {
		/*
		 * Unknown flag: reject for forward compatibility.
		 */
		return KERN_INVALID_VALUE;
	}

	return mach_make_memory_entry_internal(target_map,
					       size,
					       offset,
					       permission,
					       object_handle,
					       parent_handle);
}