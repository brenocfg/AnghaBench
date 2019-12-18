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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ixgb_hw {TYPE_1__ fc; } ;
struct ixgb_adapter {int /*<<< orphan*/  netdev; struct ixgb_hw hw; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  ixgb_down (struct ixgb_adapter*,int) ; 
 int /*<<< orphan*/  ixgb_fc_full ; 
 int /*<<< orphan*/  ixgb_fc_none ; 
 int /*<<< orphan*/  ixgb_fc_rx_pause ; 
 int /*<<< orphan*/  ixgb_fc_tx_pause ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_set_speed_duplex (struct net_device*) ; 
 int /*<<< orphan*/  ixgb_up (struct ixgb_adapter*) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgb_set_pauseparam(struct net_device *netdev,
			 struct ethtool_pauseparam *pause)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_hw *hw = &adapter->hw;

	if (pause->autoneg == AUTONEG_ENABLE)
		return -EINVAL;

	if (pause->rx_pause && pause->tx_pause)
		hw->fc.type = ixgb_fc_full;
	else if (pause->rx_pause && !pause->tx_pause)
		hw->fc.type = ixgb_fc_rx_pause;
	else if (!pause->rx_pause && pause->tx_pause)
		hw->fc.type = ixgb_fc_tx_pause;
	else if (!pause->rx_pause && !pause->tx_pause)
		hw->fc.type = ixgb_fc_none;

	if (netif_running(adapter->netdev)) {
		ixgb_down(adapter, true);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	} else
		ixgb_reset(adapter);

	return 0;
}