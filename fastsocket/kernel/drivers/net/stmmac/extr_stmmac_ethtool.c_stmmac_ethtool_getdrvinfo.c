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
struct stmmac_priv {int /*<<< orphan*/  is_gmac; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {char* fw_version; int /*<<< orphan*/  n_stats; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MODULE_VERSION ; 
 int /*<<< orphan*/  GMAC_ETHTOOL_NAME ; 
 int /*<<< orphan*/  MAC100_ETHTOOL_NAME ; 
 int /*<<< orphan*/  STMMAC_STATS_LEN ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void stmmac_ethtool_getdrvinfo(struct net_device *dev,
			       struct ethtool_drvinfo *info)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (!priv->is_gmac)
		strcpy(info->driver, MAC100_ETHTOOL_NAME);
	else
		strcpy(info->driver, GMAC_ETHTOOL_NAME);

	strcpy(info->version, DRV_MODULE_VERSION);
	info->fw_version[0] = '\0';
	info->n_stats = STMMAC_STATS_LEN;
	return;
}