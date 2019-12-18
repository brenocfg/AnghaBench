#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_urefs_t ;
typedef  int /*<<< orphan*/  mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  scalar_t__ ipc_port_request_index_t ;
typedef  TYPE_1__* ipc_entry_t ;
typedef  int ipc_entry_bits_t ;
struct TYPE_4__ {int ie_bits; scalar_t__ ie_request; scalar_t__ ie_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_BITS_TYPE (int) ; 
 int /*<<< orphan*/  IE_BITS_UREFS (int) ; 
 scalar_t__ IE_REQ_NONE ; 
 int IP_VALID (scalar_t__) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND_RIGHTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (scalar_t__) ; 
 int /*<<< orphan*/  ip_lock (scalar_t__) ; 
 int /*<<< orphan*/  ip_release (scalar_t__) ; 
 int /*<<< orphan*/  ip_unlock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_request_type (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipc_right_check (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_right_info(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry,
	mach_port_type_t	*typep,
	mach_port_urefs_t	*urefsp)
{
	ipc_port_t port;
	ipc_entry_bits_t bits;
	mach_port_type_t type = 0;
	ipc_port_request_index_t request;

	bits = entry->ie_bits;
	request = entry->ie_request;
	port = (ipc_port_t) entry->ie_object;

	if (bits & MACH_PORT_TYPE_RECEIVE) {
		assert(IP_VALID(port));

		if (request != IE_REQ_NONE) {
			ip_lock(port);
			assert(ip_active(port));
			type |= ipc_port_request_type(port, name, request);
			ip_unlock(port);
		}
		is_write_unlock(space);

	} else if (bits & MACH_PORT_TYPE_SEND_RIGHTS) {
		/*
		 * validate port is still alive - if so, get request
		 * types while we still have it locked.  Otherwise,
		 * recapture the (now dead) bits.
		 */
		if (!ipc_right_check(space, port, name, entry)) {
			if (request != IE_REQ_NONE)
				type |= ipc_port_request_type(port, name, request);
			ip_unlock(port);
			is_write_unlock(space);
		} else {
			bits = entry->ie_bits;
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_DEAD_NAME);
			is_write_unlock(space);
			ip_release(port);
		}
	} else {
		is_write_unlock(space);
	}

	type |= IE_BITS_TYPE(bits);

	*typep = type;
	*urefsp = IE_BITS_UREFS(bits);
	return KERN_SUCCESS;
}