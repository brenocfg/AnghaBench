#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct TYPE_7__ {int (* setup_link ) (struct e1000_hw*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ media_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_2__ phy; TYPE_1__ fc; } ;
struct e1000_adapter {scalar_t__ fc_autoneg; int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_fc_default ; 
 int /*<<< orphan*/  e1000_fc_full ; 
 int /*<<< orphan*/  e1000_fc_none ; 
 int /*<<< orphan*/  e1000_fc_rx_pause ; 
 int /*<<< orphan*/  e1000_fc_tx_pause ; 
 scalar_t__ e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000e_down (struct e1000_adapter*) ; 
 int e1000e_force_mac_fc (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_set_fc_watermarks (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_up (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int stub1 (struct e1000_hw*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int e1000_set_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pause)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int retval = 0;

	adapter->fc_autoneg = pause->autoneg;

	while (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	if (adapter->fc_autoneg == AUTONEG_ENABLE) {
		hw->fc.requested_mode = e1000_fc_default;
		if (netif_running(adapter->netdev)) {
			e1000e_down(adapter);
			e1000e_up(adapter);
		} else {
			e1000e_reset(adapter);
		}
	} else {
		if (pause->rx_pause && pause->tx_pause)
			hw->fc.requested_mode = e1000_fc_full;
		else if (pause->rx_pause && !pause->tx_pause)
			hw->fc.requested_mode = e1000_fc_rx_pause;
		else if (!pause->rx_pause && pause->tx_pause)
			hw->fc.requested_mode = e1000_fc_tx_pause;
		else if (!pause->rx_pause && !pause->tx_pause)
			hw->fc.requested_mode = e1000_fc_none;

		hw->fc.current_mode = hw->fc.requested_mode;

		if (hw->phy.media_type == e1000_media_type_fiber) {
			retval = hw->mac.ops.setup_link(hw);
			/* implicit goto out */
		} else {
			retval = e1000e_force_mac_fc(hw);
			if (retval)
				goto out;
			e1000e_set_fc_watermarks(hw);
		}
	}

out:
	clear_bit(__E1000_RESETTING, &adapter->state);
	return retval;
}