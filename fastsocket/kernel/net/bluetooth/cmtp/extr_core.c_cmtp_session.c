#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct cmtp_session {int flags; TYPE_1__* sock; int /*<<< orphan*/  terminate; int /*<<< orphan*/  num; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*) ; 
 int CMTP_LOOPBACK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __cmtp_unlink_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_detach_device (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_process_transmit (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_recv_frame (struct cmtp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  daemonize (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmtp_session*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmtp_session(void *arg)
{
	struct cmtp_session *session = arg;
	struct sock *sk = session->sock->sk;
	struct sk_buff *skb;
	wait_queue_t wait;

	BT_DBG("session %p", session);

	daemonize("kcmtpd_ctr_%d", session->num);
	set_user_nice(current, -15);

	init_waitqueue_entry(&wait, current);
	add_wait_queue(sk->sk_sleep, &wait);
	while (!atomic_read(&session->terminate)) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (sk->sk_state != BT_CONNECTED)
			break;

		while ((skb = skb_dequeue(&sk->sk_receive_queue))) {
			skb_orphan(skb);
			cmtp_recv_frame(session, skb);
		}

		cmtp_process_transmit(session);

		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(sk->sk_sleep, &wait);

	down_write(&cmtp_session_sem);

	if (!(session->flags & (1 << CMTP_LOOPBACK)))
		cmtp_detach_device(session);

	fput(session->sock->file);

	__cmtp_unlink_session(session);

	up_write(&cmtp_session_sem);

	kfree(session);
	return 0;
}