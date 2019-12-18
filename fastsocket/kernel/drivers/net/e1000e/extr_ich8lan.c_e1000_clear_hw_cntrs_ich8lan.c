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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* read_reg_page ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* set_page ) (struct e1000_hw*,int) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ALGNERRC ; 
 int /*<<< orphan*/  CEXTERR ; 
 int /*<<< orphan*/  HV_COLC_LOWER ; 
 int /*<<< orphan*/  HV_COLC_UPPER ; 
 int /*<<< orphan*/  HV_DC_LOWER ; 
 int /*<<< orphan*/  HV_DC_UPPER ; 
 int /*<<< orphan*/  HV_ECOL_LOWER ; 
 int /*<<< orphan*/  HV_ECOL_UPPER ; 
 int /*<<< orphan*/  HV_LATECOL_LOWER ; 
 int /*<<< orphan*/  HV_LATECOL_UPPER ; 
 int /*<<< orphan*/  HV_MCC_LOWER ; 
 int /*<<< orphan*/  HV_MCC_UPPER ; 
 int /*<<< orphan*/  HV_SCC_LOWER ; 
 int /*<<< orphan*/  HV_SCC_UPPER ; 
 int HV_STATS_PAGE ; 
 int /*<<< orphan*/  HV_TNCRS_LOWER ; 
 int /*<<< orphan*/  HV_TNCRS_UPPER ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  ICRXOC ; 
 int IGP_PAGE_SHIFT ; 
 int /*<<< orphan*/  MGTPDC ; 
 int /*<<< orphan*/  MGTPRC ; 
 int /*<<< orphan*/  MGTPTC ; 
 int /*<<< orphan*/  RXERRC ; 
 int /*<<< orphan*/  TNCRS ; 
 int /*<<< orphan*/  TSCTC ; 
 int /*<<< orphan*/  TSCTFC ; 
 scalar_t__ e1000_phy_82577 ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_phy_82579 ; 
 scalar_t__ e1000_phy_i217 ; 
 int /*<<< orphan*/  e1000e_clear_hw_cntrs_base (struct e1000_hw*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub10 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub13 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub14 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub15 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub17 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_clear_hw_cntrs_ich8lan(struct e1000_hw *hw)
{
	u16 phy_data;
	s32 ret_val;

	e1000e_clear_hw_cntrs_base(hw);

	er32(ALGNERRC);
	er32(RXERRC);
	er32(TNCRS);
	er32(CEXTERR);
	er32(TSCTC);
	er32(TSCTFC);

	er32(MGTPRC);
	er32(MGTPDC);
	er32(MGTPTC);

	er32(IAC);
	er32(ICRXOC);

	/* Clear PHY statistics registers */
	if ((hw->phy.type == e1000_phy_82578) ||
	    (hw->phy.type == e1000_phy_82579) ||
	    (hw->phy.type == e1000_phy_i217) ||
	    (hw->phy.type == e1000_phy_82577)) {
		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return;
		ret_val = hw->phy.ops.set_page(hw,
					       HV_STATS_PAGE << IGP_PAGE_SHIFT);
		if (ret_val)
			goto release;
		hw->phy.ops.read_reg_page(hw, HV_SCC_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_SCC_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_ECOL_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_ECOL_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_MCC_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_MCC_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_LATECOL_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_LATECOL_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_COLC_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_COLC_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_DC_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_DC_LOWER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_TNCRS_UPPER, &phy_data);
		hw->phy.ops.read_reg_page(hw, HV_TNCRS_LOWER, &phy_data);
release:
		hw->phy.ops.release(hw);
	}
}