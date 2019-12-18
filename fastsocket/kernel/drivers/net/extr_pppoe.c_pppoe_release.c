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
struct sock {int sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote; int /*<<< orphan*/  sid; } ;
struct pppox_sock {int /*<<< orphan*/  pppoe_ifindex; TYPE_1__ pppoe_pa; int /*<<< orphan*/ * pppoe_dev; } ;
struct pppoe_net {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int PPPOX_BOUND ; 
 int PPPOX_CONNECTED ; 
 int PPPOX_DEAD ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  delete_item (struct pppoe_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pppoe_net* pppoe_pernet (struct net*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int pppoe_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct pppox_sock *po;
	struct pppoe_net *pn;
	struct net *net = NULL;

	if (!sk)
		return 0;

	lock_sock(sk);
	if (sock_flag(sk, SOCK_DEAD)) {
		release_sock(sk);
		return -EBADF;
	}

	po = pppox_sk(sk);

	if (sk->sk_state & (PPPOX_CONNECTED | PPPOX_BOUND)) {
		dev_put(po->pppoe_dev);
		po->pppoe_dev = NULL;
	}

	pppox_unbind_sock(sk);

	/* Signal the death of the socket. */
	sk->sk_state = PPPOX_DEAD;

	net = sock_net(sk);
	pn = pppoe_pernet(net);

	/*
	 * protect "po" from concurrent updates
	 * on pppoe_flush_dev
	 */
	delete_item(pn, po->pppoe_pa.sid, po->pppoe_pa.remote,
		    po->pppoe_ifindex);

	sock_orphan(sk);
	sock->sk = NULL;

	skb_queue_purge(&sk->sk_receive_queue);
	release_sock(sk);
	sock_put(sk);

	return 0;
}