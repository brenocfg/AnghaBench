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
struct sock {int /*<<< orphan*/  sk_data_ready; } ;
struct netlink_sock {void (* netlink_rcv ) (struct sk_buff*) ;int /*<<< orphan*/  flags; } ;
struct net {int dummy; } ;
struct mutex {int dummy; } ;
struct module {int dummy; } ;
struct listeners_rcu_head {int dummy; } ;
struct TYPE_2__ {int registered; unsigned int groups; unsigned long* listeners; struct module* module; struct mutex* cb_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_LINKS ; 
 int /*<<< orphan*/  NETLINK_KERNEL_SOCKET ; 
 scalar_t__ NLGRPSZ (unsigned int) ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ __netlink_create (int /*<<< orphan*/ *,struct socket*,struct mutex*,int) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_data_ready ; 
 scalar_t__ netlink_insert (struct sock*,struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_kernel_release (struct sock*) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_change_net (struct sock*,struct net*) ; 
 scalar_t__ sock_create_lite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

struct sock *
netlink_kernel_create(struct net *net, int unit, unsigned int groups,
		      void (*input)(struct sk_buff *skb),
		      struct mutex *cb_mutex, struct module *module)
{
	struct socket *sock;
	struct sock *sk;
	struct netlink_sock *nlk;
	unsigned long *listeners = NULL;

	BUG_ON(!nl_table);

	if (unit < 0 || unit >= MAX_LINKS)
		return NULL;

	if (sock_create_lite(PF_NETLINK, SOCK_DGRAM, unit, &sock))
		return NULL;

	/*
	 * We have to just have a reference on the net from sk, but don't
	 * get_net it. Besides, we cannot get and then put the net here.
	 * So we create one inside init_net and the move it to net.
	 */

	if (__netlink_create(&init_net, sock, cb_mutex, unit) < 0)
		goto out_sock_release_nosk;

	sk = sock->sk;
	sk_change_net(sk, net);

	if (groups < 32)
		groups = 32;

	listeners = kzalloc(NLGRPSZ(groups) + sizeof(struct listeners_rcu_head),
			    GFP_KERNEL);
	if (!listeners)
		goto out_sock_release;

	sk->sk_data_ready = netlink_data_ready;
	if (input)
		nlk_sk(sk)->netlink_rcv = input;

	if (netlink_insert(sk, net, 0))
		goto out_sock_release;

	nlk = nlk_sk(sk);
	nlk->flags |= NETLINK_KERNEL_SOCKET;

	netlink_table_grab();
	if (!nl_table[unit].registered) {
		nl_table[unit].groups = groups;
		nl_table[unit].listeners = listeners;
		nl_table[unit].cb_mutex = cb_mutex;
		nl_table[unit].module = module;
		nl_table[unit].registered = 1;
	} else {
		kfree(listeners);
		nl_table[unit].registered++;
	}
	netlink_table_ungrab();
	return sk;

out_sock_release:
	kfree(listeners);
	netlink_kernel_release(sk);
	return NULL;

out_sock_release_nosk:
	sock_release(sock);
	return NULL;
}