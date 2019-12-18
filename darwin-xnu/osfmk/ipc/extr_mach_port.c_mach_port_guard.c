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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_translate_receive (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_NAME ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_RIGHT ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_port_guard_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_guard(
	ipc_space_t		space,
	mach_port_name_t	name,
	uint64_t		guard,
	boolean_t		strict)
{
	kern_return_t		kr;
	ipc_port_t		port;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(name))
		return KERN_INVALID_NAME;

	/* Guard can be applied only to receive rights */
	kr = ipc_port_translate_receive(space, name, &port);
	if (kr != KERN_SUCCESS) {
		mach_port_guard_exception(name, 0, 0,
		                          ((KERN_INVALID_NAME == kr) ?
		                           kGUARD_EXC_INVALID_NAME :
		                           kGUARD_EXC_INVALID_RIGHT));
		return kr;
	}

	/* Port locked and active */
	kr = mach_port_guard_locked(port, guard, strict);
	ip_unlock(port);

	if (KERN_INVALID_ARGUMENT == kr) {
		mach_port_guard_exception(name, 0, 0, kGUARD_EXC_INVALID_ARGUMENT);
	}

	return kr;
}