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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  sk_rmem_alloc; struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int len; scalar_t__ dropcount; int /*<<< orphan*/ * dev; int /*<<< orphan*/  truesize; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int sk_filter (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_rmem_schedule (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 
 int /*<<< orphan*/  trace_sock_rcvqueue_full (struct sock*,struct sk_buff*) ; 

int sock_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	int err = 0;
	int skb_len;
	unsigned long flags;
	struct sk_buff_head *list = &sk->sk_receive_queue;

	if (atomic_read(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf) {
		err = -ENOMEM;
		trace_sock_rcvqueue_full(sk, skb);
		goto out;
	}

	err = sk_filter(sk, skb);
	if (err)
		goto out;

	if (!sk_rmem_schedule(sk, skb->truesize)) {
		err = -ENOBUFS;
		goto out;
	}

	skb->dev = NULL;
	skb_set_owner_r(skb, sk);

	/* Cache the SKB length before we tack it onto the receive
	 * queue.  Once it is added it no longer belongs to us and
	 * may be freed by other threads of control pulling packets
	 * from the queue.
	 */
	skb_len = skb->len;

	spin_lock_irqsave(&list->lock, flags);
	skb->dropcount = atomic_read(&sk->sk_drops);
	__skb_queue_tail(list, skb);
	spin_unlock_irqrestore(&list->lock, flags);

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk, skb_len);
out:
	return err;
}