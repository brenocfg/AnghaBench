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
struct sk_buff {int peeked; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned int MSG_DONTWAIT ; 
 unsigned int MSG_PEEK ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (TYPE_1__*) ; 
 int sock_error (struct sock*) ; 
 long sock_rcvtimeo (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_packet (struct sock*,int*,long*) ; 

struct sk_buff *__skb_recv_datagram(struct sock *sk, unsigned flags,
				    int *peeked, int *err)
{
	struct sk_buff *skb;
	long timeo;
	/*
	 * Caller is allowed not to check sk->sk_err before skb_recv_datagram()
	 */
	int error = sock_error(sk);

	if (error)
		goto no_packet;

	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);

	do {
		/* Again only user level code calls this function, so nothing
		 * interrupt level will suddenly eat the receive_queue.
		 *
		 * Look at current nfs client by the way...
		 * However, this function was corrent in any case. 8)
		 */
		unsigned long cpu_flags;

		spin_lock_irqsave(&sk->sk_receive_queue.lock, cpu_flags);
		skb = skb_peek(&sk->sk_receive_queue);
		if (skb) {
			*peeked = skb->peeked;
			if (flags & MSG_PEEK) {
				skb->peeked = 1;
				atomic_inc(&skb->users);
			} else
				__skb_unlink(skb, &sk->sk_receive_queue);
		}
		spin_unlock_irqrestore(&sk->sk_receive_queue.lock, cpu_flags);

		if (skb)
			return skb;

		/* User doesn't want to wait */
		error = -EAGAIN;
		if (!timeo)
			goto no_packet;

	} while (!wait_for_packet(sk, err, &timeo));

	return NULL;

no_packet:
	*err = error;
	return NULL;
}