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
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_port_context_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ _kernelrpc_mach_port_get_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

kern_return_t
mach_port_get_context(
	ipc_space_t task,
	mach_port_name_t name,
	mach_port_context_t *context)
{
	kern_return_t rv;
	mach_vm_address_t wide_context;

	rv = _kernelrpc_mach_port_get_context(task, name, &wide_context);

	if (rv == KERN_SUCCESS) {
		*context = (mach_port_context_t)wide_context;
	}

	return (rv);
}