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
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 int VM_FLAGS_ALIAS_MASK ; 
 int /*<<< orphan*/  __syscall_logger (int,uintptr_t,uintptr_t,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ _kernelrpc_mach_vm_allocate (scalar_t__,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ _kernelrpc_mach_vm_allocate_trap (scalar_t__,scalar_t__*,scalar_t__,int) ; 
 int stack_logging_type_vm_allocate ; 

kern_return_t
mach_vm_allocate(
	mach_port_name_t target,
	mach_vm_address_t *address,
	mach_vm_size_t size,
	int flags)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_vm_allocate_trap(target, address, size, flags);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_vm_allocate(target, address, size, flags);

	if (__syscall_logger) {
		int userTagFlags = flags & VM_FLAGS_ALIAS_MASK;
		__syscall_logger(stack_logging_type_vm_allocate | userTagFlags, (uintptr_t)target, (uintptr_t)size, 0, (uintptr_t)*address, 0);
	}

	return (rv);
}