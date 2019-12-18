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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ (* commit ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {int mdix; TYPE_1__ ops; scalar_t__ disable_polarity_correction; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* check_mng_mode ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct e1000_hw {TYPE_3__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_LINK_MODE_MASK ; 
 int E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS ; 
 int E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE ; 
 int E1000_KMRNCTRLSTA_OPMODE_E_IDLE ; 
 int GG82563_ICR_DIS_PADDING ; 
 int GG82563_KMCR_PASS_FALSE_CARRIER ; 
 int GG82563_MSCR_ASSERT_CRS_ON_TX ; 
 int GG82563_MSCR_TX_CLK_1000MBPS_25 ; 
 int /*<<< orphan*/  GG82563_PHY_INBAND_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_KMRN_MODE_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_MAC_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_PWR_MGMT_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_SPEC_CTRL_2 ; 
 int GG82563_PMCR_ENABLE_ELECTRICAL_IDLE ; 
 int GG82563_PSCR2_REVERSE_AUTO_NEG ; 
 int GG82563_PSCR_CROSSOVER_MODE_AUTO ; 
 int GG82563_PSCR_CROSSOVER_MODE_MASK ; 
 int GG82563_PSCR_CROSSOVER_MODE_MDI ; 
 int GG82563_PSCR_CROSSOVER_MODE_MDIX ; 
 int GG82563_PSCR_POLARITY_REVERSAL_DISABLE ; 
 scalar_t__ e1000_read_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_copper_link_setup_gg82563_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u32 ctrl_ext;
	u16 data;

	ret_val = e1e_rphy(hw, GG82563_PHY_MAC_SPEC_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= GG82563_MSCR_ASSERT_CRS_ON_TX;
	/* Use 25MHz for both link down and 1000Base-T for Tx clock. */
	data |= GG82563_MSCR_TX_CLK_1000MBPS_25;

	ret_val = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTRL, data);
	if (ret_val)
		return ret_val;

	/* Options:
	 *   MDI/MDI-X = 0 (default)
	 *   0 - Auto for all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto for 1000Base-T only (MDI-X for 10/100Base-T modes)
	 */
	ret_val = e1e_rphy(hw, GG82563_PHY_SPEC_CTRL, &data);
	if (ret_val)
		return ret_val;

	data &= ~GG82563_PSCR_CROSSOVER_MODE_MASK;

	switch (phy->mdix) {
	case 1:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDI;
		break;
	case 2:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDIX;
		break;
	case 0:
	default:
		data |= GG82563_PSCR_CROSSOVER_MODE_AUTO;
		break;
	}

	/* Options:
	 *   disable_polarity_correction = 0 (default)
	 *       Automatic Correction for Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	data &= ~GG82563_PSCR_POLARITY_REVERSAL_DISABLE;
	if (phy->disable_polarity_correction)
		data |= GG82563_PSCR_POLARITY_REVERSAL_DISABLE;

	ret_val = e1e_wphy(hw, GG82563_PHY_SPEC_CTRL, data);
	if (ret_val)
		return ret_val;

	/* SW Reset the PHY so all changes take effect */
	ret_val = hw->phy.ops.commit(hw);
	if (ret_val) {
		e_dbg("Error Resetting the PHY\n");
		return ret_val;
	}

	/* Bypass Rx and Tx FIFO's */
	ret_val = e1000_write_kmrn_reg_80003es2lan(hw,
					E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL,
					E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS |
					E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS);
	if (ret_val)
		return ret_val;

	ret_val = e1000_read_kmrn_reg_80003es2lan(hw,
				       E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE,
				       &data);
	if (ret_val)
		return ret_val;
	data |= E1000_KMRNCTRLSTA_OPMODE_E_IDLE;
	ret_val = e1000_write_kmrn_reg_80003es2lan(hw,
					E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE,
					data);
	if (ret_val)
		return ret_val;

	ret_val = e1e_rphy(hw, GG82563_PHY_SPEC_CTRL_2, &data);
	if (ret_val)
		return ret_val;

	data &= ~GG82563_PSCR2_REVERSE_AUTO_NEG;
	ret_val = e1e_wphy(hw, GG82563_PHY_SPEC_CTRL_2, data);
	if (ret_val)
		return ret_val;

	ctrl_ext = er32(CTRL_EXT);
	ctrl_ext &= ~(E1000_CTRL_EXT_LINK_MODE_MASK);
	ew32(CTRL_EXT, ctrl_ext);

	ret_val = e1e_rphy(hw, GG82563_PHY_PWR_MGMT_CTRL, &data);
	if (ret_val)
		return ret_val;

	/* Do not init these registers when the HW is in IAMT mode, since the
	 * firmware will have already initialized them.  We only initialize
	 * them if the HW is not in IAMT mode.
	 */
	if (!hw->mac.ops.check_mng_mode(hw)) {
		/* Enable Electrical Idle on the PHY */
		data |= GG82563_PMCR_ENABLE_ELECTRICAL_IDLE;
		ret_val = e1e_wphy(hw, GG82563_PHY_PWR_MGMT_CTRL, data);
		if (ret_val)
			return ret_val;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &data);
		if (ret_val)
			return ret_val;

		data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;
		ret_val = e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, data);
		if (ret_val)
			return ret_val;
	}

	/* Workaround: Disable padding in Kumeran interface in the MAC
	 * and in the PHY to avoid CRC errors.
	 */
	ret_val = e1e_rphy(hw, GG82563_PHY_INBAND_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= GG82563_ICR_DIS_PADDING;
	ret_val = e1e_wphy(hw, GG82563_PHY_INBAND_CTRL, data);
	if (ret_val)
		return ret_val;

	return 0;
}