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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipip_net {int /*<<< orphan*/ ** tunnels_wc; struct net_device* fb_tunnel_dev; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  ipip_lock ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  ipip_tunnel_unlink (struct ipip_net*,int /*<<< orphan*/ ) ; 
 struct ipip_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipip_tunnel_uninit(struct net_device *dev)
{
	struct net *net = dev_net(dev);
	struct ipip_net *ipn = net_generic(net, ipip_net_id);

	if (dev == ipn->fb_tunnel_dev) {
		write_lock_bh(&ipip_lock);
		ipn->tunnels_wc[0] = NULL;
		write_unlock_bh(&ipip_lock);
	} else
		ipip_tunnel_unlink(ipn, netdev_priv(dev));
	dev_put(dev);
}