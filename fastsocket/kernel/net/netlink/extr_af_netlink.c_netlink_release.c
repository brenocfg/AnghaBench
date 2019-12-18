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
struct sock {size_t sk_protocol; int /*<<< orphan*/  sk_write_queue; } ;
struct netlink_sock {int /*<<< orphan*/ * groups; scalar_t__ subscriptions; int /*<<< orphan*/  module; scalar_t__ pid; int /*<<< orphan*/  wait; } ;
struct netlink_notify {size_t protocol; scalar_t__ pid; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {scalar_t__ registered; int /*<<< orphan*/ * module; int /*<<< orphan*/ * listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NETLINK_URELEASE ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_notify*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_chain ; 
 scalar_t__ netlink_is_kernel (struct sock*) ; 
 int /*<<< orphan*/  netlink_proto ; 
 int /*<<< orphan*/  netlink_remove (struct sock*) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 int /*<<< orphan*/  netlink_update_listeners (struct sock*) ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlink_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk;

	if (!sk)
		return 0;

	netlink_remove(sk);
	sock_orphan(sk);
	nlk = nlk_sk(sk);

	/*
	 * OK. Socket is unlinked, any packets that arrive now
	 * will be purged.
	 */

	sock->sk = NULL;
	wake_up_interruptible_all(&nlk->wait);

	skb_queue_purge(&sk->sk_write_queue);

	if (nlk->pid && !nlk->subscriptions) {
		struct netlink_notify n = {
						.net = sock_net(sk),
						.protocol = sk->sk_protocol,
						.pid = nlk->pid,
					  };
		atomic_notifier_call_chain(&netlink_chain,
				NETLINK_URELEASE, &n);
	}

	module_put(nlk->module);

	netlink_table_grab();
	if (netlink_is_kernel(sk)) {
		BUG_ON(nl_table[sk->sk_protocol].registered == 0);
		if (--nl_table[sk->sk_protocol].registered == 0) {
			kfree(nl_table[sk->sk_protocol].listeners);
			nl_table[sk->sk_protocol].module = NULL;
			nl_table[sk->sk_protocol].registered = 0;
		}
	} else if (nlk->subscriptions)
		netlink_update_listeners(sk);
	netlink_table_ungrab();

	kfree(nlk->groups);
	nlk->groups = NULL;

	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), &netlink_proto, -1);
	local_bh_enable();
	sock_put(sk);
	return 0;
}