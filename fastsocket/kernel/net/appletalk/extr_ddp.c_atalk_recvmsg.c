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
struct TYPE_2__ {int /*<<< orphan*/  s_net; int /*<<< orphan*/  s_node; } ;
struct sockaddr_at {TYPE_1__ sat_addr; int /*<<< orphan*/  sat_port; int /*<<< orphan*/  sat_family; } ;
struct sock {scalar_t__ sk_type; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_namelen; struct sockaddr_at* msg_name; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; } ;
struct kiocb {int dummy; } ;
struct ddpehdr {int /*<<< orphan*/  deh_snet; int /*<<< orphan*/  deh_snode; int /*<<< orphan*/  deh_sport; int /*<<< orphan*/  deh_len_hops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_APPLETALK ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 scalar_t__ SOCK_RAW ; 
 struct ddpehdr* ddp_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 

__attribute__((used)) static int atalk_recvmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg,
			 size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct ddpehdr *ddp;
	int copied = 0;
	int offset = 0;
	int err = 0;
	struct sk_buff *skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
						flags & MSG_DONTWAIT, &err);

	msg->msg_namelen = 0;
	if (!skb)
		return err;

	/* FIXME: use skb->cb to be able to use shared skbs */
	ddp = ddp_hdr(skb);
	copied = ntohs(ddp->deh_len_hops) & 1023;

	if (sk->sk_type != SOCK_RAW) {
		offset = sizeof(*ddp);
		copied -= offset;
	}

	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}
	err = skb_copy_datagram_iovec(skb, offset, msg->msg_iov, copied);

	if (!err && msg->msg_name) {
		struct sockaddr_at *sat = msg->msg_name;
		sat->sat_family      = AF_APPLETALK;
		sat->sat_port        = ddp->deh_sport;
		sat->sat_addr.s_node = ddp->deh_snode;
		sat->sat_addr.s_net  = ddp->deh_snet;
		msg->msg_namelen     = sizeof(*sat);
	}

	skb_free_datagram(sk, skb);	/* Free the datagram. */
	return err ? : copied;
}