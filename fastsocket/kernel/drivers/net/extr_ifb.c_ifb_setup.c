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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  destructor; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  TX_Q_LIMIT ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  ifb_netdev_ops ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ifb_setup(struct net_device *dev)
{
	/* Initialize the device structure. */
	dev->destructor = free_netdev;
	dev->netdev_ops = &ifb_netdev_ops;

	/* Fill in device structure with ethernet-generic values. */
	ether_setup(dev);
	dev->tx_queue_len = TX_Q_LIMIT;

	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;
	random_ether_addr(dev->dev_addr);
}