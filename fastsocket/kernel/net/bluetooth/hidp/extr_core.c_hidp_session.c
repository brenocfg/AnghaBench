#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/ * sk_sleep; void* sk_err; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct hidp_session {TYPE_3__* ctrl_sock; TYPE_2__* intr_sock; TYPE_5__* hid; TYPE_4__* input; int /*<<< orphan*/  terminate; } ;
struct TYPE_10__ {int vendor; int product; } ;
struct TYPE_6__ {int vendor; int product; } ;
struct TYPE_9__ {TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  file; struct sock* sk; } ;
struct TYPE_7__ {int /*<<< orphan*/  file; struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*) ; 
 void* EUNATCH ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __hidp_unlink_session (struct hidp_session*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  daemonize (char*,int,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_destroy_device (TYPE_5__*) ; 
 int /*<<< orphan*/  hidp_del_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_process_transmit (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_recv_ctrl_frame (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_recv_intr_frame (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_schedule (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_sem ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct hidp_session*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidp_session(void *arg)
{
	struct hidp_session *session = arg;
	struct sock *ctrl_sk = session->ctrl_sock->sk;
	struct sock *intr_sk = session->intr_sock->sk;
	struct sk_buff *skb;
	int vendor = 0x0000, product = 0x0000;
	wait_queue_t ctrl_wait, intr_wait;

	BT_DBG("session %p", session);

	if (session->input) {
		vendor  = session->input->id.vendor;
		product = session->input->id.product;
	}

	if (session->hid) {
		vendor  = session->hid->vendor;
		product = session->hid->product;
	}

	daemonize("khidpd_%04x%04x", vendor, product);
	set_user_nice(current, -15);

	init_waitqueue_entry(&ctrl_wait, current);
	init_waitqueue_entry(&intr_wait, current);
	add_wait_queue(ctrl_sk->sk_sleep, &ctrl_wait);
	add_wait_queue(intr_sk->sk_sleep, &intr_wait);
	while (!atomic_read(&session->terminate)) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (ctrl_sk->sk_state != BT_CONNECTED || intr_sk->sk_state != BT_CONNECTED)
			break;

		while ((skb = skb_dequeue(&ctrl_sk->sk_receive_queue))) {
			skb_orphan(skb);
			hidp_recv_ctrl_frame(session, skb);
		}

		while ((skb = skb_dequeue(&intr_sk->sk_receive_queue))) {
			skb_orphan(skb);
			hidp_recv_intr_frame(session, skb);
		}

		hidp_process_transmit(session);

		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(intr_sk->sk_sleep, &intr_wait);
	remove_wait_queue(ctrl_sk->sk_sleep, &ctrl_wait);

	down_write(&hidp_session_sem);

	hidp_del_timer(session);

	if (session->input) {
		input_unregister_device(session->input);
		session->input = NULL;
	}

	if (session->hid) {
		hid_destroy_device(session->hid);
		session->hid = NULL;
	}

	/* Wakeup user-space polling for socket errors */
	session->intr_sock->sk->sk_err = EUNATCH;
	session->ctrl_sock->sk->sk_err = EUNATCH;

	hidp_schedule(session);

	fput(session->intr_sock->file);

	wait_event_timeout(*(ctrl_sk->sk_sleep),
		(ctrl_sk->sk_state == BT_CLOSED), msecs_to_jiffies(500));

	fput(session->ctrl_sock->file);

	__hidp_unlink_session(session);

	up_write(&hidp_session_sem);

	kfree(session);
	return 0;
}