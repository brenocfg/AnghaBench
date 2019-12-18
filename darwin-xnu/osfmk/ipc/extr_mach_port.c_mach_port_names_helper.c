#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_port_timestamp_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  scalar_t__ ipc_port_request_index_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  size_t ipc_entry_num_t ;
typedef  int ipc_entry_bits_t ;
struct TYPE_11__ {int ie_bits; scalar_t__ ie_request; scalar_t__ ie_object; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_BITS_TYPE (int) ; 
 int IE_BITS_TYPE_MASK ; 
 scalar_t__ IE_REQ_NONE ; 
 scalar_t__ IP_TIMESTAMP_ORDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IP_VALID (TYPE_1__*) ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND_RIGHTS ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_request_type (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void
mach_port_names_helper(
	ipc_port_timestamp_t	timestamp,
	ipc_entry_t		entry,
	mach_port_name_t	name,
	mach_port_name_t	*names,
	mach_port_type_t	*types,
	ipc_entry_num_t		*actualp)
{
	ipc_entry_bits_t bits;
	ipc_port_request_index_t request;
	mach_port_type_t type = 0;
	ipc_entry_num_t actual;
	ipc_port_t port;

	bits = entry->ie_bits;
	request = entry->ie_request;
	__IGNORE_WCASTALIGN(port = (ipc_port_t) entry->ie_object);

	if (bits & MACH_PORT_TYPE_RECEIVE) {
		assert(IP_VALID(port));

		if (request != IE_REQ_NONE) {
			ip_lock(port);
			assert(ip_active(port));
			type |= ipc_port_request_type(port, name, request);
			ip_unlock(port);
		}

	} else if (bits & MACH_PORT_TYPE_SEND_RIGHTS) {
		mach_port_type_t reqtype;

		assert(IP_VALID(port));
		ip_lock(port);

		reqtype = (request != IE_REQ_NONE) ?
			  ipc_port_request_type(port, name, request) : 0;
		
		/*
		 * If the port is alive, or was alive when the mach_port_names
		 * started, then return that fact.  Otherwise, pretend we found
		 * a dead name entry.
		 */
		if (ip_active(port) || IP_TIMESTAMP_ORDER(timestamp, port->ip_timestamp)) {
			type |= reqtype;
		} else {
			bits &= ~(IE_BITS_TYPE_MASK);
			bits |= MACH_PORT_TYPE_DEAD_NAME;
			/* account for additional reference for dead-name notification */
			if (reqtype != 0)
				bits++;
		}
		ip_unlock(port);
	}

	type |= IE_BITS_TYPE(bits);

	actual = *actualp;
	names[actual] = name;
	types[actual] = type;
	*actualp = actual+1;
}