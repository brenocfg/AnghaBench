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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_context; scalar_t__ ip_strict_guard; } ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 scalar_t__ ipc_port_translate_receive (scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  kGUARD_EXC_SET_CONTEXT ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_set_context(
	ipc_space_t		space,
	mach_port_name_t	name,
	mach_vm_address_t	context)
{
	ipc_port_t port;
	kern_return_t kr;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(name))
		return KERN_INVALID_RIGHT;

	kr = ipc_port_translate_receive(space, name, &port);
	if (kr != KERN_SUCCESS)
		return kr;

	/* port is locked and active */
	if(port->ip_strict_guard) {
		uint64_t portguard = port->ip_context;
		ip_unlock(port);
		/* For strictly guarded ports, disallow overwriting context; Raise Exception */
		mach_port_guard_exception(name, context, portguard, kGUARD_EXC_SET_CONTEXT);
		return KERN_INVALID_ARGUMENT;
	}

	port->ip_context = context;

	ip_unlock(port);
	return KERN_SUCCESS;
}