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
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_no_check; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_IPX ; 
 scalar_t__ SOCK_DGRAM ; 
 struct net init_net ; 
 int /*<<< orphan*/  ipx_dgram_ops ; 
 int /*<<< orphan*/  ipx_proto ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int ipx_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	int rc = -ESOCKTNOSUPPORT;
	struct sock *sk;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	/*
	 * SPX support is not anymore in the kernel sources. If you want to
	 * ressurrect it, completing it and making it understand shared skbs,
	 * be fully multithreaded, etc, grab the sources in an early 2.5 kernel
	 * tree.
	 */
	if (sock->type != SOCK_DGRAM)
		goto out;

	rc = -ENOMEM;
	sk = sk_alloc(net, PF_IPX, GFP_KERNEL, &ipx_proto);
	if (!sk)
		goto out;

	sk_refcnt_debug_inc(sk);
	sock_init_data(sock, sk);
	sk->sk_no_check = 1;		/* Checksum off by default */
	sock->ops = &ipx_dgram_ops;
	rc = 0;
out:
	return rc;
}