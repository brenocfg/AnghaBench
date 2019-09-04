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
typedef  int /*<<< orphan*/  mach_port_right_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_1__* ipc_entry_t ;
struct TYPE_4__ {int ie_bits; scalar_t__ ie_object; } ;

/* Variables and functions */
 scalar_t__ IO_NULL ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_PORT_TYPE (int /*<<< orphan*/ ) ; 
 int MACH_PORT_TYPE_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  io_lock (scalar_t__) ; 
 scalar_t__ ipc_right_lookup_two_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  is_read_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_RIGHT ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
ipc_object_translate_two(
	ipc_space_t		space,
	mach_port_name_t	name1,
	mach_port_right_t	right1,
	ipc_object_t		*objectp1,
	mach_port_name_t	name2,
	mach_port_right_t	right2,
	ipc_object_t		*objectp2)
{
	ipc_entry_t entry1;
	ipc_entry_t entry2;
	ipc_object_t object;
	kern_return_t kr;

	kr = ipc_right_lookup_two_read(space, name1, &entry1, name2, &entry2);
	if (kr != KERN_SUCCESS)
		return kr;
	/* space is read-locked and active */

	if ((entry1->ie_bits & MACH_PORT_TYPE(right1)) == MACH_PORT_TYPE_NONE) {
		is_read_unlock(space);
		mach_port_guard_exception(name1, 0, 0, kGUARD_EXC_INVALID_RIGHT);
		return KERN_INVALID_RIGHT;
	}

	if ((entry2->ie_bits & MACH_PORT_TYPE(right2)) == MACH_PORT_TYPE_NONE) {
		is_read_unlock(space);
		mach_port_guard_exception(name2, 0, 0, kGUARD_EXC_INVALID_RIGHT);
		return KERN_INVALID_RIGHT;
	}

	object = entry1->ie_object;
	assert(object != IO_NULL);
	io_lock(object);
	*objectp1 = object;

	object = entry2->ie_object;
	assert(object != IO_NULL);
	io_lock(object);
	*objectp2 = object;

	is_read_unlock(space);
	return KERN_SUCCESS;
}