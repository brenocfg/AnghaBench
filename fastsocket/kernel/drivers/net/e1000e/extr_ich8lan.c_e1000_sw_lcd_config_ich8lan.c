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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {TYPE_4__ ops; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int type; } ;
struct e1000_hw {struct e1000_phy_info phy; TYPE_3__ mac; TYPE_2__* adapter; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DEV_ID_ICH8_IGP_AMT ; 
 int /*<<< orphan*/  E1000_DEV_ID_ICH8_IGP_C ; 
 int E1000_EXTCNF_CTRL_EXT_CNF_POINTER_MASK ; 
 int E1000_EXTCNF_CTRL_EXT_CNF_POINTER_SHIFT ; 
 int E1000_EXTCNF_CTRL_LCD_WRITE_ENABLE ; 
 int E1000_EXTCNF_CTRL_OEM_WRITE_ENABLE ; 
 int E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_MASK ; 
 int E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_SHIFT ; 
 int E1000_FEXTNVM_SW_CONFIG ; 
 int E1000_FEXTNVM_SW_CONFIG_ICH8M ; 
 int /*<<< orphan*/  EXTCNF_CTRL ; 
 int /*<<< orphan*/  EXTCNF_SIZE ; 
 int /*<<< orphan*/  FEXTNVM ; 
 int /*<<< orphan*/  HV_LED_CONFIG ; 
 scalar_t__ IGP01E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  LEDCTL ; 
 scalar_t__ PHY_REG_MASK ; 
#define  e1000_ich8lan 131 
#define  e1000_pch2lan 130 
#define  e1000_pch_lpt 129 
#define  e1000_pchlan 128 
 int /*<<< orphan*/  e1000_phy_igp_3 ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ e1000_write_phy_reg_hv_locked (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ e1000_write_smbus_addr (struct e1000_hw*) ; 
 scalar_t__ e1e_wphy_locked (struct e1000_hw*,int,scalar_t__) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_sw_lcd_config_ich8lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 i, data, cnf_size, cnf_base_addr, sw_cfg_mask;
	s32 ret_val = 0;
	u16 word_addr, reg_data, reg_addr, phy_page = 0;

	/* Initialize the PHY from the NVM on ICH platforms.  This
	 * is needed due to an issue where the NVM configuration is
	 * not properly autoloaded after power transitions.
	 * Therefore, after each PHY reset, we will load the
	 * configuration data out of the NVM manually.
	 */
	switch (hw->mac.type) {
	case e1000_ich8lan:
		if (phy->type != e1000_phy_igp_3)
			return ret_val;

		if ((hw->adapter->pdev->device == E1000_DEV_ID_ICH8_IGP_AMT) ||
		    (hw->adapter->pdev->device == E1000_DEV_ID_ICH8_IGP_C)) {
			sw_cfg_mask = E1000_FEXTNVM_SW_CONFIG;
			break;
		}
		/* Fall-thru */
	case e1000_pchlan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
		sw_cfg_mask = E1000_FEXTNVM_SW_CONFIG_ICH8M;
		break;
	default:
		return ret_val;
	}

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	data = er32(FEXTNVM);
	if (!(data & sw_cfg_mask))
		goto release;

	/* Make sure HW does not configure LCD from PHY
	 * extended configuration before SW configuration
	 */
	data = er32(EXTCNF_CTRL);
	if ((hw->mac.type < e1000_pch2lan) &&
	    (data & E1000_EXTCNF_CTRL_LCD_WRITE_ENABLE))
		goto release;

	cnf_size = er32(EXTCNF_SIZE);
	cnf_size &= E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_MASK;
	cnf_size >>= E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_SHIFT;
	if (!cnf_size)
		goto release;

	cnf_base_addr = data & E1000_EXTCNF_CTRL_EXT_CNF_POINTER_MASK;
	cnf_base_addr >>= E1000_EXTCNF_CTRL_EXT_CNF_POINTER_SHIFT;

	if (((hw->mac.type == e1000_pchlan) &&
	     !(data & E1000_EXTCNF_CTRL_OEM_WRITE_ENABLE)) ||
	    (hw->mac.type > e1000_pchlan)) {
		/* HW configures the SMBus address and LEDs when the
		 * OEM and LCD Write Enable bits are set in the NVM.
		 * When both NVM bits are cleared, SW will configure
		 * them instead.
		 */
		ret_val = e1000_write_smbus_addr(hw);
		if (ret_val)
			goto release;

		data = er32(LEDCTL);
		ret_val = e1000_write_phy_reg_hv_locked(hw, HV_LED_CONFIG,
							(u16)data);
		if (ret_val)
			goto release;
	}

	/* Configure LCD from extended configuration region. */

	/* cnf_base_addr is in DWORD */
	word_addr = (u16)(cnf_base_addr << 1);

	for (i = 0; i < cnf_size; i++) {
		ret_val = e1000_read_nvm(hw, (word_addr + i * 2), 1, &reg_data);
		if (ret_val)
			goto release;

		ret_val = e1000_read_nvm(hw, (word_addr + i * 2 + 1),
					 1, &reg_addr);
		if (ret_val)
			goto release;

		/* Save off the PHY page for future writes. */
		if (reg_addr == IGP01E1000_PHY_PAGE_SELECT) {
			phy_page = reg_data;
			continue;
		}

		reg_addr &= PHY_REG_MASK;
		reg_addr |= phy_page;

		ret_val = e1e_wphy_locked(hw, (u32)reg_addr, reg_data);
		if (ret_val)
			goto release;
	}

release:
	hw->phy.ops.release(hw);
	return ret_val;
}