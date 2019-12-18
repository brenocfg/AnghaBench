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
struct socket {int dummy; } ;
struct sock_xprt {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/  xprt_net; } ;

/* Variables and functions */
 struct socket* ERR_PTR (int) ; 
 int __sock_create (int /*<<< orphan*/ ,int,int,int,struct socket**,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int xs_bind (struct sock_xprt*,struct socket*) ; 
 int /*<<< orphan*/  xs_reclassify_socket (int,struct socket*) ; 

__attribute__((used)) static struct socket *xs_create_sock(struct rpc_xprt *xprt,
		struct sock_xprt *transport, int family, int type, int protocol)
{
	struct socket *sock;
	int err;

	err = __sock_create(xprt->xprt_net, family, type, protocol, &sock, 1);
	if (err < 0) {
		dprintk("RPC:       can't create %d transport socket (%d).\n",
				protocol, -err);
		goto out;
	}
	xs_reclassify_socket(family, sock);

	err = xs_bind(transport, sock);
	if (err) {
		sock_release(sock);
		goto out;
	}

	return sock;
out:
	return ERR_PTR(err);
}