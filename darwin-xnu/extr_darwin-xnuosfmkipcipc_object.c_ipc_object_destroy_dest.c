#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;

/* Variables and functions */
 scalar_t__ IOT_PORT ; 
 int IO_VALID (int /*<<< orphan*/ ) ; 
#define  MACH_MSG_TYPE_PORT_SEND 129 
#define  MACH_MSG_TYPE_PORT_SEND_ONCE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  io_active (int /*<<< orphan*/ ) ; 
 scalar_t__ io_otype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_full_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_notify_send_once (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_sonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_object_destroy_dest(
	ipc_object_t		object,
	mach_msg_type_name_t	msgt_name)
{
	assert(IO_VALID(object));
	assert(io_otype(object) == IOT_PORT);

	switch (msgt_name) {
	    case MACH_MSG_TYPE_PORT_SEND:
		ipc_port_release_send((ipc_port_t) object);
		break;

	    case MACH_MSG_TYPE_PORT_SEND_ONCE:
		if (io_active(object) && 
		    !ip_full_kernel((ipc_port_t) object))
			ipc_notify_send_once((ipc_port_t) object);
		else
			ipc_port_release_sonce((ipc_port_t) object);
		break;

	    default:
		panic("ipc_object_destroy_dest: strange rights");
	}
}