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
typedef  scalar_t__ vm_prot_t ;
typedef  scalar_t__ vm_inherit_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  scalar_t__ mem_entry_name_port_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int VM_FLAGS_ALIAS_MASK ; 
 scalar_t__ VM_INHERIT_DEFAULT ; 
 scalar_t__ VM_PROT_ALL ; 
 int /*<<< orphan*/  __syscall_logger (int,uintptr_t,uintptr_t,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ _kernelrpc_mach_vm_map (scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ _kernelrpc_mach_vm_map_trap (scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int stack_logging_type_mapped_file_or_shared_mem ; 
 int stack_logging_type_vm_allocate ; 

kern_return_t
mach_vm_map(
	mach_port_name_t target,
	mach_vm_address_t *address,
	mach_vm_size_t size,
	mach_vm_offset_t mask,
	int flags,
	mem_entry_name_port_t object,
	memory_object_offset_t offset,
	boolean_t copy,
	vm_prot_t cur_protection,
	vm_prot_t max_protection,
	vm_inherit_t inheritance)
{
	kern_return_t rv = MACH_SEND_INVALID_DEST;

	if (object == MEMORY_OBJECT_NULL && max_protection == VM_PROT_ALL &&
			inheritance == VM_INHERIT_DEFAULT)
		rv = _kernelrpc_mach_vm_map_trap(target, address, size, mask, flags,
				cur_protection);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_vm_map(target, address, size, mask, flags, object,
			offset, copy, cur_protection, max_protection, inheritance);

	if (__syscall_logger) {
		int eventTypeFlags = stack_logging_type_vm_allocate | stack_logging_type_mapped_file_or_shared_mem;
		int userTagFlags = flags & VM_FLAGS_ALIAS_MASK;
		__syscall_logger(eventTypeFlags | userTagFlags, (uintptr_t)target, (uintptr_t)size, 0, (uintptr_t)*address, 0);
	}

	return (rv);
}