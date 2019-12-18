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
struct sock {int dummy; } ;
struct netns_pfkey {int /*<<< orphan*/  table; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct netns_pfkey* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_net_id ; 
 int /*<<< orphan*/  pfkey_table_grab () ; 
 int /*<<< orphan*/  pfkey_table_ungrab () ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 struct net* sock_net (struct sock*) ; 

__attribute__((used)) static void pfkey_insert(struct sock *sk)
{
	struct net *net = sock_net(sk);
	struct netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	pfkey_table_grab();
	sk_add_node(sk, &net_pfkey->table);
	pfkey_table_ungrab();
}