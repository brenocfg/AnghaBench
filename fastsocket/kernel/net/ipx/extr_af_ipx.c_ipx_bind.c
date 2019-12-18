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
struct sockaddr_ipx {int sipx_port; int /*<<< orphan*/  sipx_node; int /*<<< orphan*/  sipx_network; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct ipx_sock {int port; int /*<<< orphan*/  node; } ;
struct ipx_interface {int /*<<< orphan*/  if_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EACCES ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 scalar_t__ IPX_MIN_EPHEMERAL_SOCKET ; 
 int /*<<< orphan*/  IPX_NODE_LEN ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*,scalar_t__) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_broadcast_node ; 
 int ipx_first_free_socketnum (struct ipx_interface*) ; 
 struct ipx_interface* ipx_internal_net ; 
 struct ipx_sock* ipx_sk (struct sock*) ; 
 int /*<<< orphan*/  ipx_this_node ; 
 scalar_t__ ipxitf_find_internal_socket (struct ipx_interface*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipxitf_find_socket (struct ipx_interface*,int) ; 
 struct ipx_interface* ipxitf_find_using_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipxitf_insert_socket (struct ipx_interface*,struct sock*) ; 
 int /*<<< orphan*/  ipxitf_put (struct ipx_interface*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipx_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sock *sk = sock->sk;
	struct ipx_sock *ipxs = ipx_sk(sk);
	struct ipx_interface *intrfc;
	struct sockaddr_ipx *addr = (struct sockaddr_ipx *)uaddr;
	int rc = -EINVAL;

	if (!sock_flag(sk, SOCK_ZAPPED) || addr_len != sizeof(struct sockaddr_ipx))
		goto out;

	intrfc = ipxitf_find_using_net(addr->sipx_network);
	rc = -EADDRNOTAVAIL;
	if (!intrfc)
		goto out;

	if (!addr->sipx_port) {
		addr->sipx_port = ipx_first_free_socketnum(intrfc);
		rc = -EINVAL;
		if (!addr->sipx_port)
			goto out_put;
	}

	/* protect IPX system stuff like routing/sap */
	rc = -EACCES;
	if (ntohs(addr->sipx_port) < IPX_MIN_EPHEMERAL_SOCKET &&
	    !capable(CAP_NET_ADMIN))
		goto out_put;

	ipxs->port = addr->sipx_port;

#ifdef CONFIG_IPX_INTERN
	if (intrfc == ipx_internal_net) {
		/* The source address is to be set explicitly if the
		 * socket is to be bound on the internal network. If a
		 * node number 0 was specified, the default is used.
		 */

		rc = -EINVAL;
		if (!memcmp(addr->sipx_node, ipx_broadcast_node, IPX_NODE_LEN))
			goto out_put;
		if (!memcmp(addr->sipx_node, ipx_this_node, IPX_NODE_LEN))
			memcpy(ipxs->node, intrfc->if_node, IPX_NODE_LEN);
		else
			memcpy(ipxs->node, addr->sipx_node, IPX_NODE_LEN);

		rc = -EADDRINUSE;
		if (ipxitf_find_internal_socket(intrfc, ipxs->node,
						ipxs->port)) {
			SOCK_DEBUG(sk,
				"IPX: bind failed because port %X in use.\n",
				ntohs(addr->sipx_port));
			goto out_put;
		}
	} else {
		/* Source addresses are easy. It must be our
		 * network:node pair for an interface routed to IPX
		 * with the ipx routing ioctl()
		 */

		memcpy(ipxs->node, intrfc->if_node, IPX_NODE_LEN);

		rc = -EADDRINUSE;
		if (ipxitf_find_socket(intrfc, addr->sipx_port)) {
			SOCK_DEBUG(sk,
				"IPX: bind failed because port %X in use.\n",
				ntohs(addr->sipx_port));
			goto out_put;
		}
	}

#else	/* !def CONFIG_IPX_INTERN */

	/* Source addresses are easy. It must be our network:node pair for
	   an interface routed to IPX with the ipx routing ioctl() */

	rc = -EADDRINUSE;
	if (ipxitf_find_socket(intrfc, addr->sipx_port)) {
		SOCK_DEBUG(sk, "IPX: bind failed because port %X in use.\n",
				ntohs((int)addr->sipx_port));
		goto out_put;
	}

#endif	/* CONFIG_IPX_INTERN */

	ipxitf_insert_socket(intrfc, sk);
	sock_reset_flag(sk, SOCK_ZAPPED);

	rc = 0;
out_put:
	ipxitf_put(intrfc);
out:
	return rc;
}