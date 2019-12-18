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
struct sockaddr_ipx {scalar_t__ sipx_zero; int /*<<< orphan*/  sipx_type; int /*<<< orphan*/  sipx_family; int /*<<< orphan*/  sipx_port; struct sockaddr* sipx_node; scalar_t__ sipx_network; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct ipx_address {struct sockaddr_ipx* node; int /*<<< orphan*/  sock; scalar_t__ net; } ;
struct ipx_sock {int /*<<< orphan*/  type; int /*<<< orphan*/  port; TYPE_1__* intrfc; struct sockaddr_ipx* node; struct ipx_address dest_addr; } ;
typedef  int /*<<< orphan*/  sipx ;
struct TYPE_2__ {struct sockaddr_ipx* if_node; scalar_t__ if_netnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IPX ; 
 int ENOTCONN ; 
 int IPX_NODE_LEN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 struct ipx_sock* ipx_sk (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_ipx*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,char,int) ; 

__attribute__((used)) static int ipx_getname(struct socket *sock, struct sockaddr *uaddr,
			int *uaddr_len, int peer)
{
	struct ipx_address *addr;
	struct sockaddr_ipx sipx;
	struct sock *sk = sock->sk;
	struct ipx_sock *ipxs = ipx_sk(sk);
	int rc;

	*uaddr_len = sizeof(struct sockaddr_ipx);

	if (peer) {
		rc = -ENOTCONN;
		if (sk->sk_state != TCP_ESTABLISHED)
			goto out;

		addr = &ipxs->dest_addr;
		sipx.sipx_network	= addr->net;
		sipx.sipx_port		= addr->sock;
		memcpy(sipx.sipx_node, addr->node, IPX_NODE_LEN);
	} else {
		if (ipxs->intrfc) {
			sipx.sipx_network = ipxs->intrfc->if_netnum;
#ifdef CONFIG_IPX_INTERN
			memcpy(sipx.sipx_node, ipxs->node, IPX_NODE_LEN);
#else
			memcpy(sipx.sipx_node, ipxs->intrfc->if_node,
				IPX_NODE_LEN);
#endif	/* CONFIG_IPX_INTERN */

		} else {
			sipx.sipx_network = 0;
			memset(sipx.sipx_node, '\0', IPX_NODE_LEN);
		}

		sipx.sipx_port = ipxs->port;
	}

	sipx.sipx_family = AF_IPX;
	sipx.sipx_type	 = ipxs->type;
	sipx.sipx_zero	 = 0;
	memcpy(uaddr, &sipx, sizeof(sipx));

	rc = 0;
out:
	return rc;
}