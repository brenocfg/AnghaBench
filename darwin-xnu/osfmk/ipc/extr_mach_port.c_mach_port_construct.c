#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  mpl; } ;
typedef  TYPE_1__ mach_port_options_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/ * mach_port_info_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
struct TYPE_9__ {scalar_t__ ip_context; } ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND ; 
 int /*<<< orphan*/  MACH_PORT_DENAP_RECEIVER ; 
 int /*<<< orphan*/  MACH_PORT_IMPORTANCE_RECEIVER ; 
 int /*<<< orphan*/  MACH_PORT_LIMITS_INFO ; 
 int /*<<< orphan*/  MACH_PORT_TEMPOWNER ; 
 int MPO_CONTEXT_AS_GUARD ; 
 int MPO_DENAP_RECEIVER ; 
 int MPO_IMPORTANCE_RECEIVER ; 
 int MPO_INSERT_SEND_RIGHT ; 
 int MPO_QLIMIT ; 
 int MPO_STRICT ; 
 int MPO_TEMPOWNER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 scalar_t__ ipc_object_copyin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_port_alloc (scalar_t__,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  mach_port_destruct (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mach_port_guard_locked (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ mach_port_insert_right (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_port_set_attributes (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

kern_return_t
mach_port_construct(
	ipc_space_t		space,
	mach_port_options_t	*options,
	uint64_t		context,
	mach_port_name_t	*name)
{
	kern_return_t		kr;
	ipc_port_t		port;

	if (space == IS_NULL)
		return (KERN_INVALID_TASK);

	/* Allocate a new port in the IPC space */
	kr = ipc_port_alloc(space, name, &port);
	if (kr != KERN_SUCCESS)
		return kr;
	
	/* Port locked and active */
	if (options->flags & MPO_CONTEXT_AS_GUARD) {
		kr = mach_port_guard_locked(port, (uint64_t) context, (options->flags & MPO_STRICT));
		/* A newly allocated and locked port should always be guarded successfully */
		assert(kr == KERN_SUCCESS);
	} else {
		port->ip_context = context;
	}
	
	/* Unlock port */
	ip_unlock(port);

	/* Set port attributes as requested */

	if (options->flags & MPO_QLIMIT) {
		kr = mach_port_set_attributes(space, *name, MACH_PORT_LIMITS_INFO,
					      (mach_port_info_t)&options->mpl, sizeof(options->mpl)/sizeof(int));
		if (kr != KERN_SUCCESS)
			goto cleanup;	
	}

	if (options->flags & MPO_TEMPOWNER) {
		kr = mach_port_set_attributes(space, *name, MACH_PORT_TEMPOWNER, NULL, 0);
		if (kr != KERN_SUCCESS)
			goto cleanup;
	}

	if (options->flags & MPO_IMPORTANCE_RECEIVER) {
		kr = mach_port_set_attributes(space, *name, MACH_PORT_IMPORTANCE_RECEIVER, NULL, 0);
		if (kr != KERN_SUCCESS)
			goto cleanup;
	}

	if (options->flags & MPO_DENAP_RECEIVER) {
		kr = mach_port_set_attributes(space, *name, MACH_PORT_DENAP_RECEIVER, NULL, 0);
		if (kr != KERN_SUCCESS)
			goto cleanup;
	}

	if (options->flags & MPO_INSERT_SEND_RIGHT) {
		kr = ipc_object_copyin(space, *name, MACH_MSG_TYPE_MAKE_SEND, (ipc_object_t *)&port);
		if (kr != KERN_SUCCESS)
			goto cleanup;

		kr = mach_port_insert_right(space, *name, port, MACH_MSG_TYPE_PORT_SEND);
		if (kr != KERN_SUCCESS)
			goto cleanup;
	}

	return KERN_SUCCESS;

cleanup:
	/* Attempt to destroy port. If its already destroyed by some other thread, we're done */
	(void) mach_port_destruct(space, *name, 0, context);
	return kr;
}