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
typedef  int mach_port_urefs_t ;
typedef  int mach_port_type_t ;
typedef  int mach_port_right_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_entry_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_INVALID_VALUE ; 
 scalar_t__ KERN_SUCCESS ; 
#define  MACH_PORT_RIGHT_DEAD_NAME 132 
 int MACH_PORT_RIGHT_NUMBER ; 
#define  MACH_PORT_RIGHT_PORT_SET 131 
#define  MACH_PORT_RIGHT_RECEIVE 130 
#define  MACH_PORT_RIGHT_SEND 129 
#define  MACH_PORT_RIGHT_SEND_ONCE 128 
 int MACH_PORT_TYPE (int) ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ipc_right_info (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ipc_right_lookup_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_NAME ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

kern_return_t
mach_port_get_refs(
	ipc_space_t		space,
	mach_port_name_t	name,
	mach_port_right_t	right,
	mach_port_urefs_t	*urefsp)
{
	mach_port_type_t type;
	mach_port_urefs_t urefs;
	ipc_entry_t entry;
	kern_return_t kr;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (right >= MACH_PORT_RIGHT_NUMBER)
		return KERN_INVALID_VALUE;

	if (!MACH_PORT_VALID(name)) {
	  	if (right == MACH_PORT_RIGHT_SEND ||
		    right == MACH_PORT_RIGHT_SEND_ONCE) {
			*urefsp = 1;
			return KERN_SUCCESS;
		}
		return KERN_INVALID_NAME;
	}

	kr = ipc_right_lookup_write(space, name, &entry);
	if (kr != KERN_SUCCESS) {
		mach_port_guard_exception(name, 0, 0, kGUARD_EXC_INVALID_NAME);
		return kr;
	}

	/* space is write-locked and active */
	kr = ipc_right_info(space, name, entry, &type, &urefs);
	/* space is unlocked */

	if (kr != KERN_SUCCESS)
		return kr;	

	if (type & MACH_PORT_TYPE(right))
		switch (right) {
		    case MACH_PORT_RIGHT_SEND_ONCE:
			assert(urefs == 1);
			/* fall-through */

		    case MACH_PORT_RIGHT_PORT_SET:
		    case MACH_PORT_RIGHT_RECEIVE:
			*urefsp = 1;
			break;

		    case MACH_PORT_RIGHT_DEAD_NAME:
		    case MACH_PORT_RIGHT_SEND:
			assert(urefs > 0);
			*urefsp = urefs;
			break;

		    default:
			panic("mach_port_get_refs: strange rights");
		}
	else
		*urefsp = 0;

	return kr;
}