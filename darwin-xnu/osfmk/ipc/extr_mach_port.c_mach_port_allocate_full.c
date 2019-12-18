#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_t ;
typedef  int mach_port_right_t ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ name; scalar_t__ prealloc; } ;
typedef  TYPE_1__ mach_port_qos_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_msg_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_pset_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ ipc_kmsg_t ;

/* Variables and functions */
 scalar_t__ IKM_NULL ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MACH_MSG_SIZE_MAX ; 
 scalar_t__ MACH_PORT_NULL ; 
#define  MACH_PORT_RIGHT_DEAD_NAME 130 
#define  MACH_PORT_RIGHT_PORT_SET 129 
#define  MACH_PORT_RIGHT_RECEIVE 128 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_TRAILER_SIZE ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kmsg_free (scalar_t__) ; 
 scalar_t__ ipc_kmsg_prealloc (scalar_t__) ; 
 int /*<<< orphan*/  ipc_kmsg_set_prealloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_object_alloc_dead (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_alloc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_alloc_name (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_pset_alloc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_pset_alloc_name (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ips_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_allocate_full(
	ipc_space_t		space,
	mach_port_right_t	right,
	mach_port_t		proto,
	mach_port_qos_t		*qosp,
	mach_port_name_t	*namep)
{
	ipc_kmsg_t		kmsg = IKM_NULL;
	kern_return_t		kr;

	if (space == IS_NULL)
		return (KERN_INVALID_TASK);

	if (proto != MACH_PORT_NULL)
		return (KERN_INVALID_VALUE);

	if (qosp->name) {
		if (!MACH_PORT_VALID (*namep))
			return (KERN_INVALID_VALUE);
	}

	if (qosp->prealloc) {
		if (qosp->len > MACH_MSG_SIZE_MAX - MAX_TRAILER_SIZE) {
			return KERN_RESOURCE_SHORTAGE;
		} else {
			mach_msg_size_t size = qosp->len + MAX_TRAILER_SIZE;

			if (right != MACH_PORT_RIGHT_RECEIVE) {
				return (KERN_INVALID_VALUE);
			}

			kmsg = (ipc_kmsg_t)ipc_kmsg_prealloc(size);
			if (kmsg == IKM_NULL) {
				return (KERN_RESOURCE_SHORTAGE);
			}
		}
	}

	switch (right) {
	    case MACH_PORT_RIGHT_RECEIVE:
	    {
		ipc_port_t	port;

		if (qosp->name)
			kr = ipc_port_alloc_name(space, *namep, &port);
		else
			kr = ipc_port_alloc(space, namep, &port);
		if (kr == KERN_SUCCESS) {
			if (kmsg != IKM_NULL) 
				ipc_kmsg_set_prealloc(kmsg, port);

			ip_unlock(port);

		} else if (kmsg != IKM_NULL)
			ipc_kmsg_free(kmsg);
		break;
	    }

	    case MACH_PORT_RIGHT_PORT_SET:
	    {
		ipc_pset_t	pset;

		if (qosp->name)
			kr = ipc_pset_alloc_name(space, *namep, &pset);
		else
			kr = ipc_pset_alloc(space, namep, &pset);
		if (kr == KERN_SUCCESS)
			ips_unlock(pset);
		break;
	    }

	    case MACH_PORT_RIGHT_DEAD_NAME:
		kr = ipc_object_alloc_dead(space, namep);
		break;

	    default:
		kr = KERN_INVALID_VALUE;
		break;
	}

	return (kr);
}