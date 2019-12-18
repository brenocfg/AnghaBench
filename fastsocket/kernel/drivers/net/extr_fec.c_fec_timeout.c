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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct fec_enet_private {int /*<<< orphan*/  full_duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  fec_restart (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void
fec_timeout(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);

	dev->stats.tx_errors++;

	fec_restart(dev, fep->full_duplex);
	netif_wake_queue(dev);
}