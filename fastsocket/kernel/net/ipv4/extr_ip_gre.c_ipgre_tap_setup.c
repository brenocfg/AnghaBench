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
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  gre_tap_net_id ; 
 int /*<<< orphan*/  gre_tap_netdev_ops ; 
 int /*<<< orphan*/  ip_tunnel_setup (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipgre_tap_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->netdev_ops		= &gre_tap_netdev_ops;
	ip_tunnel_setup(dev, gre_tap_net_id);
}