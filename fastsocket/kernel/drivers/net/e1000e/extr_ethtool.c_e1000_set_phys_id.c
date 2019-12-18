#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* led_off ) (struct e1000_hw*) ;int /*<<< orphan*/  (* led_on ) (struct e1000_hw*) ;int /*<<< orphan*/  (* cleanup_led ) (struct e1000_hw*) ;int /*<<< orphan*/  (* blink_led ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  IFE_PHY_SPECIAL_CONTROL_LED ; 
 int /*<<< orphan*/  e1000_phy_ife ; 
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*) ; 

__attribute__((used)) static int e1000_set_phys_id(struct net_device *netdev,
			     enum ethtool_phys_id_state state)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		if (!hw->mac.ops.blink_led)
			return 2;	/* cycle on/off twice per second */

		hw->mac.ops.blink_led(hw);
		break;

	case ETHTOOL_ID_INACTIVE:
		if (hw->phy.type == e1000_phy_ife)
			e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED, 0);
		hw->mac.ops.led_off(hw);
		hw->mac.ops.cleanup_led(hw);
		break;

	case ETHTOOL_ID_ON:
		hw->mac.ops.led_on(hw);
		break;

	case ETHTOOL_ID_OFF:
		hw->mac.ops.led_off(hw);
		break;
	}
	return 0;
}