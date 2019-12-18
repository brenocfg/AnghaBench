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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ memory_object_size_t ;
typedef  scalar_t__ memory_object_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  mach_make_memory_entry_64 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
_mach_make_memory_entry(
	vm_map_t		target_map,
	memory_object_size_t	*size,
	memory_object_offset_t	offset,
	vm_prot_t		permission,
	ipc_port_t		*object_handle,
	ipc_port_t		parent_entry)
{
	memory_object_size_t 	mo_size;
	kern_return_t		kr;
	
	mo_size = (memory_object_size_t)*size;
	kr = mach_make_memory_entry_64(target_map, &mo_size, 
			(memory_object_offset_t)offset, permission, object_handle,
			parent_entry);
	*size = mo_size;
	return kr;
}