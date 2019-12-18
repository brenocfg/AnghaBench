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
struct mv643xx_eth_private {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rx_coal (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  get_tx_coal (struct mv643xx_eth_private*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mv643xx_eth_get_coalesce(struct net_device *dev, struct ethtool_coalesce *ec)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	ec->rx_coalesce_usecs = get_rx_coal(mp);
	ec->tx_coalesce_usecs = get_tx_coal(mp);

	return 0;
}