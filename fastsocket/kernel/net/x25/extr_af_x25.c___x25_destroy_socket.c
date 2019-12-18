#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct sock {TYPE_2__ sk_timer; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  X25_STATE_0 ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ sk_has_allocations (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  x25_destroy_timer ; 
 int /*<<< orphan*/  x25_remove_socket (struct sock*) ; 
 TYPE_1__* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_timer (struct sock*) ; 

__attribute__((used)) static void __x25_destroy_socket(struct sock *sk)
{
	struct sk_buff *skb;

	x25_stop_heartbeat(sk);
	x25_stop_timer(sk);

	x25_remove_socket(sk);
	x25_clear_queues(sk);		/* Flush the queues */

	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		if (skb->sk != sk) {		/* A pending connection */
			/*
			 * Queue the unaccepted socket for death
			 */
			sock_set_flag(skb->sk, SOCK_DEAD);
			x25_start_heartbeat(skb->sk);
			x25_sk(skb->sk)->state = X25_STATE_0;
		}

		kfree_skb(skb);
	}

	if (sk_has_allocations(sk)) {
		/* Defer: outstanding buffers */
		sk->sk_timer.expires  = jiffies + 10 * HZ;
		sk->sk_timer.function = x25_destroy_timer;
		sk->sk_timer.data = (unsigned long)sk;
		add_timer(&sk->sk_timer);
	} else {
		/* drop last reference so sock_put will free */
		__sock_put(sk);
	}
}