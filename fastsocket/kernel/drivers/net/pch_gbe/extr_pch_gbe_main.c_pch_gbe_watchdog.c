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
struct TYPE_2__ {scalar_t__ link_duplex; int /*<<< orphan*/  link_speed; } ;
struct pch_gbe_hw {TYPE_1__ mac; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  mii; int /*<<< orphan*/  tx_queue_len; struct pch_gbe_hw hw; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  tx_queue_len; } ;
struct ethtool_cmd {scalar_t__ duplex; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 scalar_t__ PCH_GBE_WATCHDOG_PERIOD ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 scalar_t__ mii_link_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_set_mode (struct pch_gbe_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pch_gbe_set_rgmii_ctrl (struct pch_gbe_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pch_gbe_update_stats (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 

__attribute__((used)) static void pch_gbe_watchdog(unsigned long data)
{
	struct pch_gbe_adapter *adapter = (struct pch_gbe_adapter *)data;
	struct net_device *netdev = adapter->netdev;
	struct pch_gbe_hw *hw = &adapter->hw;

	pr_debug("right now = %ld\n", jiffies);

	pch_gbe_update_stats(adapter);
	if ((mii_link_ok(&adapter->mii)) && (!netif_carrier_ok(netdev))) {
		struct ethtool_cmd cmd = { .cmd = ETHTOOL_GSET };
		netdev->tx_queue_len = adapter->tx_queue_len;
		/* mii library handles link maintenance tasks */
		if (mii_ethtool_gset(&adapter->mii, &cmd)) {
			pr_err("ethtool get setting Error\n");
			mod_timer(&adapter->watchdog_timer,
				  round_jiffies(jiffies +
						PCH_GBE_WATCHDOG_PERIOD));
			return;
		}
		hw->mac.link_speed = ethtool_cmd_speed(&cmd);
		hw->mac.link_duplex = cmd.duplex;
		/* Set the RGMII control. */
		pch_gbe_set_rgmii_ctrl(adapter, hw->mac.link_speed,
						hw->mac.link_duplex);
		/* Set the communication mode */
		pch_gbe_set_mode(adapter, hw->mac.link_speed,
				 hw->mac.link_duplex);
		netdev_dbg(netdev,
			   "Link is Up %d Mbps %s-Duplex\n",
			   hw->mac.link_speed,
			   cmd.duplex == DUPLEX_FULL ? "Full" : "Half");
		netif_carrier_on(netdev);
		netif_wake_queue(netdev);
	} else if ((!mii_link_ok(&adapter->mii)) &&
		   (netif_carrier_ok(netdev))) {
		netdev_dbg(netdev, "NIC Link is Down\n");
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		netif_carrier_off(netdev);
		netif_stop_queue(netdev);
	}
	mod_timer(&adapter->watchdog_timer,
		  round_jiffies(jiffies + PCH_GBE_WATCHDOG_PERIOD));
}