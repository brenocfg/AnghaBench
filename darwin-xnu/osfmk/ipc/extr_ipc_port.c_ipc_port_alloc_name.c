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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOT_PORT ; 
 int IP_CALLSTACK_MAX ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_TYPE_RECEIVE ; 
 scalar_t__ ipc_object_alloc_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_callstack_init_debug (uintptr_t*,int) ; 
 int /*<<< orphan*/  ipc_port_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_init_debug (scalar_t__,uintptr_t*,int) ; 

kern_return_t
ipc_port_alloc_name(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_port_t		*portp)
{
	ipc_port_t port;
	kern_return_t kr;

#if     MACH_ASSERT
	uintptr_t buf[IP_CALLSTACK_MAX];
	ipc_port_callstack_init_debug(&buf[0], IP_CALLSTACK_MAX);
#endif /* MACH_ASSERT */	

	kr = ipc_object_alloc_name(space, IOT_PORT,
				   MACH_PORT_TYPE_RECEIVE, 0,
				   name, (ipc_object_t *) &port);
	if (kr != KERN_SUCCESS)
		return kr;

	/* port is locked */

	ipc_port_init(port, space, name);

#if     MACH_ASSERT
	ipc_port_init_debug(port, &buf[0], IP_CALLSTACK_MAX);
#endif  /* MACH_ASSERT */	

	*portp = port;

	return KERN_SUCCESS;
}