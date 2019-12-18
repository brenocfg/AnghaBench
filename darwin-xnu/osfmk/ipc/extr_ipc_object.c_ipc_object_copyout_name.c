#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;
typedef  struct TYPE_19__   TYPE_17__ ;

/* Type definitions */
struct knote {int dummy; } ;
typedef  scalar_t__ mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  scalar_t__ ipc_importance_task_t ;
typedef  TYPE_3__* ipc_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_23__ {int ie_bits; scalar_t__ ie_object; } ;
struct TYPE_22__ {int ip_impcount; scalar_t__ ip_tempowner; } ;
struct TYPE_21__ {TYPE_18__* is_task; } ;
struct TYPE_20__ {scalar_t__ task_imp_base; } ;
struct TYPE_19__ {struct knote* ith_knote; } ;

/* Variables and functions */
 scalar_t__ IE_BITS_TYPE (int) ; 
 scalar_t__ IIT_NULL ; 
 scalar_t__ IOT_PORT ; 
 scalar_t__ IO_NULL ; 
 int IO_VALID (scalar_t__) ; 
 scalar_t__ ITH_KNOTE_VALID (struct knote*,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_INVALID_CAPABILITY ; 
 scalar_t__ KERN_NAME_EXISTS ; 
 scalar_t__ KERN_RIGHT_EXISTS ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_RECEIVE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND_ONCE ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 TYPE_18__* TASK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_17__* current_thread () ; 
 int /*<<< orphan*/  filt_machport_turnstile_prepare_lazily (struct knote*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  io_active (scalar_t__) ; 
 int /*<<< orphan*/  io_lock (scalar_t__) ; 
 scalar_t__ io_otype (scalar_t__) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 scalar_t__ ipc_entry_alloc_name (TYPE_1__*,scalar_t__,TYPE_3__**) ; 
 int /*<<< orphan*/  ipc_entry_dealloc (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_importance_task_hold_internal_assertion (scalar_t__,int) ; 
 scalar_t__ ipc_importance_task_is_any_receiver_type (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_reference (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_release (scalar_t__) ; 
 scalar_t__ ipc_right_copyout (TYPE_1__*,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ipc_right_inuse (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 scalar_t__ ipc_right_reverse (TYPE_1__*,scalar_t__,scalar_t__*,TYPE_3__**) ; 
 int /*<<< orphan*/  is_write_unlock (TYPE_1__*) ; 

kern_return_t
ipc_object_copyout_name(
	ipc_space_t		space,
	ipc_object_t		object,
	mach_msg_type_name_t	msgt_name,
	boolean_t		overflow,
	mach_port_name_t	name)
{
	mach_port_name_t oname;
	ipc_entry_t oentry;
	ipc_entry_t entry;
	kern_return_t kr;
	struct knote *kn = current_thread()->ith_knote;

#if IMPORTANCE_INHERITANCE
	int assertcnt = 0;
	ipc_importance_task_t task_imp = IIT_NULL;
#endif /* IMPORTANCE_INHERITANCE */

	assert(IO_VALID(object));
	assert(io_otype(object) == IOT_PORT);

	if (ITH_KNOTE_VALID(kn, msgt_name)) {
		filt_machport_turnstile_prepare_lazily(kn,
				msgt_name, (ipc_port_t)object);
	}

	kr = ipc_entry_alloc_name(space, name, &entry);
	if (kr != KERN_SUCCESS)
		return kr;
	/* space is write-locked and active */

	if ((msgt_name != MACH_MSG_TYPE_PORT_SEND_ONCE) &&
	    ipc_right_reverse(space, object, &oname, &oentry)) {
		/* object is locked and active */

		if (name != oname) {
			io_unlock(object);

			if (IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE)
				ipc_entry_dealloc(space, name, entry);

			is_write_unlock(space);
			return KERN_RIGHT_EXISTS;
		}

		assert(entry == oentry);
		assert(entry->ie_bits & MACH_PORT_TYPE_SEND_RECEIVE);
	} else {
		if (ipc_right_inuse(space, name, entry))
			return KERN_NAME_EXISTS;

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
	}

	/* space is write-locked and active, object is locked and active */

#if IMPORTANCE_INHERITANCE
	/*
	 * We are slamming a receive right into the space, without
	 * first having been enqueued on a port destined there.  So,
	 * we have to arrange to boost the task appropriately if this
	 * port has assertions (and the task wants them).
	 */
	if (msgt_name == MACH_MSG_TYPE_PORT_RECEIVE) {
		ipc_port_t port = (ipc_port_t)object;

		if (space->is_task != TASK_NULL) {
			task_imp = space->is_task->task_imp_base;
			if (ipc_importance_task_is_any_receiver_type(task_imp)) {
				assertcnt = port->ip_impcount;
				ipc_importance_task_reference(task_imp);
			} else {
				task_imp = IIT_NULL;
			}
		}

		/* take port out of limbo */
		assert(port->ip_tempowner != 0);
		port->ip_tempowner = 0;
	}

#endif /* IMPORTANCE_INHERITANCE */

	kr = ipc_right_copyout(space, name, entry,
			       msgt_name, overflow, object);

	/* object is unlocked */
	is_write_unlock(space);

#if IMPORTANCE_INHERITANCE
	/*
	 * Add the assertions to the task that we captured before
	 */
	if (task_imp != IIT_NULL) {
		ipc_importance_task_hold_internal_assertion(task_imp, assertcnt);
		ipc_importance_task_release(task_imp);
	}
#endif /* IMPORTANCE_INHERITANCE */

	return kr;
}