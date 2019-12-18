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
struct ip_tunnel {int ip_tnl_net_id; } ;

/* Variables and functions */
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

void ip_tunnel_setup(struct net_device *dev, int net_id)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	tunnel->ip_tnl_net_id = net_id;
}