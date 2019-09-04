#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int ipc_entry_bits_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {int ie_bits; scalar_t__ ie_object; int /*<<< orphan*/  ie_request; } ;
struct TYPE_11__ {scalar_t__ ip_srights; scalar_t__ ip_sorights; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IE_BITS_TYPE (int) ; 
 int IE_BITS_TYPE_MASK ; 
 int IE_BITS_UREFS (int) ; 
 int /*<<< orphan*/  IE_REQ_NONE ; 
 scalar_t__ IO_NULL ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND ; 
 int MACH_PORT_TYPE_SEND_ONCE ; 
 int MACH_PORT_UREFS_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_entry_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ipc_port_request_type (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_active (int /*<<< orphan*/ ) ; 

boolean_t
ipc_right_check(
	ipc_space_t		space,
	ipc_port_t		port,
	mach_port_name_t	name,
	ipc_entry_t		entry)
{
	ipc_entry_bits_t bits;

	assert(is_active(space));
	assert(port == (ipc_port_t) entry->ie_object);

	ip_lock(port);
	if (ip_active(port))
		return FALSE;

	/* this was either a pure send right or a send-once right */

	bits = entry->ie_bits;
	assert((bits & MACH_PORT_TYPE_RECEIVE) == 0);
	assert(IE_BITS_UREFS(bits) > 0);

	if (bits & MACH_PORT_TYPE_SEND) {
                assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND);
		assert(IE_BITS_UREFS(bits) > 0);
		assert(port->ip_srights > 0);
		port->ip_srights--;
        } else {
                assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND_ONCE);
                assert(IE_BITS_UREFS(bits) == 1);
		assert(port->ip_sorights > 0);
		port->ip_sorights--;
        }
	ip_unlock(port);

	/*
	 * delete SEND rights from ipc hash.
	 */

	if ((bits & MACH_PORT_TYPE_SEND) != 0) {
		ipc_hash_delete(space, (ipc_object_t)port, name, entry);
	}

	/* convert entry to dead name */
	bits = (bits &~ IE_BITS_TYPE_MASK) | MACH_PORT_TYPE_DEAD_NAME;
	
	/*
	 * If there was a notification request outstanding on this
	 * name, and the port went dead, that notification
	 * must already be on its way up from the port layer.
	 *
	 * Add the reference that the notification carries. It
	 * is done here, and not in the notification delivery,
	 * because the latter doesn't have a space reference and
	 * trying to actually move a send-right reference would
	 * get short-circuited into a MACH_PORT_DEAD by IPC. Since
	 * all calls that deal with the right eventually come
	 * through here, it has the same result.
	 *
	 * Once done, clear the request index so we only account
	 * for it once.
	 */
	if (entry->ie_request != IE_REQ_NONE) {
		if (ipc_port_request_type(port, name, entry->ie_request) != 0) {
			/* if urefs are pegged due to overflow, leave them pegged */
			if (IE_BITS_UREFS(bits) < MACH_PORT_UREFS_MAX)
				bits++; /* increment urefs */
		}
		entry->ie_request = IE_REQ_NONE; 
	}
	entry->ie_bits = bits;
	entry->ie_object = IO_NULL;
	ipc_entry_modified(space, name, entry);
	return TRUE;
}