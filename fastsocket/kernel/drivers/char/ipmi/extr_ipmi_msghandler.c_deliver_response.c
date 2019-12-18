#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ipmi_recv_msg {TYPE_2__* user; TYPE_3__* user_msg_data; } ;
typedef  TYPE_2__* ipmi_user_t ;
typedef  TYPE_3__* ipmi_smi_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* null_user_handler ) (TYPE_3__*,struct ipmi_recv_msg*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  handler_data; TYPE_1__* handler; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ipmi_recv_hndl ) (struct ipmi_recv_msg*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  handled_local_responses ; 
 int /*<<< orphan*/  ipmi_free_recv_msg (struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  ipmi_inc_stat (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  stub2 (struct ipmi_recv_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhandled_local_responses ; 

__attribute__((used)) static void deliver_response(struct ipmi_recv_msg *msg)
{
	if (!msg->user) {
		ipmi_smi_t    intf = msg->user_msg_data;

		/* Special handling for NULL users. */
		if (intf->null_user_handler) {
			intf->null_user_handler(intf, msg);
			ipmi_inc_stat(intf, handled_local_responses);
		} else {
			/* No handler, so give up. */
			ipmi_inc_stat(intf, unhandled_local_responses);
		}
		ipmi_free_recv_msg(msg);
	} else {
		ipmi_user_t user = msg->user;
		user->handler->ipmi_recv_hndl(msg, user->handler_data);
	}
}