#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct knote {int dummy; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_1__* ipc_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {struct knote* ith_knote; } ;
struct TYPE_7__ {int ie_bits; scalar_t__ ie_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (scalar_t__) ; 
 scalar_t__ IE_BITS_TYPE (int) ; 
 scalar_t__ IOT_PORT ; 
 scalar_t__ IO_NULL ; 
 int IO_VALID (scalar_t__) ; 
 scalar_t__ ITH_KNOTE_VALID (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITS_SIZE_NONE ; 
 scalar_t__ KERN_INVALID_CAPABILITY ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND_ONCE ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* current_thread () ; 
 int /*<<< orphan*/  filt_machport_turnstile_prepare_lazily (struct knote*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_active (scalar_t__) ; 
 int /*<<< orphan*/  io_lock (scalar_t__) ; 
 scalar_t__ io_otype (scalar_t__) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_entry_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ipc_entry_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ ipc_entry_grow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_right_copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ipc_right_reverse (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_object_copyout(
	ipc_space_t		space,
	ipc_object_t		object,
	mach_msg_type_name_t	msgt_name,
	boolean_t		overflow,
	mach_port_name_t	*namep)
{
	struct knote *kn = current_thread()->ith_knote;
	mach_port_name_t name;
	ipc_entry_t entry;
	kern_return_t kr;

	assert(IO_VALID(object));
	assert(io_otype(object) == IOT_PORT);

	if (ITH_KNOTE_VALID(kn, msgt_name)) {
		filt_machport_turnstile_prepare_lazily(kn,
				msgt_name, (ipc_port_t)object);
	}

	is_write_lock(space);

	for (;;) {
		if (!is_active(space)) {
			is_write_unlock(space);
			return KERN_INVALID_TASK;
		}

		if ((msgt_name != MACH_MSG_TYPE_PORT_SEND_ONCE) &&
		    ipc_right_reverse(space, object, &name, &entry)) { 
			/* object is locked and active */

			assert(entry->ie_bits & MACH_PORT_TYPE_SEND_RECEIVE);
			break;
		}

		name = CAST_MACH_PORT_TO_NAME(object);
		kr = ipc_entry_get(space, &name, &entry);
		if (kr != KERN_SUCCESS) {
			/* unlocks/locks space, so must start again */

			kr = ipc_entry_grow_table(space, ITS_SIZE_NONE);
			if (kr != KERN_SUCCESS)
				return kr; /* space is unlocked */

			continue;
		}

		assert(IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE);
		assert(entry->ie_object == IO_NULL);

		io_lock(object);
		if (!io_active(object)) {
			io_unlock(object);
			ipc_entry_dealloc(space, name, entry);
			is_write_unlock(space);
			return KERN_INVALID_CAPABILITY;
		}

		entry->ie_object = object;
		break;
	}

	/* space is write-locked and active, object is locked and active */

	kr = ipc_right_copyout(space, name, entry,
			       msgt_name, overflow, object);

	/* object is unlocked */
	is_write_unlock(space);

	if (kr == KERN_SUCCESS)
		*namep = name;
	return kr;
}