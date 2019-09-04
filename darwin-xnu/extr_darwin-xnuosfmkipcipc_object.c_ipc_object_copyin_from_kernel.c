#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int mach_msg_type_name_t ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_node_id; } ;
struct TYPE_8__ {int ip_srights; int ip_sorights; int /*<<< orphan*/  ip_receiver_name; int /*<<< orphan*/  ip_mscount; TYPE_2__* ip_receiver; int /*<<< orphan*/  ip_messages; int /*<<< orphan*/  ip_destination; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_LOCAL_NODE ; 
 int IO_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_NULL ; 
#define  MACH_MSG_TYPE_COPY_SEND 133 
#define  MACH_MSG_TYPE_MAKE_SEND 132 
#define  MACH_MSG_TYPE_MAKE_SEND_ONCE 131 
#define  MACH_MSG_TYPE_MOVE_RECEIVE 130 
#define  MACH_MSG_TYPE_MOVE_SEND 129 
#define  MACH_MSG_TYPE_MOVE_SEND_ONCE 128 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_set_mscount (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ipc_space_kernel ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_object_copyin_from_kernel(
	ipc_object_t		object,
	mach_msg_type_name_t	msgt_name)
{
	assert(IO_VALID(object));

	switch (msgt_name) {
	    case MACH_MSG_TYPE_MOVE_RECEIVE: {
		ipc_port_t port = (ipc_port_t) object;

		ip_lock(port);
		imq_lock(&port->ip_messages);
		assert(ip_active(port));
		if (port->ip_destination != IP_NULL) {
			assert(port->ip_receiver == ipc_space_kernel);

			/* relevant part of ipc_port_clear_receiver */
			ipc_port_set_mscount(port, 0);

			port->ip_receiver_name = MACH_PORT_NULL;
			port->ip_destination = IP_NULL;
		}
		imq_unlock(&port->ip_messages);
		ip_unlock(port);
		break;
	    }

	    case MACH_MSG_TYPE_COPY_SEND: {
		ipc_port_t port = (ipc_port_t) object;

		ip_lock(port);
		if (ip_active(port)) {
			assert(port->ip_srights > 0);
			port->ip_srights++;
		}
		ip_reference(port);
		ip_unlock(port);
		break;
	    }

	    case MACH_MSG_TYPE_MAKE_SEND: {
		ipc_port_t port = (ipc_port_t) object;

		ip_lock(port);
		if (ip_active(port)) {
			assert(port->ip_receiver_name != MACH_PORT_NULL);
			assert((port->ip_receiver == ipc_space_kernel) ||
                   (port->ip_receiver->is_node_id != HOST_LOCAL_NODE));
			port->ip_mscount++;
		}

		port->ip_srights++;
		ip_reference(port);
		ip_unlock(port);
		break;
	    }

	    case MACH_MSG_TYPE_MOVE_SEND: {
		/* move naked send right into the message */
		assert(((ipc_port_t)object)->ip_srights);
		break;
	    }

	    case MACH_MSG_TYPE_MAKE_SEND_ONCE: {
		ipc_port_t port = (ipc_port_t) object;

		ip_lock(port);
		if (ip_active(port)) {
			assert(port->ip_receiver_name != MACH_PORT_NULL);
		}
		port->ip_sorights++;
		ip_reference(port);
		ip_unlock(port);
		break;
	    }

	    case MACH_MSG_TYPE_MOVE_SEND_ONCE: {
		/* move naked send-once right into the message */
	    	assert(((ipc_port_t)object)->ip_sorights);
		break;
	    }

	    default:
		panic("ipc_object_copyin_from_kernel: strange rights");
	}
}