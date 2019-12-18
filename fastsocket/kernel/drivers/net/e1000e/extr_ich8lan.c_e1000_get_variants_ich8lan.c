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
struct TYPE_4__ {int /*<<< orphan*/ * blink_led; } ;
struct TYPE_6__ {int type; TYPE_1__ ops; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ phy; } ;
struct e1000_adapter {int /*<<< orphan*/  flags2; struct e1000_hw hw; int /*<<< orphan*/  flags; scalar_t__ max_hw_frame_size; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_LSECCK ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  FLAG2_PCIM2PCI_ARBITER_WA ; 
 int /*<<< orphan*/  FLAG_HAS_JUMBO_FRAMES ; 
 int /*<<< orphan*/  FLAG_LSC_GIG_SPEED_DROP ; 
 int /*<<< orphan*/  FWSM ; 
#define  e1000_ich10lan 133 
#define  e1000_ich8lan 132 
#define  e1000_ich9lan 131 
 scalar_t__ e1000_init_mac_params_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_init_nvm_params_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_init_phy_params_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_init_phy_params_pchlan (struct e1000_hw*) ; 
#define  e1000_pch2lan 130 
#define  e1000_pch_lpt 129 
#define  e1000_pchlan 128 
 scalar_t__ e1000_phy_ife ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_get_variants_ich8lan(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	s32 rc;

	rc = e1000_init_mac_params_ich8lan(hw);
	if (rc)
		return rc;

	rc = e1000_init_nvm_params_ich8lan(hw);
	if (rc)
		return rc;

	switch (hw->mac.type) {
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
		rc = e1000_init_phy_params_ich8lan(hw);
		break;
	case e1000_pchlan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
		rc = e1000_init_phy_params_pchlan(hw);
		break;
	default:
		break;
	}
	if (rc)
		return rc;

	/* Disable Jumbo Frame support on parts with Intel 10/100 PHY or
	 * on parts with MACsec enabled in NVM (reflected in CTRL_EXT).
	 */
	if ((adapter->hw.phy.type == e1000_phy_ife) ||
	    ((adapter->hw.mac.type >= e1000_pch2lan) &&
	     (!(er32(CTRL_EXT) & E1000_CTRL_EXT_LSECCK)))) {
		adapter->flags &= ~FLAG_HAS_JUMBO_FRAMES;
		adapter->max_hw_frame_size = ETH_FRAME_LEN + ETH_FCS_LEN;

		hw->mac.ops.blink_led = NULL;
	}

	if ((adapter->hw.mac.type == e1000_ich8lan) &&
	    (adapter->hw.phy.type != e1000_phy_ife))
		adapter->flags |= FLAG_LSC_GIG_SPEED_DROP;

	/* Enable workaround for 82579 w/ ME enabled */
	if ((adapter->hw.mac.type == e1000_pch2lan) &&
	    (er32(FWSM) & E1000_ICH_FWSM_FW_VALID))
		adapter->flags2 |= FLAG2_PCIM2PCI_ARBITER_WA;

	return 0;
}