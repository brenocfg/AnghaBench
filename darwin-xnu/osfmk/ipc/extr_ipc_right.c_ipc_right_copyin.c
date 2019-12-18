#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int ipc_entry_bits_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_21__ {int ie_bits; scalar_t__ ie_object; scalar_t__ ie_request; } ;
struct TYPE_20__ {int ip_tempowner; int ip_impcount; int /*<<< orphan*/  ip_sorights; int /*<<< orphan*/  ip_srights; int /*<<< orphan*/  ip_receiver; int /*<<< orphan*/  ip_receiver_name; int /*<<< orphan*/  ip_imp_task; int /*<<< orphan*/  ip_messages; struct TYPE_20__* ip_destination; int /*<<< orphan*/  ip_mscount; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IE_BITS_TYPE (int) ; 
 int IE_BITS_UREFS (int) ; 
 int IE_BITS_UREFS_MASK ; 
 scalar_t__ IE_REQ_NONE ; 
 int /*<<< orphan*/  IIT_NULL ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IO_DEAD ; 
 void* IO_NULL ; 
 TYPE_1__* IP_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_CAPABILITY ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  MACH_MSG_TYPE_COPY_SEND 133 
#define  MACH_MSG_TYPE_MAKE_SEND 132 
#define  MACH_MSG_TYPE_MAKE_SEND_ONCE 131 
#define  MACH_MSG_TYPE_MOVE_RECEIVE 130 
#define  MACH_MSG_TYPE_MOVE_SEND 129 
#define  MACH_MSG_TYPE_MOVE_SEND_ONCE 128 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int MACH_PORT_TYPE_RECEIVE ; 
 int MACH_PORT_TYPE_SEND ; 
 int MACH_PORT_TYPE_SEND_ONCE ; 
 int MACH_PORT_TYPE_SEND_RECEIVE ; 
 int MACH_PORT_TYPE_SEND_RIGHTS ; 
 int MACH_PORT_UREFS_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_kotype (scalar_t__) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_entry_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_hash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_clear_receiver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_right_check (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ipc_right_request_cancel_macro (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int is_active (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_right_copyin(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		entry,
	mach_msg_type_name_t	msgt_name,
	boolean_t		deadok,
	ipc_object_t		*objectp,
	ipc_port_t		*sorightp,
	ipc_port_t		*releasep,
	int			*assertcntp)
{
	ipc_entry_bits_t bits;
	ipc_port_t port;

	*releasep = IP_NULL;
	*assertcntp = 0;

	bits = entry->ie_bits;

	assert(is_active(space));

	switch (msgt_name) {
	    case MACH_MSG_TYPE_MAKE_SEND: {

		if ((bits & MACH_PORT_TYPE_RECEIVE) == 0)
			goto invalid_right;

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		ip_lock(port);
		assert(ip_active(port));
		assert(port->ip_receiver_name == name);
		assert(port->ip_receiver == space);

		port->ip_mscount++;
		port->ip_srights++;
		ip_reference(port);
		ip_unlock(port);

		*objectp = (ipc_object_t) port;
		*sorightp = IP_NULL;
		break;
	    }

	    case MACH_MSG_TYPE_MAKE_SEND_ONCE: {

		if ((bits & MACH_PORT_TYPE_RECEIVE) == 0)
			goto invalid_right;

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		ip_lock(port);
		assert(ip_active(port));
		assert(port->ip_receiver_name == name);
		assert(port->ip_receiver == space);

		port->ip_sorights++;
		ip_reference(port);
		ip_unlock(port);

		*objectp = (ipc_object_t) port;
		*sorightp = IP_NULL;
		break;
	    }

	    case MACH_MSG_TYPE_MOVE_RECEIVE: {
		ipc_port_t request = IP_NULL;

		if ((bits & MACH_PORT_TYPE_RECEIVE) == 0)
			goto invalid_right;

		/*
		 * Disallow moving receive-right kobjects, e.g. mk_timer ports
		 * The ipc_port structure uses the kdata union of kobject and
		 * imp_task exclusively. Thus, general use of a kobject port as
		 * a receive right can cause type confusion in the importance
		 * code.
		 */
		if (io_kotype(entry->ie_object) != IKOT_NONE) {
			/*
			 * Distinguish an invalid right, e.g., trying to move
			 * a send right as a receive right, from this
			 * situation which is, "This is a valid receive right,
			 * but it's also a kobject and you can't move it."
			 */
			return KERN_INVALID_CAPABILITY;
		}

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		ip_lock(port);
		assert(ip_active(port));
		assert(port->ip_receiver_name == name);
		assert(port->ip_receiver == space);

		if (bits & MACH_PORT_TYPE_SEND) {
			assert(IE_BITS_TYPE(bits) ==
					MACH_PORT_TYPE_SEND_RECEIVE);
			assert(IE_BITS_UREFS(bits) > 0);
			assert(port->ip_srights > 0);

			ipc_hash_insert(space, (ipc_object_t) port,
					name, entry);
			ip_reference(port);
		} else {
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_RECEIVE);
			assert(IE_BITS_UREFS(bits) == 0);

			request = ipc_right_request_cancel_macro(space, port,
							     name, entry);
			entry->ie_object = IO_NULL;
		}
		entry->ie_bits = bits &~ MACH_PORT_TYPE_RECEIVE;
		ipc_entry_modified(space, name, entry);

		(void)ipc_port_clear_receiver(port, FALSE); /* don't destroy the port/mqueue */
		imq_lock(&port->ip_messages);
		port->ip_receiver_name = MACH_PORT_NULL;
		port->ip_destination = IP_NULL;
		imq_unlock(&port->ip_messages);

#if IMPORTANCE_INHERITANCE
		/*
		 * Account for boosts the current task is going to lose when
		 * copying this right in.  Tempowner ports have either not
		 * been accounting to any task (and therefore are already in
		 * "limbo" state w.r.t. assertions) or to some other specific
		 * task. As we have no way to drop the latter task's assertions
		 * here, We'll deduct those when we enqueue it on its
		 * destination port (see ipc_port_check_circularity()).
		 */
		if (port->ip_tempowner == 0) {
			assert(IIT_NULL == port->ip_imp_task);

			/* ports in limbo have to be tempowner */
			port->ip_tempowner = 1;
			*assertcntp = port->ip_impcount;
		}
#endif /* IMPORTANCE_INHERITANCE */

		ip_unlock(port);

		*objectp = (ipc_object_t) port;
		*sorightp = request;
		break;
	    }

	    case MACH_MSG_TYPE_COPY_SEND: {

		if (bits & MACH_PORT_TYPE_DEAD_NAME)
			goto copy_dead;

		/* allow for dead send-once rights */

		if ((bits & MACH_PORT_TYPE_SEND_RIGHTS) == 0)
			goto invalid_right;

		assert(IE_BITS_UREFS(bits) > 0);

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		if (ipc_right_check(space, port, name, entry)) {
			bits = entry->ie_bits;
			*releasep = port;
			goto copy_dead;
		}
		/* port is locked and active */

		if ((bits & MACH_PORT_TYPE_SEND) == 0) {
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND_ONCE);
			assert(port->ip_sorights > 0);

			ip_unlock(port);
			goto invalid_right;
		}

		assert(port->ip_srights > 0);

		port->ip_srights++;
		ip_reference(port);
		ip_unlock(port);

		*objectp = (ipc_object_t) port;
		*sorightp = IP_NULL;
		break;
	    }

	    case MACH_MSG_TYPE_MOVE_SEND: {
		ipc_port_t request = IP_NULL;

		if (bits & MACH_PORT_TYPE_DEAD_NAME)
			goto move_dead;

		/* allow for dead send-once rights */

		if ((bits & MACH_PORT_TYPE_SEND_RIGHTS) == 0)
			goto invalid_right;

		assert(IE_BITS_UREFS(bits) > 0);

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		if (ipc_right_check(space, port, name, entry)) {
			bits = entry->ie_bits;
			*releasep = port;
			goto move_dead;
		}
		/* port is locked and active */

		if ((bits & MACH_PORT_TYPE_SEND) == 0) {
			assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND_ONCE);
			assert(port->ip_sorights > 0);

			ip_unlock(port);
			goto invalid_right;
		}

		assert(port->ip_srights > 0);

		if (IE_BITS_UREFS(bits) == 1) {
			if (bits & MACH_PORT_TYPE_RECEIVE) {
				assert(port->ip_receiver_name == name);
				assert(port->ip_receiver == space);
				assert(IE_BITS_TYPE(bits) ==
						MACH_PORT_TYPE_SEND_RECEIVE);

				ip_reference(port);
			} else {
				assert(IE_BITS_TYPE(bits) ==
						MACH_PORT_TYPE_SEND);

				request = ipc_right_request_cancel_macro(space, port,
								     name, entry);
				ipc_hash_delete(space, (ipc_object_t) port,
						name, entry);
				entry->ie_object = IO_NULL;
				/* transfer entry's reference to caller */
			}
			entry->ie_bits = bits &~
				(IE_BITS_UREFS_MASK|MACH_PORT_TYPE_SEND);
		} else {
			port->ip_srights++;
			ip_reference(port);
			/* if urefs are pegged due to overflow, leave them pegged */
			if (IE_BITS_UREFS(bits) < MACH_PORT_UREFS_MAX)
				entry->ie_bits = bits-1; /* decrement urefs */
		}

		ipc_entry_modified(space, name, entry);
		ip_unlock(port);

		*objectp = (ipc_object_t) port;
		*sorightp = request;
		break;
	    }

	    case MACH_MSG_TYPE_MOVE_SEND_ONCE: {
		ipc_port_t request;

		if (bits & MACH_PORT_TYPE_DEAD_NAME)
			goto move_dead;

		/* allow for dead send rights */

		if ((bits & MACH_PORT_TYPE_SEND_RIGHTS) == 0)
			goto invalid_right;

		assert(IE_BITS_UREFS(bits) > 0);

		port = (ipc_port_t) entry->ie_object;
		assert(port != IP_NULL);

		if (ipc_right_check(space, port, name, entry)) {
			bits = entry->ie_bits;
			*releasep = port;
			goto move_dead;
		}
		/* port is locked and active */

		if ((bits & MACH_PORT_TYPE_SEND_ONCE) == 0) {
			assert(bits & MACH_PORT_TYPE_SEND);
			assert(port->ip_srights > 0);

			ip_unlock(port);
			goto invalid_right;
		}

		assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_SEND_ONCE);
		assert(IE_BITS_UREFS(bits) == 1);
		assert(port->ip_sorights > 0);

		request = ipc_right_request_cancel_macro(space, port, name, entry);
		ip_unlock(port);

		entry->ie_object = IO_NULL;
		entry->ie_bits = bits &~
			(IE_BITS_UREFS_MASK | MACH_PORT_TYPE_SEND_ONCE);
		ipc_entry_modified(space, name, entry);
		*objectp = (ipc_object_t) port;
		*sorightp = request;
		break;
	    }

	    default:
	    invalid_right:
		return KERN_INVALID_RIGHT;
	}

	return KERN_SUCCESS;

    copy_dead:
	assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_DEAD_NAME);
	assert(IE_BITS_UREFS(bits) > 0);
	assert(entry->ie_request == IE_REQ_NONE);
	assert(entry->ie_object == 0);

	if (!deadok)
		goto invalid_right;

	*objectp = IO_DEAD;
	*sorightp = IP_NULL;
	return KERN_SUCCESS;

    move_dead:
	assert(IE_BITS_TYPE(bits) == MACH_PORT_TYPE_DEAD_NAME);
	assert(IE_BITS_UREFS(bits) > 0);
	assert(entry->ie_request == IE_REQ_NONE);
	assert(entry->ie_object == 0);

	if (!deadok)
		goto invalid_right;

	if (IE_BITS_UREFS(bits) == 1) {
		bits &= ~MACH_PORT_TYPE_DEAD_NAME;
	}
	/* if urefs are pegged due to overflow, leave them pegged */
	if (IE_BITS_UREFS(bits) < MACH_PORT_UREFS_MAX)
		entry->ie_bits = bits-1; /* decrement urefs */

	ipc_entry_modified(space, name, entry);
	*objectp = IO_DEAD;
	*sorightp = IP_NULL;
	return KERN_SUCCESS;

}