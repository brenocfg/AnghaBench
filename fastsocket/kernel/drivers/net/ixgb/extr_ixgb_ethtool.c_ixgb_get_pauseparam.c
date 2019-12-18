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
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgb_hw {TYPE_1__ fc; } ;
struct ixgb_adapter {struct ixgb_hw hw; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 scalar_t__ ixgb_fc_full ; 
 scalar_t__ ixgb_fc_rx_pause ; 
 scalar_t__ ixgb_fc_tx_pause ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ixgb_get_pauseparam(struct net_device *netdev,
			 struct ethtool_pauseparam *pause)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_hw *hw = &adapter->hw;

	pause->autoneg = AUTONEG_DISABLE;

	if (hw->fc.type == ixgb_fc_rx_pause)
		pause->rx_pause = 1;
	else if (hw->fc.type == ixgb_fc_tx_pause)
		pause->tx_pause = 1;
	else if (hw->fc.type == ixgb_fc_full) {
		pause->rx_pause = 1;
		pause->tx_pause = 1;
	}
}