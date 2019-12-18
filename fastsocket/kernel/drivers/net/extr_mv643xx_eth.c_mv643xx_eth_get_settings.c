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
struct mv643xx_eth_private {int /*<<< orphan*/ * phy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int mv643xx_eth_get_settings_phy (struct mv643xx_eth_private*,struct ethtool_cmd*) ; 
 int mv643xx_eth_get_settings_phyless (struct mv643xx_eth_private*,struct ethtool_cmd*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mv643xx_eth_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	if (mp->phy != NULL)
		return mv643xx_eth_get_settings_phy(mp, cmd);
	else
		return mv643xx_eth_get_settings_phyless(mp, cmd);
}