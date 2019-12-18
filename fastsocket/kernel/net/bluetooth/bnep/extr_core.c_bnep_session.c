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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct bnep_session {TYPE_1__* sock; int /*<<< orphan*/  killed; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  EUNATCH ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __bnep_unlink_session (struct bnep_session*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_rx_frame (struct bnep_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 scalar_t__ bnep_tx_frame (struct bnep_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  daemonize (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnep_session(void *arg)
{
	struct bnep_session *s = arg;
	struct net_device *dev = s->dev;
	struct sock *sk = s->sock->sk;
	struct sk_buff *skb;
	wait_queue_t wait;

	BT_DBG("");

	daemonize("kbnepd %s", dev->name);
	set_user_nice(current, -15);

	init_waitqueue_entry(&wait, current);
	add_wait_queue(sk->sk_sleep, &wait);
	while (!atomic_read(&s->killed)) {
		set_current_state(TASK_INTERRUPTIBLE);

		// RX
		while ((skb = skb_dequeue(&sk->sk_receive_queue))) {
			skb_orphan(skb);
			bnep_rx_frame(s, skb);
		}

		if (sk->sk_state != BT_CONNECTED)
			break;

		// TX
		while ((skb = skb_dequeue(&sk->sk_write_queue)))
			if (bnep_tx_frame(s, skb))
				break;
		netif_wake_queue(dev);

		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(sk->sk_sleep, &wait);

	/* Cleanup session */
	down_write(&bnep_session_sem);

	/* Delete network device */
	unregister_netdev(dev);

	/* Wakeup user-space polling for socket errors */
	s->sock->sk->sk_err = EUNATCH;

	wake_up_interruptible(s->sock->sk->sk_sleep);

	/* Release the socket */
	fput(s->sock->file);

	__bnep_unlink_session(s);

	up_write(&bnep_session_sem);
	free_netdev(dev);
	return 0;
}