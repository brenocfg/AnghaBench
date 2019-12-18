#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_1__* ipc_pset_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  int /*<<< orphan*/ * ipc_mqueue_t ;
typedef  TYPE_3__* ipc_entry_t ;
struct TYPE_14__ {int ie_bits; scalar_t__ ie_object; } ;
struct TYPE_13__ {scalar_t__ ip_receiver; int /*<<< orphan*/  ips_messages; int /*<<< orphan*/  ip_messages; int /*<<< orphan*/  ip_receiver_name; } ;

/* Variables and functions */
 TYPE_3__* IE_NULL ; 
 TYPE_1__* IPS_NULL ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 int MACH_PORT_TYPE_PORT_SET ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int /*<<< orphan*/  MACH_RCV_INVALID_NAME ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  io_reference (scalar_t__) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 TYPE_3__* ipc_entry_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int ips_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  is_active (scalar_t__) ; 
 int /*<<< orphan*/  is_read_lock (scalar_t__) ; 
 int /*<<< orphan*/  is_read_unlock (scalar_t__) ; 

mach_msg_return_t
ipc_mqueue_copyin(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_mqueue_t		*mqueuep,
	ipc_object_t		*objectp)
{
	ipc_entry_t entry;
	ipc_object_t object;
	ipc_mqueue_t mqueue;

	is_read_lock(space);
	if (!is_active(space)) {
		is_read_unlock(space);
		return MACH_RCV_INVALID_NAME;
	}

	entry = ipc_entry_lookup(space, name);
	if (entry == IE_NULL) {
		is_read_unlock(space);
		return MACH_RCV_INVALID_NAME;
	}

	object = entry->ie_object;

	if (entry->ie_bits & MACH_PORT_TYPE_RECEIVE) {
		ipc_port_t port;

		__IGNORE_WCASTALIGN(port = (ipc_port_t) object);
		assert(port != IP_NULL);

		ip_lock(port);
		assert(ip_active(port));
		assert(port->ip_receiver_name == name);
		assert(port->ip_receiver == space);
		is_read_unlock(space);
		mqueue = &port->ip_messages;

	} else if (entry->ie_bits & MACH_PORT_TYPE_PORT_SET) {
		ipc_pset_t pset;

		__IGNORE_WCASTALIGN(pset = (ipc_pset_t) object);
		assert(pset != IPS_NULL);

		ips_lock(pset);
		assert(ips_active(pset));
		is_read_unlock(space);

		mqueue = &pset->ips_messages;
	} else {
		is_read_unlock(space);
		return MACH_RCV_INVALID_NAME;
	}

	/*
	 *	At this point, the object is locked and active,
	 *	the space is unlocked, and mqueue is initialized.
	 */

	io_reference(object);
	io_unlock(object);

	*objectp = object;
	*mqueuep = mqueue;
	return MACH_MSG_SUCCESS;
}