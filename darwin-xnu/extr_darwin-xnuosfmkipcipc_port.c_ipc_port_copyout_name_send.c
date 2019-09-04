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
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (scalar_t__) ; 
 scalar_t__ IP_VALID (scalar_t__) ; 
 scalar_t__ KERN_INVALID_CAPABILITY ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ipc_object_copyout_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 

mach_port_name_t
ipc_port_copyout_name_send(
	ipc_port_t	sright,
	ipc_space_t	space,
	mach_port_name_t name)
{
	if (IP_VALID(sright)) {
		kern_return_t kr;

		kr = ipc_object_copyout_name(space, (ipc_object_t) sright,
					MACH_MSG_TYPE_PORT_SEND, TRUE, name);
		if (kr != KERN_SUCCESS) {
			ipc_port_release_send(sright);

			if (kr == KERN_INVALID_CAPABILITY)
				name = MACH_PORT_DEAD;
			else
				name = MACH_PORT_NULL;
		}
	} else
		name = CAST_MACH_PORT_TO_NAME(sright);

	return name;
}