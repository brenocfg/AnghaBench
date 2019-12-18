#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  scalar_t__ ipc_pset_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  TYPE_1__* ipc_entry_t ;
struct TYPE_5__ {int ie_bits; scalar_t__ ie_object; } ;

/* Variables and functions */
 TYPE_1__* IE_NULL ; 
 scalar_t__ IPS_NULL ; 
 scalar_t__ IP_NULL ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_PORT_TYPE_PORT_SET ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAITQ_DONT_LOCK ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (scalar_t__) ; 
 int /*<<< orphan*/  ip_lock (scalar_t__) ; 
 int /*<<< orphan*/  ip_unlock (scalar_t__) ; 
 TYPE_1__* ipc_entry_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_pset_add (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ipc_pset_lazy_allocate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_pset_remove_from_all (scalar_t__) ; 
 scalar_t__ ipc_right_lookup_read (scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  ips_lock (scalar_t__) ; 
 int /*<<< orphan*/  ips_unlock (scalar_t__) ; 
 int /*<<< orphan*/  is_read_unlock (scalar_t__) ; 
 int /*<<< orphan*/  waitq_link_release (scalar_t__) ; 
 scalar_t__ waitq_link_reserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_prepost_release_reserve (scalar_t__) ; 
 scalar_t__ waitq_prepost_reserve (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_move_member(
	ipc_space_t		space,
	mach_port_name_t	member,
	mach_port_name_t	after)
{
	ipc_entry_t entry;
	ipc_port_t port;
	ipc_pset_t nset;
	kern_return_t kr;
	uint64_t wq_link_id = 0;
	uint64_t wq_reserved_prepost = 0;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	if (!MACH_PORT_VALID(member))
		return KERN_INVALID_RIGHT;

	if (after == MACH_PORT_DEAD) {
		return KERN_INVALID_RIGHT;
	} else if (after == MACH_PORT_NULL) {
		wq_link_id = 0;
	} else {
		/*
		 * We reserve both a link, and
		 * enough prepost objects to complete
		 * the set move atomically - we can't block
		 * while we're holding the space lock, and
		 * the ipc_pset_add calls ipc_mqueue_add
		 * which may have to prepost this port onto
		 * this set.
		 */
		wq_link_id = waitq_link_reserve(NULL);
		wq_reserved_prepost = waitq_prepost_reserve(NULL, 10,
		                                            WAITQ_DONT_LOCK);
		kr = ipc_pset_lazy_allocate(space, after);
		if (kr != KERN_SUCCESS)
			goto done;
	}

	kr = ipc_right_lookup_read(space, member, &entry);
	if (kr != KERN_SUCCESS)
		goto done;
	/* space is read-locked and active */

	if ((entry->ie_bits & MACH_PORT_TYPE_RECEIVE) == 0) {
		is_read_unlock(space);
		kr = KERN_INVALID_RIGHT;
		goto done;
	}

	__IGNORE_WCASTALIGN(port = (ipc_port_t) entry->ie_object);
	assert(port != IP_NULL);

	if (after == MACH_PORT_NULL)
		nset = IPS_NULL;
	else {
		entry = ipc_entry_lookup(space, after);
		if (entry == IE_NULL) {
			is_read_unlock(space);
			kr = KERN_INVALID_NAME;
			goto done;
		}

		if ((entry->ie_bits & MACH_PORT_TYPE_PORT_SET) == 0) {
			is_read_unlock(space);
			kr = KERN_INVALID_RIGHT;
			goto done;
		}

		__IGNORE_WCASTALIGN(nset = (ipc_pset_t) entry->ie_object);
		assert(nset != IPS_NULL);
	}
	ip_lock(port);
	assert(ip_active(port));
	ipc_pset_remove_from_all(port);

	if (nset != IPS_NULL) {
		ips_lock(nset);
		kr = ipc_pset_add(nset, port, &wq_link_id, &wq_reserved_prepost);
		ips_unlock(nset);
	}
	ip_unlock(port);
	is_read_unlock(space);

 done:

	/*
	 * on success the ipc_pset_add() will consume the wq_link_id
	 * value (resetting it to 0), so this function is always safe to call.
	 */
	waitq_link_release(wq_link_id);
	waitq_prepost_release_reserve(wq_reserved_prepost);

	return kr;
}