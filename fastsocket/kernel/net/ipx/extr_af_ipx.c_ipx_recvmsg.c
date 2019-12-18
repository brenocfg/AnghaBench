#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_ipx {scalar_t__ sipx_zero; int /*<<< orphan*/  sipx_type; scalar_t__ sipx_network; int /*<<< orphan*/  sipx_node; scalar_t__ sipx_port; int /*<<< orphan*/  sipx_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {scalar_t__ tv64; } ;
struct sock {TYPE_2__ sk_stamp; } ;
struct sk_buff {TYPE_2__ tstamp; } ;
struct msghdr {int msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; scalar_t__ sock; } ;
struct ipxhdr {int /*<<< orphan*/  ipx_type; TYPE_3__ ipx_source; int /*<<< orphan*/  ipx_pktsize; } ;
struct ipx_sock {TYPE_1__* intrfc; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {scalar_t__ ipx_source_net; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IPX ; 
 int ENETDOWN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  IPX_NODE_LEN ; 
 TYPE_4__* IPX_SKB_CB (struct sk_buff*) ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int ipx_bind (struct socket*,struct sockaddr*,int) ; 
 struct ipxhdr* ipx_hdr (struct sk_buff*) ; 
 struct ipx_sock* ipx_sk (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipx_recvmsg(struct kiocb *iocb, struct socket *sock,
		struct msghdr *msg, size_t size, int flags)
{
	struct sock *sk = sock->sk;
	struct ipx_sock *ipxs = ipx_sk(sk);
	struct sockaddr_ipx *sipx = (struct sockaddr_ipx *)msg->msg_name;
	struct ipxhdr *ipx = NULL;
	struct sk_buff *skb;
	int copied, rc;

	msg->msg_namelen = 0;

	/* put the autobinding in */
	if (!ipxs->port) {
		struct sockaddr_ipx uaddr;

		uaddr.sipx_port		= 0;
		uaddr.sipx_network 	= 0;

#ifdef CONFIG_IPX_INTERN
		rc = -ENETDOWN;
		if (!ipxs->intrfc)
			goto out; /* Someone zonked the iface */
		memcpy(uaddr.sipx_node, ipxs->intrfc->if_node, IPX_NODE_LEN);
#endif	/* CONFIG_IPX_INTERN */

		rc = ipx_bind(sock, (struct sockaddr *)&uaddr,
			      sizeof(struct sockaddr_ipx));
		if (rc)
			goto out;
	}

	rc = -ENOTCONN;
	if (sock_flag(sk, SOCK_ZAPPED))
		goto out;

	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
				flags & MSG_DONTWAIT, &rc);
	if (!skb)
		goto out;

	ipx 	= ipx_hdr(skb);
	copied 	= ntohs(ipx->ipx_pktsize) - sizeof(struct ipxhdr);
	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}

	rc = skb_copy_datagram_iovec(skb, sizeof(struct ipxhdr), msg->msg_iov,
				     copied);
	if (rc)
		goto out_free;
	if (skb->tstamp.tv64)
		sk->sk_stamp = skb->tstamp;

	if (sipx) {
		sipx->sipx_family	= AF_IPX;
		sipx->sipx_port		= ipx->ipx_source.sock;
		memcpy(sipx->sipx_node, ipx->ipx_source.node, IPX_NODE_LEN);
		sipx->sipx_network	= IPX_SKB_CB(skb)->ipx_source_net;
		sipx->sipx_type 	= ipx->ipx_type;
		sipx->sipx_zero		= 0;
		msg->msg_namelen	= sizeof(*sipx);
	}
	rc = copied;

out_free:
	skb_free_datagram(sk, skb);
out:
	return rc;
}