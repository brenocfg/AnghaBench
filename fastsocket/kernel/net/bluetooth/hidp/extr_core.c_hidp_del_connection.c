#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hidp_session {int /*<<< orphan*/  terminate; TYPE_4__* ctrl_sock; TYPE_2__* intr_sock; int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  ctrl_transmit; } ;
struct hidp_conndel_req {int flags; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_8__ {TYPE_3__* sk; } ;
struct TYPE_7__ {void* sk_err; } ;
struct TYPE_6__ {TYPE_1__* sk; } ;
struct TYPE_5__ {void* sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int ENOENT ; 
 void* EUNATCH ; 
 int HIDP_CTRL_VIRTUAL_CABLE_UNPLUG ; 
 int HIDP_TRANS_HID_CONTROL ; 
 int HIDP_VIRTUAL_CABLE_UNPLUG ; 
 struct hidp_session* __hidp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_schedule (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_send_ctrl_message (struct hidp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_session_sem ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int hidp_del_connection(struct hidp_conndel_req *req)
{
	struct hidp_session *session;
	int err = 0;

	BT_DBG("");

	down_read(&hidp_session_sem);

	session = __hidp_get_session(&req->bdaddr);
	if (session) {
		if (req->flags & (1 << HIDP_VIRTUAL_CABLE_UNPLUG)) {
			hidp_send_ctrl_message(session,
				HIDP_TRANS_HID_CONTROL | HIDP_CTRL_VIRTUAL_CABLE_UNPLUG, NULL, 0);
		} else {
			/* Flush the transmit queues */
			skb_queue_purge(&session->ctrl_transmit);
			skb_queue_purge(&session->intr_transmit);

			/* Wakeup user-space polling for socket errors */
			session->intr_sock->sk->sk_err = EUNATCH;
			session->ctrl_sock->sk->sk_err = EUNATCH;

			/* Kill session thread */
			atomic_inc(&session->terminate);
			hidp_schedule(session);
		}
	} else
		err = -ENOENT;

	up_read(&hidp_session_sem);
	return err;
}