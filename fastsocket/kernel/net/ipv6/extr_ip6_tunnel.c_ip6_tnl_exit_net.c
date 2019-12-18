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
struct net {int dummy; } ;
struct ip6_tnl_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_tnl_destroy_tunnels (struct ip6_tnl_net*) ; 
 int /*<<< orphan*/  ip6_tnl_net_id ; 
 int /*<<< orphan*/  kfree (struct ip6_tnl_net*) ; 
 struct ip6_tnl_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void ip6_tnl_exit_net(struct net *net)
{
	struct ip6_tnl_net *ip6n;

	ip6n = net_generic(net, ip6_tnl_net_id);
	rtnl_lock();
	ip6_tnl_destroy_tunnels(ip6n);
	rtnl_unlock();
	kfree(ip6n);
}