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
typedef  int /*<<< orphan*/  vm_purgable_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 scalar_t__ _kernelrpc_mach_vm_purgable_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ _kernelrpc_mach_vm_purgable_control_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

kern_return_t
mach_vm_purgable_control(
	mach_port_name_t	target,
	mach_vm_offset_t	address,
	vm_purgable_t		control,
	int			*state)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_vm_purgable_control_trap(target, address, control, state);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_vm_purgable_control(target, address, control, state);

	return (rv);
}