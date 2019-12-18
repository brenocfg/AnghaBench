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
struct ethtool_cmd {int supported; scalar_t__ speed; int duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  advertising; } ;
struct atl1e_hw {scalar_t__ nic_type; int /*<<< orphan*/  autoneg_advertised; } ;
struct atl1e_adapter {scalar_t__ link_speed; scalar_t__ link_duplex; struct atl1e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 scalar_t__ FULL_DUPLEX ; 
 int /*<<< orphan*/  PORT_TP ; 
 scalar_t__ SPEED_0 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 scalar_t__ athr_l1e ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl1e_get_settings(struct net_device *netdev,
			      struct ethtool_cmd *ecmd)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	struct atl1e_hw *hw = &adapter->hw;

	ecmd->supported = (SUPPORTED_10baseT_Half  |
			   SUPPORTED_10baseT_Full  |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_Autoneg       |
			   SUPPORTED_TP);
	if (hw->nic_type == athr_l1e)
		ecmd->supported |= SUPPORTED_1000baseT_Full;

	ecmd->advertising = ADVERTISED_TP;

	ecmd->advertising |= ADVERTISED_Autoneg;
	ecmd->advertising |= hw->autoneg_advertised;

	ecmd->port = PORT_TP;
	ecmd->phy_address = 0;
	ecmd->transceiver = XCVR_INTERNAL;

	if (adapter->link_speed != SPEED_0) {
		ecmd->speed = adapter->link_speed;
		if (adapter->link_duplex == FULL_DUPLEX)
			ecmd->duplex = DUPLEX_FULL;
		else
			ecmd->duplex = DUPLEX_HALF;
	} else {
		ecmd->speed = -1;
		ecmd->duplex = -1;
	}

	ecmd->autoneg = AUTONEG_ENABLE;
	return 0;
}