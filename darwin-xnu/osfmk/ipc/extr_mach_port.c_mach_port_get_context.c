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
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_context; scalar_t__ ip_strict_guard; } ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 scalar_t__ ipc_port_translate_receive (scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 

kern_return_t
mach_port_get_context(
	ipc_space_t		space,
	mach_port_name_t	name,
	mach_vm_address_t	*context)
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

	/* Port locked and active */

	/* For strictly guarded ports, return empty context (which acts as guard) */
	if (port->ip_strict_guard)
		*context = 0;
	else
		*context = port->ip_context;

	ip_unlock(port);
	return KERN_SUCCESS;
}