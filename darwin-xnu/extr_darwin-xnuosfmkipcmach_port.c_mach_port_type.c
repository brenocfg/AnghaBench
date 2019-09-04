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
typedef  int /*<<< orphan*/  mach_port_urefs_t ;
typedef  int mach_port_type_t ;
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_entry_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_PORT_DEAD ; 
 scalar_t__ MACH_PORT_NULL ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_SPREQUEST ; 
 int MACH_PORT_TYPE_SPREQUEST_DELAYED ; 
 scalar_t__ ipc_right_info (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_right_lookup_write (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_NAME ; 
 int /*<<< orphan*/  mach_port_guard_exception (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_type(
	ipc_space_t		space,
	mach_port_name_t	name,
	mach_port_type_t	*typep)
{
	mach_port_urefs_t urefs;
	ipc_entry_t entry;
	kern_return_t kr;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (name == MACH_PORT_NULL)
		return KERN_INVALID_NAME;

	if (name == MACH_PORT_DEAD) {
		*typep = MACH_PORT_TYPE_DEAD_NAME;
		return KERN_SUCCESS;
	}

	kr = ipc_right_lookup_write(space, name, &entry);
	if (kr != KERN_SUCCESS) {
		mach_port_guard_exception(name, 0, 0, kGUARD_EXC_INVALID_NAME);
		return kr;
	}

	/* space is write-locked and active */
	kr = ipc_right_info(space, name, entry, typep, &urefs);
	/* space is unlocked */

#if 1
        /* JMM - workaround rdar://problem/9121297 (CF being too picky on these bits). */
        *typep &= ~(MACH_PORT_TYPE_SPREQUEST | MACH_PORT_TYPE_SPREQUEST_DELAYED);
#endif

	return kr;
}