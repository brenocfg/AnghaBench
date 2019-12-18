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
struct sit_net {int /*<<< orphan*/ ** tunnels_wc; struct net_device* fb_tunnel_dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 int /*<<< orphan*/  ipip6_tunnel_del_prl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipip6_tunnel_unlink (struct sit_net*,int /*<<< orphan*/ ) ; 
 struct sit_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sit_net_id ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipip6_tunnel_uninit(struct net_device *dev)
{
	struct net *net = dev_net(dev);
	struct sit_net *sitn = net_generic(net, sit_net_id);

	if (dev == sitn->fb_tunnel_dev) {
		write_lock_bh(&ipip6_lock);
		sitn->tunnels_wc[0] = NULL;
		write_unlock_bh(&ipip6_lock);
		dev_put(dev);
	} else {
		ipip6_tunnel_unlink(sitn, netdev_priv(dev));
		ipip6_tunnel_del_prl(netdev_priv(dev), NULL);
		dev_put(dev);
	}
}