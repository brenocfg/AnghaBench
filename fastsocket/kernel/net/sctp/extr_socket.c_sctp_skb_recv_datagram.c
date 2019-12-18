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
struct sock {int sk_shutdown; TYPE_1__ sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int MSG_PEEK ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_wait_for_packet (struct sock*,int*,long*) ; 
 struct sk_buff* skb_dequeue (TYPE_1__*) ; 
 struct sk_buff* skb_peek (TYPE_1__*) ; 
 int sock_error (struct sock*) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *sctp_skb_recv_datagram(struct sock *sk, int flags,
					      int noblock, int *err)
{
	int error;
	struct sk_buff *skb;
	long timeo;

	timeo = sock_rcvtimeo(sk, noblock);

	SCTP_DEBUG_PRINTK("Timeout: timeo: %ld, MAX: %ld.\n",
			  timeo, MAX_SCHEDULE_TIMEOUT);

	do {
		/* Again only user level code calls this function,
		 * so nothing interrupt level
		 * will suddenly eat the receive_queue.
		 *
		 *  Look at current nfs client by the way...
		 *  However, this function was corrent in any case. 8)
		 */
		if (flags & MSG_PEEK) {
			spin_lock_bh(&sk->sk_receive_queue.lock);
			skb = skb_peek(&sk->sk_receive_queue);
			if (skb)
				atomic_inc(&skb->users);
			spin_unlock_bh(&sk->sk_receive_queue.lock);
		} else {
			skb = skb_dequeue(&sk->sk_receive_queue);
		}

		if (skb)
			return skb;

		/* Caller is allowed not to check sk->sk_err before calling. */
		error = sock_error(sk);
		if (error)
			goto no_packet;

		if (sk->sk_shutdown & RCV_SHUTDOWN)
			break;

		/* User doesn't want to wait.  */
		error = -EAGAIN;
		if (!timeo)
			goto no_packet;
	} while (sctp_wait_for_packet(sk, err, &timeo) == 0);

	return NULL;

no_packet:
	*err = error;
	return NULL;
}