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
struct net_device {int watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  bnep_netdev_ops ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 

void bnep_net_setup(struct net_device *dev)
{

	memset(dev->broadcast, 0xff, ETH_ALEN);
	dev->addr_len = ETH_ALEN;

	ether_setup(dev);
	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->netdev_ops = &bnep_netdev_ops;

	dev->watchdog_timeo  = HZ * 2;
}