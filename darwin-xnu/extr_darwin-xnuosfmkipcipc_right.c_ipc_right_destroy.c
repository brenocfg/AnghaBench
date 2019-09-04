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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_port_mscount_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_pset_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int /*<<< orphan*/  ipc_entry_bits_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_19__ {void* ie_object; int /*<<< orphan*/  ie_request; int /*<<< orphan*/  ie_bits; } ;
struct TYPE_18__ {int /*<<< orphan*/  ip_receiver; int /*<<< orphan*/  ip_sorights; int /*<<< orphan*/  ip_mscount; struct TYPE_18__* ip_nsrequest; int /*<<< orphan*/  ip_srights; int /*<<< orphan*/  ip_context; int /*<<< orphan*/  ip_guarded; } ;

/* Variables and functions */
 int IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IE_BITS_TYPE_MASK ; 
 int /*<<< orphan*/  IE_REQ_NONE ; 
 void* IO_NULL ; 
 int /*<<< orphan*/  IPS_NULL ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  MACH_PORT_TYPE_DEAD_NAME 133 
#define  MACH_PORT_TYPE_PORT_SET 132 
#define  MACH_PORT_TYPE_RECEIVE 131 
#define  MACH_PORT_TYPE_SEND 130 
#define  MACH_PORT_TYPE_SEND_ONCE 129 
#define  MACH_PORT_TYPE_SEND_RECEIVE 128 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_entry_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_notify_no_senders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_port_deleted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_send_once (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_pset_destroy (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipc_right_request_cancel_macro (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ips_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_lock (int /*<<< orphan*/ ) ; 
 int is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kGUARD_EXC_DESTROY ; 
 int /*<<< orphan*/  mach_port_guard_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

kern_return_t
ipc_right_destroy(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry,
	boolean_t		check_guard,
	uint64_t		guard)
{
	ipc_entry_bits_t bits;
	mach_port_type_t type;

	bits = entry->ie_bits;
	entry->ie_bits &= ~IE_BITS_TYPE_MASK;
	type = IE_BITS_TYPE(bits);

	assert(is_active(space));

	switch (type) {
	    case MACH_PORT_TYPE_DEAD_NAME:
		assert(entry->ie_request == IE_REQ_NONE);
		assert(entry->ie_object == IO_NULL);

		ipc_entry_dealloc(space, name, entry);
		is_write_unlock(space);
		break;

	    case MACH_PORT_TYPE_PORT_SET: {
		ipc_pset_t pset = (ipc_pset_t) entry->ie_object;

		assert(entry->ie_request == IE_REQ_NONE);
		assert(pset != IPS_NULL);

		entry->ie_object = IO_NULL;
		ipc_entry_dealloc(space, name, entry);

		ips_lock(pset);
		is_write_unlock(space);

		assert(ips_active(pset));
		ipc_pset_destroy(pset); /* consumes ref, unlocks */
		break;
	    }

	    case MACH_PORT_TYPE_SEND:
	    case MACH_PORT_TYPE_RECEIVE:
	    case MACH_PORT_TYPE_SEND_RECEIVE:
	    case MACH_PORT_TYPE_SEND_ONCE: {
		ipc_port_t port = (ipc_port_t) entry->ie_object;
		ipc_port_t nsrequest = IP_NULL;
		mach_port_mscount_t mscount = 0;
		ipc_port_t request;

		assert(port != IP_NULL);

		if (type == MACH_PORT_TYPE_SEND)
			ipc_hash_delete(space, (ipc_object_t) port,
					name, entry);

		ip_lock(port);

		if (!ip_active(port)) {
			assert((type & MACH_PORT_TYPE_RECEIVE) == 0);
			ip_unlock(port);
			entry->ie_request = IE_REQ_NONE;
			entry->ie_object = IO_NULL;
			ipc_entry_dealloc(space, name, entry);
			is_write_unlock(space);
			ip_release(port);
			break;
		}

		/* For receive rights, check for guarding */
		if ((type & MACH_PORT_TYPE_RECEIVE) &&
		    (check_guard) && (port->ip_guarded) &&
		    (guard != port->ip_context)) {
			/* Guard Violation */
			uint64_t portguard = port->ip_context;
			ip_unlock(port);
			is_write_unlock(space);
			/* Raise mach port guard exception */
			mach_port_guard_exception(name, 0, portguard, kGUARD_EXC_DESTROY);
			return KERN_INVALID_RIGHT;		
		}


		request = ipc_right_request_cancel_macro(space, port, name, entry);

		entry->ie_object = IO_NULL;
		ipc_entry_dealloc(space, name, entry);
		is_write_unlock(space);

		if (type & MACH_PORT_TYPE_SEND) {
			assert(port->ip_srights > 0);
			if (--port->ip_srights == 0) {
				nsrequest = port->ip_nsrequest;
				if (nsrequest != IP_NULL) {
					port->ip_nsrequest = IP_NULL;
					mscount = port->ip_mscount;
				}
			}
		}

		if (type & MACH_PORT_TYPE_RECEIVE) {
			assert(ip_active(port));
			assert(port->ip_receiver == space);

			ipc_port_destroy(port); /* clears receiver, consumes our ref, unlocks */

		} else if (type & MACH_PORT_TYPE_SEND_ONCE) {
			assert(port->ip_sorights > 0);
			ip_unlock(port);

			ipc_notify_send_once(port); /* consumes our ref */
		} else {
			assert(port->ip_receiver != space);

			ip_unlock(port);
			ip_release(port);
		}

		if (nsrequest != IP_NULL)
			ipc_notify_no_senders(nsrequest, mscount);

		if (request != IP_NULL)
			ipc_notify_port_deleted(request, name);


		break;
	    }

	    default:
		panic("ipc_right_destroy: strange type");
	}

	return KERN_SUCCESS;
}