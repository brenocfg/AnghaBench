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
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 scalar_t__ _kernelrpc_mach_vm_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _kernelrpc_mach_vm_protect_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_protect(
	mach_port_name_t task,
	mach_vm_address_t address,
	mach_vm_size_t size,
	boolean_t set_maximum,
	vm_prot_t new_protection)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_vm_protect_trap(task, address, size, set_maximum,
		new_protection);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_vm_protect(task, address, size,
			set_maximum, new_protection);

	return (rv);
}