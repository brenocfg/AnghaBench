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
struct smsc9420_pdata {int /*<<< orphan*/  phy_dev; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int maxtxpkt; int maxrxpkt; } ;

/* Variables and functions */
 int ENODEV ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int phy_ethtool_gset (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 

__attribute__((used)) static int smsc9420_ethtool_get_settings(struct net_device *dev,
					 struct ethtool_cmd *cmd)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);

	if (!pd->phy_dev)
		return -ENODEV;

	cmd->maxtxpkt = 1;
	cmd->maxrxpkt = 1;
	return phy_ethtool_gset(pd->phy_dev, cmd);
}