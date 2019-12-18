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
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {scalar_t__ type; int revision; int addr; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_PORT_GEN_CFG ; 
 int /*<<< orphan*/  HV_KMRN_FIFO_CTRLSTA ; 
 int /*<<< orphan*/  I82577_MSE_THRESHOLD ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHY_REG (int,int) ; 
 scalar_t__ e1000_k1_gig_workaround_hv (struct e1000_hw*,int) ; 
 scalar_t__ e1000_pchlan ; 
 scalar_t__ e1000_phy_82577 ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_set_mdio_slow_mode_hv (struct e1000_hw*) ; 
 scalar_t__ e1000_write_emi_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e1000e_phy_sw_reset (struct e1000_hw*) ; 
 scalar_t__ e1000e_write_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1e_rphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1e_wphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_hv_phy_workarounds_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 phy_data;

	if (hw->mac.type != e1000_pchlan)
		return 0;

	/* Set MDIO slow mode before any other MDIO access */
	if (hw->phy.type == e1000_phy_82577) {
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		if (ret_val)
			return ret_val;
	}

	if (((hw->phy.type == e1000_phy_82577) &&
	     ((hw->phy.revision == 1) || (hw->phy.revision == 2))) ||
	    ((hw->phy.type == e1000_phy_82578) && (hw->phy.revision == 1))) {
		/* Disable generation of early preamble */
		ret_val = e1e_wphy(hw, PHY_REG(769, 25), 0x4431);
		if (ret_val)
			return ret_val;

		/* Preamble tuning for SSC */
		ret_val = e1e_wphy(hw, HV_KMRN_FIFO_CTRLSTA, 0xA204);
		if (ret_val)
			return ret_val;
	}

	if (hw->phy.type == e1000_phy_82578) {
		/* Return registers to default by doing a soft reset then
		 * writing 0x3140 to the control register.
		 */
		if (hw->phy.revision < 2) {
			e1000e_phy_sw_reset(hw);
			ret_val = e1e_wphy(hw, MII_BMCR, 0x3140);
		}
	}

	/* Select page 0 */
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	hw->phy.addr = 1;
	ret_val = e1000e_write_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT, 0);
	hw->phy.ops.release(hw);
	if (ret_val)
		return ret_val;

	/* Configure the K1 Si workaround during phy reset assuming there is
	 * link so that it disables K1 if link is in 1Gbps.
	 */
	ret_val = e1000_k1_gig_workaround_hv(hw, true);
	if (ret_val)
		return ret_val;

	/* Workaround for link disconnects on a busy hub in half duplex */
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;
	ret_val = e1e_rphy_locked(hw, BM_PORT_GEN_CFG, &phy_data);
	if (ret_val)
		goto release;
	ret_val = e1e_wphy_locked(hw, BM_PORT_GEN_CFG, phy_data & 0x00FF);
	if (ret_val)
		goto release;

	/* set MSE higher to enable link to stay up when noise is high */
	ret_val = e1000_write_emi_reg_locked(hw, I82577_MSE_THRESHOLD, 0x0034);
release:
	hw->phy.ops.release(hw);

	return ret_val;
}