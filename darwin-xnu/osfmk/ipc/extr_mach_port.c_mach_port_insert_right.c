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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_CAPABILITY ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_ANY_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_object_copyout_name (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_insert_right(
	ipc_space_t			space,
	mach_port_name_t		name,
	ipc_port_t			poly,
	mach_msg_type_name_t		polyPoly)
{
	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(name) ||
	    !MACH_MSG_TYPE_PORT_ANY_RIGHT(polyPoly))
		return KERN_INVALID_VALUE;

	if (!IO_VALID((ipc_object_t) poly))
		return KERN_INVALID_CAPABILITY;

	return ipc_object_copyout_name(space, (ipc_object_t) poly, 
				       polyPoly, FALSE, name);
}