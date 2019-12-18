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
struct net_device_stats {int /*<<< orphan*/  tx_packets; } ;
struct orinoco_private {struct net_device_stats stats; } ;
struct net_device {int dummy; } ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_FID ; 
 int /*<<< orphan*/  TXCOMPLFID ; 
 int /*<<< orphan*/  hermes_write_regn (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void __orinoco_ev_tx(struct net_device *dev, struct hermes *hw)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct net_device_stats *stats = &priv->stats;

	stats->tx_packets++;

	netif_wake_queue(dev);

	hermes_write_regn(hw, TXCOMPLFID, DUMMY_FID);
}