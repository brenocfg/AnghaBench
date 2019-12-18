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
struct socket {struct sock* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  ax25_call; } ;
struct sockaddr_ax25 {TYPE_1__ sax25_call; int /*<<< orphan*/  sax25_family; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {size_t len; } ;
struct msghdr {int msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETROM ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 int ENOTCONN ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int nr_recvmsg(struct kiocb *iocb, struct socket *sock,
		      struct msghdr *msg, size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct sockaddr_ax25 *sax = (struct sockaddr_ax25 *)msg->msg_name;
	size_t copied;
	struct sk_buff *skb;
	int er;

	/*
	 * This works for seqpacket too. The receiver has ordered the queue for
	 * us! We do one quick check first though
	 */

	lock_sock(sk);
	if (sk->sk_state != TCP_ESTABLISHED) {
		release_sock(sk);
		return -ENOTCONN;
	}

	msg->msg_namelen = 0;

	/* Now we can treat all alike */
	if ((skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT, flags & MSG_DONTWAIT, &er)) == NULL) {
		release_sock(sk);
		return er;
	}

	skb_reset_transport_header(skb);
	copied     = skb->len;

	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}

	skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copied);

	if (sax != NULL) {
		sax->sax25_family = AF_NETROM;
		skb_copy_from_linear_data_offset(skb, 7, sax->sax25_call.ax25_call,
			      AX25_ADDR_LEN);
		msg->msg_namelen = sizeof(*sax);
	}

	skb_free_datagram(sk, skb);

	release_sock(sk);
	return copied;
}