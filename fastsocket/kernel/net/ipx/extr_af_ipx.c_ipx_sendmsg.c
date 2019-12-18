#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_ipx {scalar_t__ sipx_family; int /*<<< orphan*/  sipx_node; scalar_t__ sipx_network; scalar_t__ sipx_port; int /*<<< orphan*/  sipx_type; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct msghdr {int msg_flags; int msg_namelen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct ipxhdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; scalar_t__ net; scalar_t__ sock; } ;
struct ipx_sock {TYPE_2__ dest_addr; int /*<<< orphan*/  type; TYPE_1__* intrfc; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_node; } ;

/* Variables and functions */
 scalar_t__ AF_IPX ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  IPX_NODE_LEN ; 
 int MSG_CMSG_COMPAT ; 
 int MSG_DONTWAIT ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int ipx_bind (struct socket*,struct sockaddr*,int) ; 
 struct ipx_sock* ipx_sk (struct sock*) ; 
 int ipxrtr_route_packet (struct sock*,struct sockaddr_ipx*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipx_sendmsg(struct kiocb *iocb, struct socket *sock,
	struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
	struct ipx_sock *ipxs = ipx_sk(sk);
	struct sockaddr_ipx *usipx = (struct sockaddr_ipx *)msg->msg_name;
	struct sockaddr_ipx local_sipx;
	int rc = -EINVAL;
	int flags = msg->msg_flags;

	/* Socket gets bound below anyway */
/*	if (sk->sk_zapped)
		return -EIO; */	/* Socket not bound */
	if (flags & ~(MSG_DONTWAIT|MSG_CMSG_COMPAT))
		goto out;

	/* Max possible packet size limited by 16 bit pktsize in header */
	if (len >= 65535 - sizeof(struct ipxhdr))
		goto out;

	if (usipx) {
		if (!ipxs->port) {
			struct sockaddr_ipx uaddr;

			uaddr.sipx_port		= 0;
			uaddr.sipx_network	= 0;
#ifdef CONFIG_IPX_INTERN
			rc = -ENETDOWN;
			if (!ipxs->intrfc)
				goto out; /* Someone zonked the iface */
			memcpy(uaddr.sipx_node, ipxs->intrfc->if_node,
				IPX_NODE_LEN);
#endif
			rc = ipx_bind(sock, (struct sockaddr *)&uaddr,
					sizeof(struct sockaddr_ipx));
			if (rc)
				goto out;
		}

		rc = -EINVAL;
		if (msg->msg_namelen < sizeof(*usipx) ||
		    usipx->sipx_family != AF_IPX)
			goto out;
	} else {
		rc = -ENOTCONN;
		if (sk->sk_state != TCP_ESTABLISHED)
			goto out;

		usipx = &local_sipx;
		usipx->sipx_family 	= AF_IPX;
		usipx->sipx_type 	= ipxs->type;
		usipx->sipx_port 	= ipxs->dest_addr.sock;
		usipx->sipx_network 	= ipxs->dest_addr.net;
		memcpy(usipx->sipx_node, ipxs->dest_addr.node, IPX_NODE_LEN);
	}

	rc = ipxrtr_route_packet(sk, usipx, msg->msg_iov, len,
				 flags & MSG_DONTWAIT);
	if (rc >= 0)
		rc = len;
out:
	return rc;
}