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
typedef  int /*<<< orphan*/  mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_INVALID_CAPABILITY ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_IPC_KERNEL ; 
 int /*<<< orphan*/  MACH_MSG_IPC_SPACE ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ipc_object_copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_object_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mach_msg_return_t
ipc_kmsg_copyout_object(
	ipc_space_t		space,
	ipc_object_t		object,
	mach_msg_type_name_t	msgt_name,
	mach_port_name_t	*namep)
{
	kern_return_t kr;

	if (!IO_VALID(object)) {
		*namep = CAST_MACH_PORT_TO_NAME(object);
		return MACH_MSG_SUCCESS;
	}

	kr = ipc_object_copyout(space, object, msgt_name, TRUE, namep);
	if (kr != KERN_SUCCESS) {
		ipc_object_destroy(object, msgt_name);

		if (kr == KERN_INVALID_CAPABILITY)
			*namep = MACH_PORT_DEAD;
		else {
			*namep = MACH_PORT_NULL;

			if (kr == KERN_RESOURCE_SHORTAGE)
				return MACH_MSG_IPC_KERNEL;
			else
				return MACH_MSG_IPC_SPACE;
		}
	}

	return MACH_MSG_SUCCESS;
}