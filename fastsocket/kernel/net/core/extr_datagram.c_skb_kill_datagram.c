#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_1__ sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int ENOENT ; 
 unsigned int MSG_PEEK ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mem_reclaim_partial (struct sock*) ; 
 struct sk_buff* skb_peek (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int skb_kill_datagram(struct sock *sk, struct sk_buff *skb, unsigned int flags)
{
	int err = 0;

	if (flags & MSG_PEEK) {
		err = -ENOENT;
		spin_lock_bh(&sk->sk_receive_queue.lock);
		if (skb == skb_peek(&sk->sk_receive_queue)) {
			__skb_unlink(skb, &sk->sk_receive_queue);
			atomic_dec(&skb->users);
			err = 0;
		}
		spin_unlock_bh(&sk->sk_receive_queue.lock);
	}

	kfree_skb(skb);
	sk_mem_reclaim_partial(sk);

	return err;
}