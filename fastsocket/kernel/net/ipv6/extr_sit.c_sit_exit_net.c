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
struct sit_net {int /*<<< orphan*/  fb_tunnel_dev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sit_net*) ; 
 struct sit_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sit_destroy_tunnels (struct sit_net*) ; 
 int /*<<< orphan*/  sit_net_id ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sit_exit_net(struct net *net)
{
	struct sit_net *sitn;

	sitn = net_generic(net, sit_net_id);
	rtnl_lock();
	sit_destroy_tunnels(sitn);
	unregister_netdevice(sitn->fb_tunnel_dev);
	rtnl_unlock();
	kfree(sitn);
}