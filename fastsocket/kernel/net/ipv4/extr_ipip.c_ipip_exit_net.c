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
struct ipip_net {int /*<<< orphan*/  fb_tunnel_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipip_destroy_tunnels (struct ipip_net*) ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  kfree (struct ipip_net*) ; 
 struct ipip_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipip_exit_net(struct net *net)
{
	struct ipip_net *ipn;

	ipn = net_generic(net, ipip_net_id);
	rtnl_lock();
	ipip_destroy_tunnels(ipn);
	unregister_netdevice(ipn->fb_tunnel_dev);
	rtnl_unlock();
	kfree(ipn);
}