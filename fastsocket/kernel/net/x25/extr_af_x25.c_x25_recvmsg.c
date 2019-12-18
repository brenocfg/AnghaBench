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
struct x25_sock {int /*<<< orphan*/  dest_addr; scalar_t__ qbitincl; TYPE_1__* neighbour; int /*<<< orphan*/  interrupt_in_queue; } ;
struct socket {struct sock* sk; } ;
struct sockaddr_x25 {int /*<<< orphan*/  sx25_addr; int /*<<< orphan*/  sx25_family; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int* data; size_t len; } ;
struct msghdr {int msg_namelen; int msg_flags; int /*<<< orphan*/  msg_iov; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct TYPE_2__ {scalar_t__ extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_X25 ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_OOB ; 
 int MSG_TRUNC ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  X25_EXT_MIN_LEN ; 
 int X25_Q_BIT ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_check_rbuf (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_recvmsg(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *msg, size_t size,
		       int flags)
{
	struct sock *sk = sock->sk;
	struct x25_sock *x25 = x25_sk(sk);
	struct sockaddr_x25 *sx25 = (struct sockaddr_x25 *)msg->msg_name;
	size_t copied;
	int qbit;
	struct sk_buff *skb;
	unsigned char *asmptr;
	int rc = -ENOTCONN;

	/*
	 * This works for seqpacket too. The receiver has ordered the queue for
	 * us! We do one quick check first though
	 */
	if (sk->sk_state != TCP_ESTABLISHED)
		goto out;

	msg->msg_namelen = 0;
	if (flags & MSG_OOB) {
		rc = -EINVAL;
		if (sock_flag(sk, SOCK_URGINLINE) ||
		    !skb_peek(&x25->interrupt_in_queue))
			goto out;

		skb = skb_dequeue(&x25->interrupt_in_queue);

		skb_pull(skb, X25_STD_MIN_LEN);

		/*
		 *	No Q bit information on Interrupt data.
		 */
		if (x25->qbitincl) {
			asmptr  = skb_push(skb, 1);
			*asmptr = 0x00;
		}

		msg->msg_flags |= MSG_OOB;
	} else {
		/* Now we can treat all alike */
		skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
					flags & MSG_DONTWAIT, &rc);
		if (!skb)
			goto out;

		qbit = (skb->data[0] & X25_Q_BIT) == X25_Q_BIT;

		skb_pull(skb, x25->neighbour->extended ?
				X25_EXT_MIN_LEN : X25_STD_MIN_LEN);

		if (x25->qbitincl) {
			asmptr  = skb_push(skb, 1);
			*asmptr = qbit;
		}
	}

	skb_reset_transport_header(skb);
	copied = skb->len;

	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}

	/* Currently, each datagram always contains a complete record */
	msg->msg_flags |= MSG_EOR;

	rc = skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copied);
	if (rc)
		goto out_free_dgram;

	if (sx25) {
		sx25->sx25_family = AF_X25;
		sx25->sx25_addr   = x25->dest_addr;
		msg->msg_namelen = sizeof(*sx25);
	}

	lock_sock(sk);
	x25_check_rbuf(sk);
	release_sock(sk);
	rc = copied;
out_free_dgram:
	skb_free_datagram(sk, skb);
out:
	return rc;
}