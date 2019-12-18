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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* check_reset_block ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_FORCE_SMBUS ; 
 int E1000_CTRL_EXT_LPCD ; 
 int E1000_CTRL_LANPHYPC_OVERRIDE ; 
 int E1000_CTRL_LANPHYPC_VALUE ; 
 scalar_t__ E1000_ERR_PHY ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int /*<<< orphan*/  FEXTNVM3 ; 
 int /*<<< orphan*/  FWSM ; 
 int /*<<< orphan*/  e1000_gate_hw_phy_config_ich8lan (struct e1000_hw*,int) ; 
#define  e1000_pch2lan 130 
#define  e1000_pch_lpt 129 
#define  e1000_pchlan 128 
 int /*<<< orphan*/  e1000_phy_is_accessible_pchlan (struct e1000_hw*) ; 
 scalar_t__ e1000e_phy_hw_reset_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_init_phy_workarounds_pchlan(struct e1000_hw *hw)
{
	u32 mac_reg, fwsm = er32(FWSM);
	s32 ret_val;

	/* Gate automatic PHY configuration by hardware on managed and
	 * non-managed 82579 and newer adapters.
	 */
	e1000_gate_hw_phy_config_ich8lan(hw, true);

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val) {
		e_dbg("Failed to initialize PHY flow\n");
		goto out;
	}

	/* The MAC-PHY interconnect may be in SMBus mode.  If the PHY is
	 * inaccessible and resetting the PHY is not blocked, toggle the
	 * LANPHYPC Value bit to force the interconnect to PCIe mode.
	 */
	switch (hw->mac.type) {
	case e1000_pch_lpt:
		if (e1000_phy_is_accessible_pchlan(hw))
			break;

		/* Before toggling LANPHYPC, see if PHY is accessible by
		 * forcing MAC to SMBus mode first.
		 */
		mac_reg = er32(CTRL_EXT);
		mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
		ew32(CTRL_EXT, mac_reg);

		/* Wait 50 milliseconds for MAC to finish any retries
		 * that it might be trying to perform from previous
		 * attempts to acknowledge any phy read requests.
		 */
		msleep(50);

		/* fall-through */
	case e1000_pch2lan:
		if (e1000_phy_is_accessible_pchlan(hw))
			break;

		/* fall-through */
	case e1000_pchlan:
		if ((hw->mac.type == e1000_pchlan) &&
		    (fwsm & E1000_ICH_FWSM_FW_VALID))
			break;

		if (hw->phy.ops.check_reset_block(hw)) {
			e_dbg("Required LANPHYPC toggle blocked by ME\n");
			ret_val = -E1000_ERR_PHY;
			break;
		}

		e_dbg("Toggling LANPHYPC\n");

		/* Set Phy Config Counter to 50msec */
		mac_reg = er32(FEXTNVM3);
		mac_reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
		mac_reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
		ew32(FEXTNVM3, mac_reg);

		/* Toggle LANPHYPC Value bit */
		mac_reg = er32(CTRL);
		mac_reg |= E1000_CTRL_LANPHYPC_OVERRIDE;
		mac_reg &= ~E1000_CTRL_LANPHYPC_VALUE;
		ew32(CTRL, mac_reg);
		e1e_flush();
		usleep_range(10, 20);
		mac_reg &= ~E1000_CTRL_LANPHYPC_OVERRIDE;
		ew32(CTRL, mac_reg);
		e1e_flush();
		if (hw->mac.type < e1000_pch_lpt) {
			msleep(50);
		} else {
			u16 count = 20;
			do {
				usleep_range(5000, 10000);
			} while (!(er32(CTRL_EXT) &
				   E1000_CTRL_EXT_LPCD) && count--);
			usleep_range(30000, 60000);
			if (e1000_phy_is_accessible_pchlan(hw))
				break;

			/* Toggling LANPHYPC brings the PHY out of SMBus mode
			 * so ensure that the MAC is also out of SMBus mode
			 */
			mac_reg = er32(CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			ew32(CTRL_EXT, mac_reg);

			if (e1000_phy_is_accessible_pchlan(hw))
				break;

			ret_val = -E1000_ERR_PHY;
		}
		break;
	default:
		break;
	}

	hw->phy.ops.release(hw);
	if (!ret_val) {
		/* Reset the PHY before any access to it.  Doing so, ensures
		 * that the PHY is in a known good state before we read/write
		 * PHY registers.  The generic reset is sufficient here,
		 * because we haven't determined the PHY type yet.
		 */
		ret_val = e1000e_phy_hw_reset_generic(hw);
	}

out:
	/* Ungate automatic PHY configuration on non-managed 82579 */
	if ((hw->mac.type == e1000_pch2lan) &&
	    !(fwsm & E1000_ICH_FWSM_FW_VALID)) {
		usleep_range(10000, 20000);
		e1000_gate_hw_phy_config_ich8lan(hw, false);
	}

	return ret_val;
}