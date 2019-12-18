#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  link_duplex; scalar_t__ link_speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg_advertised; } ;
struct pch_gbe_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mii; struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_down (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_hal_phy_sw_reset (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_hal_write_phy_reg (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_reset (struct pch_gbe_adapter*) ; 
 int pch_gbe_up (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pch_gbe_set_settings(struct net_device *netdev,
				 struct ethtool_cmd *ecmd)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_hw *hw = &adapter->hw;
	u32 speed = ethtool_cmd_speed(ecmd);
	int ret;

	pch_gbe_hal_write_phy_reg(hw, MII_BMCR, BMCR_RESET);

	/* when set_settings() is called with a ethtool_cmd previously
	 * filled by get_settings() on a down link, speed is -1: */
	if (speed == UINT_MAX) {
		speed = SPEED_1000;
		ecmd->duplex = DUPLEX_FULL;
	}
	ret = mii_ethtool_sset(&adapter->mii, ecmd);
	if (ret) {
		pr_err("Error: mii_ethtool_sset\n");
		return ret;
	}
	hw->mac.link_speed = speed;
	hw->mac.link_duplex = ecmd->duplex;
	hw->phy.autoneg_advertised = ecmd->advertising;
	hw->mac.autoneg = ecmd->autoneg;
	pch_gbe_hal_phy_sw_reset(hw);

	/* reset the link */
	if (netif_running(adapter->netdev)) {
		pch_gbe_down(adapter);
		ret = pch_gbe_up(adapter);
	} else {
		pch_gbe_reset(adapter);
	}
	return ret;
}