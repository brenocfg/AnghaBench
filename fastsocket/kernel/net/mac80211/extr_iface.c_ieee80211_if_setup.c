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
struct net_device {int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  ieee80211_dataif_ops ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 

__attribute__((used)) static void ieee80211_if_setup(struct net_device *dev)
{
	ether_setup(dev);
	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->netdev_ops = &ieee80211_dataif_ops;
	dev->destructor = free_netdev;
}