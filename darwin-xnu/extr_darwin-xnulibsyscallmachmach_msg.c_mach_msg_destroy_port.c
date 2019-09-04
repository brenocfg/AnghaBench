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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int mach_msg_type_name_t ;

/* Variables and functions */
#define  MACH_MSG_TYPE_MAKE_SEND 132 
#define  MACH_MSG_TYPE_MAKE_SEND_ONCE 131 
#define  MACH_MSG_TYPE_MOVE_RECEIVE 130 
#define  MACH_MSG_TYPE_MOVE_SEND 129 
#define  MACH_MSG_TYPE_MOVE_SEND_ONCE 128 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_port_extract_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mach_port_insert_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  mach_port_mod_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self_ ; 

__attribute__((used)) static void
mach_msg_destroy_port(mach_port_t port, mach_msg_type_name_t type)
{
    if (MACH_PORT_VALID(port)) switch (type) {
      case MACH_MSG_TYPE_MOVE_SEND:
      case MACH_MSG_TYPE_MOVE_SEND_ONCE:
	/* destroy the send/send-once right */
	(void) mach_port_deallocate(mach_task_self_, port);
	break;

      case MACH_MSG_TYPE_MOVE_RECEIVE:
	/* destroy the receive right */
	(void) mach_port_mod_refs(mach_task_self_, port,
				  MACH_PORT_RIGHT_RECEIVE, -1);
	break;

      case MACH_MSG_TYPE_MAKE_SEND:
	/* create a send right and then destroy it */
	(void) mach_port_insert_right(mach_task_self_, port,
				      port, MACH_MSG_TYPE_MAKE_SEND);
	(void) mach_port_deallocate(mach_task_self_, port);
	break;

      case MACH_MSG_TYPE_MAKE_SEND_ONCE:
	/* create a send-once right and then destroy it */
	(void) mach_port_extract_right(mach_task_self_, port,
				       MACH_MSG_TYPE_MAKE_SEND_ONCE,
				       &port, &type);
	(void) mach_port_deallocate(mach_task_self_, port);
	break;
    }
}