#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_map_kernel_flags_t ;
typedef  int /*<<< orphan*/  vm_inherit_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ pmap; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 int VM_FLAGS_USER_MAP ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ vm_map_enter_mem_object (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_map_kernel(
	vm_map_t		target_map,
	mach_vm_offset_t	*address,
	mach_vm_size_t	initial_size,
	mach_vm_offset_t	mask,
	int			flags,
	vm_map_kernel_flags_t	vmk_flags,
	vm_tag_t		tag,
	ipc_port_t		port,
	vm_object_offset_t	offset,
	boolean_t		copy,
	vm_prot_t		cur_protection,
	vm_prot_t		max_protection,
	vm_inherit_t		inheritance)
{
	kern_return_t		kr;
	vm_map_offset_t 	vmmaddr;

	vmmaddr = (vm_map_offset_t) *address;

	/* filter out any kernel-only flags */
	if (flags & ~VM_FLAGS_USER_MAP)
		return KERN_INVALID_ARGUMENT;

	kr = vm_map_enter_mem_object(target_map,
				     &vmmaddr,
				     initial_size,
				     mask,
				     flags,
				     vmk_flags,
				     tag,
				     port,
				     offset,
				     copy,
				     cur_protection,
				     max_protection,
				     inheritance);

#if KASAN
	if (kr == KERN_SUCCESS && target_map->pmap == kernel_pmap) {
		kasan_notify_address(vmmaddr, initial_size);
	}
#endif

	*address = vmmaddr;
	return kr;
}