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
struct net_device {int features; int /*<<< orphan*/ * netdev_ops; } ;
struct ixpdev_priv {int channel; scalar_t__ tx_queue_entries; int /*<<< orphan*/  napi; struct net_device* dev; } ;

/* Variables and functions */
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  ixpdev_netdev_ops ; 
 int /*<<< orphan*/  ixpdev_poll ; 
 struct ixpdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct net_device *ixpdev_alloc(int channel, int sizeof_priv)
{
	struct net_device *dev;
	struct ixpdev_priv *ip;

	dev = alloc_etherdev(sizeof_priv);
	if (dev == NULL)
		return NULL;

	dev->netdev_ops = &ixpdev_netdev_ops;

	dev->features |= NETIF_F_SG | NETIF_F_HW_CSUM;

	ip = netdev_priv(dev);
	ip->dev = dev;
	netif_napi_add(dev, &ip->napi, ixpdev_poll, 64);
	ip->channel = channel;
	ip->tx_queue_entries = 0;

	return dev;
}