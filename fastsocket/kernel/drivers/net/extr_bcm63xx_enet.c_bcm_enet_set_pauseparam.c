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
struct ethtool_pauseparam {scalar_t__ rx_pause; scalar_t__ tx_pause; scalar_t__ autoneg; } ;
struct bcm_enet_priv {scalar_t__ pause_rx; scalar_t__ pause_tx; scalar_t__ pause_auto; scalar_t__ has_phy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_enet_set_pauseparam(struct net_device *dev,
				   struct ethtool_pauseparam *ecmd)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	if (priv->has_phy) {
		if (ecmd->autoneg && (ecmd->rx_pause != ecmd->tx_pause)) {
			/* asymetric pause mode not supported,
			 * actually possible but integrated PHY has RO
			 * asym_pause bit */
			return -EINVAL;
		}
	} else {
		/* no pause autoneg on direct mii connection */
		if (ecmd->autoneg)
			return -EINVAL;
	}

	priv->pause_auto = ecmd->autoneg;
	priv->pause_rx = ecmd->rx_pause;
	priv->pause_tx = ecmd->tx_pause;

	return 0;
}