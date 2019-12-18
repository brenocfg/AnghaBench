#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_port_mscount_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_pset_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int /*<<< orphan*/  ipc_entry_bits_t ;
struct TYPE_17__ {int /*<<< orphan*/  ie_object; int /*<<< orphan*/  ie_request; int /*<<< orphan*/  ie_bits; } ;
struct TYPE_16__ {int /*<<< orphan*/  ip_receiver; int /*<<< orphan*/  ip_sorights; int /*<<< orphan*/  ip_receiver_name; int /*<<< orphan*/  ip_mscount; struct TYPE_16__* ip_nsrequest; int /*<<< orphan*/  ip_srights; } ;

/* Variables and functions */
 int IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IE_REQ_NONE ; 
 int /*<<< orphan*/  IO_NULL ; 
 int /*<<< orphan*/  IPS_NULL ; 
 TYPE_1__* IP_NULL ; 
#define  MACH_PORT_TYPE_DEAD_NAME 133 
#define  MACH_PORT_TYPE_PORT_SET 132 
#define  MACH_PORT_TYPE_RECEIVE 131 
#define  MACH_PORT_TYPE_SEND 130 
#define  MACH_PORT_TYPE_SEND_ONCE 129 
#define  MACH_PORT_TYPE_SEND_RECEIVE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_notify_no_senders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_port_deleted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_send_once (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_pset_destroy (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipc_right_request_cancel_macro (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ips_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
ipc_right_terminate(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry)
{
	ipc_entry_bits_t bits;
	mach_port_type_t type;

	bits = entry->ie_bits;
	type = IE_BITS_TYPE(bits);

	assert(!is_active(space));

	/*
	 *	IE_BITS_COMPAT/ipc_right_dncancel doesn't have this
	 *	problem, because we check that the port is active.  If
	 *	we didn't cancel IE_BITS_COMPAT, ipc_port_destroy
	 *	would still work, but dead space refs would accumulate
	 *	in ip_dnrequests.  They would use up slots in
	 *	ip_dnrequests and keep the spaces from being freed.
	 */

	switch (type) {
	    case MACH_PORT_TYPE_DEAD_NAME:
		assert(entry->ie_request == IE_REQ_NONE);
		assert(entry->ie_object == IO_NULL);
		break;

	    case MACH_PORT_TYPE_PORT_SET: {
		ipc_pset_t pset = (ipc_pset_t) entry->ie_object;

		assert(entry->ie_request == IE_REQ_NONE);
		assert(pset != IPS_NULL);

		ips_lock(pset);
		assert(ips_active(pset));
		ipc_pset_destroy(pset); /* consumes ref, unlocks */
		break;
	    }

	    case MACH_PORT_TYPE_SEND:
	    case MACH_PORT_TYPE_RECEIVE:
	    case MACH_PORT_TYPE_SEND_RECEIVE:
	    case MACH_PORT_TYPE_SEND_ONCE: {
		ipc_port_t port = (ipc_port_t) entry->ie_object;
		ipc_port_t request;
		ipc_port_t nsrequest = IP_NULL;
		mach_port_mscount_t mscount = 0;

		assert(port != IP_NULL);
		ip_lock(port);

		if (!ip_active(port)) {
			ip_unlock(port);
			ip_release(port);
			break;
		}

		request = ipc_right_request_cancel_macro(space, port, 
					name, entry);

		if (type & MACH_PORT_TYPE_SEND) {
			assert(port->ip_srights > 0);
			if (--port->ip_srights == 0
			    ) {
				nsrequest = port->ip_nsrequest;
				if (nsrequest != IP_NULL) {
					port->ip_nsrequest = IP_NULL;
					mscount = port->ip_mscount;
				}
			}
		}

		if (type & MACH_PORT_TYPE_RECEIVE) {
			assert(port->ip_receiver_name == name);
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
		panic("ipc_right_terminate: strange type - 0x%x", type);
	}
}