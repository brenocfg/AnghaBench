#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct sock {TYPE_1__ sk_timer; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ROSE_STATE_0 ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rose_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  rose_destroy_timer ; 
 int /*<<< orphan*/  rose_remove_socket (struct sock*) ; 
 TYPE_2__* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  setup_timer (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ sk_has_allocations (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

void rose_destroy_socket(struct sock *sk)
{
	struct sk_buff *skb;

	rose_remove_socket(sk);
	rose_stop_heartbeat(sk);
	rose_stop_idletimer(sk);
	rose_stop_timer(sk);

	rose_clear_queues(sk);		/* Flush the queues */

	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		if (skb->sk != sk) {	/* A pending connection */
			/* Queue the unaccepted socket for death */
			sock_set_flag(skb->sk, SOCK_DEAD);
			rose_start_heartbeat(skb->sk);
			rose_sk(skb->sk)->state = ROSE_STATE_0;
		}

		kfree_skb(skb);
	}

	if (sk_has_allocations(sk)) {
		/* Defer: outstanding buffers */
		setup_timer(&sk->sk_timer, rose_destroy_timer,
				(unsigned long)sk);
		sk->sk_timer.expires  = jiffies + 10 * HZ;
		add_timer(&sk->sk_timer);
	} else
		sock_put(sk);
}