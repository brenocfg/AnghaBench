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
struct socket {struct sock* sk; } ;
struct sockaddr_rose {int srose_ndigis; int /*<<< orphan*/  srose_call; int /*<<< orphan*/  srose_addr; int /*<<< orphan*/  srose_family; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int* data; size_t len; } ;
struct rose_sock {int dest_ndigis; int /*<<< orphan*/ * dest_digis; int /*<<< orphan*/  dest_call; int /*<<< orphan*/  dest_addr; scalar_t__ qbitincl; } ;
struct msghdr {int msg_namelen; struct sockaddr_rose* msg_name; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; } ;
struct kiocb {int dummy; } ;
struct full_sockaddr_rose {int /*<<< orphan*/ * srose_digis; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_ROSE ; 
 int ENOTCONN ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int /*<<< orphan*/  ROSE_MIN_LEN ; 
 int ROSE_Q_BIT ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  memset (struct sockaddr_rose*,int /*<<< orphan*/ ,int) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int rose_recvmsg(struct kiocb *iocb, struct socket *sock,
			struct msghdr *msg, size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct rose_sock *rose = rose_sk(sk);
	size_t copied;
	unsigned char *asmptr;
	struct sk_buff *skb;
	int n, er, qbit;

	/*
	 * This works for seqpacket too. The receiver has ordered the queue for
	 * us! We do one quick check first though
	 */
	if (sk->sk_state != TCP_ESTABLISHED)
		return -ENOTCONN;

	msg->msg_namelen = 0;

	/* Now we can treat all alike */
	if ((skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT, flags & MSG_DONTWAIT, &er)) == NULL)
		return er;

	qbit = (skb->data[0] & ROSE_Q_BIT) == ROSE_Q_BIT;

	skb_pull(skb, ROSE_MIN_LEN);

	if (rose->qbitincl) {
		asmptr  = skb_push(skb, 1);
		*asmptr = qbit;
	}

	skb_reset_transport_header(skb);
	copied     = skb->len;

	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}

	skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copied);

	if (msg->msg_name) {
		struct full_sockaddr_rose *full_srose = (struct full_sockaddr_rose *)msg->msg_name;
		struct sockaddr_rose *srose;

		memset(msg->msg_name, 0, sizeof(struct full_sockaddr_rose));
		srose = msg->msg_name;
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->dest_addr;
		srose->srose_call   = rose->dest_call;
		srose->srose_ndigis = rose->dest_ndigis;

		for (n = 0 ; n < rose->dest_ndigis ; n++)
			full_srose->srose_digis[n] = rose->dest_digis[n];
		msg->msg_namelen = sizeof(struct full_sockaddr_rose);
	}

	skb_free_datagram(sk, skb);

	return copied;
}