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

/* Variables and functions */
#define  MACH_MSG_TYPE_COPY_SEND 136 
#define  MACH_MSG_TYPE_DISPOSE_RECEIVE 135 
#define  MACH_MSG_TYPE_DISPOSE_SEND 134 
#define  MACH_MSG_TYPE_DISPOSE_SEND_ONCE 133 
#define  MACH_MSG_TYPE_MAKE_SEND 132 
#define  MACH_MSG_TYPE_MAKE_SEND_ONCE 131 
#define  MACH_MSG_TYPE_MOVE_RECEIVE 130 
#define  MACH_MSG_TYPE_MOVE_SEND 129 
#define  MACH_MSG_TYPE_MOVE_SEND_ONCE 128 
 int MACH_MSG_TYPE_PORT_NONE ; 
 int MACH_MSG_TYPE_PORT_RECEIVE ; 
 int MACH_MSG_TYPE_PORT_SEND ; 
 int MACH_MSG_TYPE_PORT_SEND_ONCE ; 

mach_msg_type_name_t
ipc_object_copyin_type(
	mach_msg_type_name_t	msgt_name)
{
	switch (msgt_name) {

	    case MACH_MSG_TYPE_MOVE_RECEIVE:
		return MACH_MSG_TYPE_PORT_RECEIVE;

	    case MACH_MSG_TYPE_MOVE_SEND_ONCE:
	    case MACH_MSG_TYPE_MAKE_SEND_ONCE:
		return MACH_MSG_TYPE_PORT_SEND_ONCE;

	    case MACH_MSG_TYPE_MOVE_SEND:
	    case MACH_MSG_TYPE_MAKE_SEND:
	    case MACH_MSG_TYPE_COPY_SEND:
		return MACH_MSG_TYPE_PORT_SEND;

	    case MACH_MSG_TYPE_DISPOSE_RECEIVE:
	    case MACH_MSG_TYPE_DISPOSE_SEND:
	    case MACH_MSG_TYPE_DISPOSE_SEND_ONCE:
		/* fall thru */
	    default:
		return MACH_MSG_TYPE_PORT_NONE;
	}
}