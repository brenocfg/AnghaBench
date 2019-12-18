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
struct socket {scalar_t__ type; int /*<<< orphan*/  sk; int /*<<< orphan*/  state; } ;
struct netlink_sock {struct module* module; } ;
struct net {int dummy; } ;
struct mutex {int dummy; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct mutex* cb_mutex; struct module* module; scalar_t__ registered; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int MAX_LINKS ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int __netlink_create (struct net*,struct socket*,struct mutex*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  netlink_lock_table () ; 
 int /*<<< orphan*/  netlink_proto ; 
 int /*<<< orphan*/  netlink_unlock_table () ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ try_module_get (struct module*) ; 

__attribute__((used)) static int netlink_create(struct net *net, struct socket *sock, int protocol,
			  int kern)
{
	struct module *module = NULL;
	struct mutex *cb_mutex;
	struct netlink_sock *nlk;
	int err = 0;

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_RAW && sock->type != SOCK_DGRAM)
		return -ESOCKTNOSUPPORT;

	if (protocol < 0 || protocol >= MAX_LINKS)
		return -EPROTONOSUPPORT;

	netlink_lock_table();
#ifdef CONFIG_MODULES
	if (!nl_table[protocol].registered) {
		netlink_unlock_table();
		request_module("net-pf-%d-proto-%d", PF_NETLINK, protocol);
		netlink_lock_table();
	}
#endif
	if (nl_table[protocol].registered &&
	    try_module_get(nl_table[protocol].module))
		module = nl_table[protocol].module;
	else
		err = -EPROTONOSUPPORT;
	cb_mutex = nl_table[protocol].cb_mutex;
	netlink_unlock_table();

	if (err < 0)
		goto out;

	err = __netlink_create(net, sock, cb_mutex, protocol);
	if (err < 0)
		goto out_module;

	local_bh_disable();
	sock_prot_inuse_add(net, &netlink_proto, 1);
	local_bh_enable();

	nlk = nlk_sk(sock->sk);
	nlk->module = module;
out:
	return err;

out_module:
	module_put(module);
	goto out;
}