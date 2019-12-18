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
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int advertising; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_TP ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 int mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_gbe_get_settings(struct net_device *netdev,
				 struct ethtool_cmd *ecmd)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	int ret;

	ret = mii_ethtool_gset(&adapter->mii, ecmd);
	ecmd->supported &= ~(SUPPORTED_TP | SUPPORTED_1000baseT_Half);
	ecmd->advertising &= ~(ADVERTISED_TP | ADVERTISED_1000baseT_Half);

	if (!netif_carrier_ok(adapter->netdev))
		ethtool_cmd_speed_set(ecmd, -1);
	return ret;
}