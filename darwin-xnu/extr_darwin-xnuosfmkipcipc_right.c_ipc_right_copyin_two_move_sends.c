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
typedef  int mach_port_urefs_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int ipc_entry_bits_t ;
struct TYPE_17__ {int ie_bits; scalar_t__ ie_object; } ;
struct TYPE_16__ {scalar_t__ ip_srights; scalar_t__ ip_receiver; int /*<<< orphan*/  ip_receiver_name; } ;

/* Variables and functions */
 int IE_BITS_TYPE (int) ; 
 scalar_t__ IE_BITS_UREFS (int) ; 
 int IE_BITS_UREFS_MASK ; 
 scalar_t__ IO_NULL ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 scalar_t__ MACH_PORT_UREFS_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_entry_modified (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_delete (scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ipc_right_check (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ipc_right_request_cancel_macro (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int is_active (scalar_t__) ; 

__attribute__((used)) static
kern_return_t
ipc_right_copyin_two_move_sends(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry,
	ipc_object_t		*objectp,
	ipc_port_t		*sorightp,
	ipc_port_t		*releasep)
{
	ipc_entry_bits_t bits;
	mach_port_urefs_t urefs;
	ipc_port_t port;
	ipc_port_t request = IP_NULL;

	*releasep = IP_NULL;

	assert(is_active(space));

	bits = entry->ie_bits;

	if ((bits & MACH_PORT_TYPE_SEND) == 0)
		goto invalid_right;

	urefs = IE_BITS_UREFS(bits);
	if (urefs < 2)
		goto invalid_right;

	port = (ipc_port_t) entry->ie_object;
	assert(port != IP_NULL);

	if (ipc_right_check(space, port, name, entry)) {
		*releasep = port;
		goto invalid_right;
	}
	/* port is locked and active */

	assert(port->ip_srights > 0);

	if (urefs == 2) {
		if (bits & MACH_PORT_TYPE_RECEIVE) {
			assert(port->ip_receiver_name == name);
			assert(port->ip_receiver == space);
			assert(IE_BITS_TYPE(bits) ==
					MACH_PORT_TYPE_SEND_RECEIVE);

			port->ip_srights++;
			ip_reference(port);
			ip_reference(port);
		} else {
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND);

			request = ipc_right_request_cancel_macro(space, port,
							     name, entry);

			port->ip_srights++;
			ip_reference(port);
			ipc_hash_delete(space, (ipc_object_t) port,
					name, entry);
			entry->ie_object = IO_NULL;
		}
		entry->ie_bits = bits &~ (IE_BITS_UREFS_MASK|MACH_PORT_TYPE_SEND);
	} else {
		port->ip_srights += 2;
		ip_reference(port);
		ip_reference(port);
		/* if urefs are pegged due to overflow, leave them pegged */
		if (IE_BITS_UREFS(bits) < MACH_PORT_UREFS_MAX)
			entry->ie_bits = bits-2; /* decrement urefs */
	}
	ipc_entry_modified(space, name, entry);

	ip_unlock(port);

	*objectp = (ipc_object_t) port;
	*sorightp = request;
	return KERN_SUCCESS;

    invalid_right:
	return KERN_INVALID_RIGHT;
}