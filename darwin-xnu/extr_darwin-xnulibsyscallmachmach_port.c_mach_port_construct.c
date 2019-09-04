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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_port_options_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_port_context_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;

/* Variables and functions */
 scalar_t__ MACH_SEND_INVALID_DEST ; 
 scalar_t__ _kernelrpc_mach_port_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _kernelrpc_mach_port_construct_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_construct(
	ipc_space_t		task,
	mach_port_options_t	*options,
	mach_port_context_t	context,
	mach_port_name_t	*name)
{
	kern_return_t rv;

	rv = _kernelrpc_mach_port_construct_trap(task, options, (uint64_t) context, name);

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_mach_port_construct(task, options, (uint64_t) context, name);

	return (rv);
}