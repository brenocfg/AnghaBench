#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ mach_port_urefs_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_port_mscount_t ;
typedef  scalar_t__ mach_port_delta_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int ipc_entry_bits_t ;
struct TYPE_19__ {int ie_bits; void* ie_object; scalar_t__ ie_request; } ;
struct TYPE_18__ {scalar_t__ ip_receiver; scalar_t__ ip_context; scalar_t__ ip_srights; int /*<<< orphan*/ * ip_pdrequest; int /*<<< orphan*/  ip_mscount; struct TYPE_18__* ip_nsrequest; scalar_t__ ip_guarded; int /*<<< orphan*/  ip_receiver_name; } ;

/* Variables and functions */
 int IE_BITS_TYPE (int) ; 
 int IE_BITS_TYPE_MASK ; 
 scalar_t__ IE_BITS_UREFS (int) ; 
 int IE_BITS_UREFS_MASK ; 
 scalar_t__ IE_REQ_NONE ; 
 void* IO_NULL ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 scalar_t__ MACH_PORT_UREFS_MAX ; 
 scalar_t__ MACH_PORT_UREFS_UNDERFLOW (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_entry_dealloc (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_entry_modified (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_insert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_notify_no_senders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_port_deleted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_1__*) ; 
 TYPE_1__* ipc_right_request_cancel_macro (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int is_active (scalar_t__) ; 
 int /*<<< orphan*/  is_write_unlock (scalar_t__) ; 
 int /*<<< orphan*/  kGUARD_EXC_DESTROY ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_RIGHT ; 
 int /*<<< orphan*/  kGUARD_EXC_INVALID_VALUE ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
ipc_right_destruct(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry,
	mach_port_delta_t	srdelta,
	uint64_t		guard)
{
	ipc_port_t port = IP_NULL;
	ipc_entry_bits_t bits;

	mach_port_urefs_t urefs;
	ipc_port_t request = IP_NULL;
	ipc_port_t nsrequest = IP_NULL;
	mach_port_mscount_t mscount = 0;

	bits = entry->ie_bits;

	assert(is_active(space));

	if (((bits & MACH_PORT_TYPE_RECEIVE) == 0) ||
	    (srdelta && ((bits & MACH_PORT_TYPE_SEND) == 0))) {
		is_write_unlock(space);
		mach_port_guard_exception(name, 0, 0, kGUARD_EXC_INVALID_RIGHT);
		return KERN_INVALID_RIGHT;
	}

	if (srdelta > 0)
		goto invalid_value;

	port = (ipc_port_t) entry->ie_object;
	assert(port != IP_NULL);

	ip_lock(port);
	assert(ip_active(port));
	assert(port->ip_receiver_name == name);
	assert(port->ip_receiver == space);

	/* Mach Port Guard Checking */
	if(port->ip_guarded && (guard != port->ip_context)) {
		uint64_t portguard = port->ip_context;
		ip_unlock(port);
		is_write_unlock(space);
		mach_port_guard_exception(name, 0, portguard, kGUARD_EXC_DESTROY);
		return KERN_INVALID_ARGUMENT;
	}

	/*
	 * First reduce the send rights as requested and
	 * adjust the entry->ie_bits accordingly. The
	 * ipc_entry_modified() call is made once the receive
	 * right is destroyed too.
	 */

	if (srdelta) {

		assert(port->ip_srights > 0);

		urefs = IE_BITS_UREFS(bits);

		/*
		 * Since we made sure that srdelta is negative,
		 * the check for urefs overflow is not required.
		 */
		if (MACH_PORT_UREFS_UNDERFLOW(urefs, srdelta)) {
			ip_unlock(port);
			goto invalid_value;
		}

		if (urefs == MACH_PORT_UREFS_MAX) {
			/*
			 * urefs are pegged due to an overflow
			 * only a delta removing all refs at once can change it
			 */
			if (srdelta != (-((mach_port_delta_t)MACH_PORT_UREFS_MAX)))
				srdelta = 0;
		}

		if ((urefs + srdelta) == 0) {
			if (--port->ip_srights == 0) {
				nsrequest = port->ip_nsrequest;
				if (nsrequest != IP_NULL) {
					port->ip_nsrequest = IP_NULL;
					mscount = port->ip_mscount;
				}
			}
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND_RECEIVE);
			entry->ie_bits = bits &~ (IE_BITS_UREFS_MASK|
					       MACH_PORT_TYPE_SEND);
		} else {
			entry->ie_bits = bits + srdelta;
		}
	}

	/*
	 * Now destroy the receive right. Update space and
	 * entry accordingly.
	 */

	bits = entry->ie_bits;
	if (bits & MACH_PORT_TYPE_SEND) {
		assert(IE_BITS_UREFS(bits) > 0);
		assert(IE_BITS_UREFS(bits) <= MACH_PORT_UREFS_MAX);

		if (port->ip_pdrequest != NULL) {
			/*
			 * Since another task has requested a
			 * destroy notification for this port, it
			 * isn't actually being destroyed - the receive
			 * right is just being moved to another task.
			 * Since we still have one or more send rights,
			 * we need to record the loss of the receive
			 * right and enter the remaining send right
			 * into the hash table.
			 */
			ipc_entry_modified(space, name, entry);
			entry->ie_bits &= ~MACH_PORT_TYPE_RECEIVE;
			ipc_hash_insert(space, (ipc_object_t) port,
			    name, entry);
			ip_reference(port);
		} else {
			/*
			 *	The remaining send right turns into a
			 *	dead name.  Notice we don't decrement
			 *	ip_srights, generate a no-senders notif,
			 *	or use ipc_right_dncancel, because the
			 *	port is destroyed "first".
			 */
			bits &= ~IE_BITS_TYPE_MASK;
			bits |= MACH_PORT_TYPE_DEAD_NAME;
			if (entry->ie_request) {
				entry->ie_request = IE_REQ_NONE;
				if (IE_BITS_UREFS(bits) < MACH_PORT_UREFS_MAX)
					bits++; /* increment urefs */
			}
			entry->ie_bits = bits;
			entry->ie_object = IO_NULL;
			ipc_entry_modified(space, name, entry);
		}
	} else {
		assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_RECEIVE);
		assert(IE_BITS_UREFS(bits) == 0);
		request = ipc_right_request_cancel_macro(space, port,
						     name, entry);
		entry->ie_object = IO_NULL;
		ipc_entry_dealloc(space, name, entry);
	}

	/* Unlock space */
	is_write_unlock(space);

	if (nsrequest != IP_NULL)
		ipc_notify_no_senders(nsrequest, mscount);

	ipc_port_destroy(port);	/* clears receiver, consumes ref, unlocks */

	if (request != IP_NULL)
		ipc_notify_port_deleted(request, name);
	
	return KERN_SUCCESS;
	
    invalid_value:
	is_write_unlock(space);
	mach_port_guard_exception(name, 0, 0, kGUARD_EXC_INVALID_VALUE);
	return KERN_INVALID_VALUE;
}