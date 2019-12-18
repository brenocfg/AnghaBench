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
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {scalar_t__ (* read ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_CONTROL_EOL_NL ; 
 int IXGBE_CONTROL_MASK_NL ; 
#define  IXGBE_CONTROL_NL 130 
 int IXGBE_CONTROL_SHIFT_NL ; 
 int IXGBE_CONTROL_SOL_NL ; 
 int IXGBE_DATA_MASK_NL ; 
#define  IXGBE_DATA_NL 129 
#define  IXGBE_DELAY_NL 128 
 scalar_t__ IXGBE_ERR_PHY ; 
 int MDIO_CTRL1 ; 
 int MDIO_CTRL1_RESET ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,...) ; 
 scalar_t__ ixgbe_get_sfp_init_sequence_offsets (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub7 (struct ixgbe_hw*,int,int*) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 ixgbe_reset_phy_nl(struct ixgbe_hw *hw)
{
	u16 phy_offset, control, eword, edata, block_crc;
	bool end_data = false;
	u16 list_offset, data_offset;
	u16 phy_data = 0;
	s32 ret_val = 0;
	u32 i;

	hw->phy.ops.read_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS, &phy_data);

	/* reset the PHY and poll for completion */
	hw->phy.ops.write_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS,
	                      (phy_data | MDIO_CTRL1_RESET));

	for (i = 0; i < 100; i++) {
		hw->phy.ops.read_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS,
		                     &phy_data);
		if ((phy_data & MDIO_CTRL1_RESET) == 0)
			break;
		usleep_range(10000, 20000);
	}

	if ((phy_data & MDIO_CTRL1_RESET) != 0) {
		hw_dbg(hw, "PHY reset did not complete.\n");
		ret_val = IXGBE_ERR_PHY;
		goto out;
	}

	/* Get init offsets */
	ret_val = ixgbe_get_sfp_init_sequence_offsets(hw, &list_offset,
	                                              &data_offset);
	if (ret_val != 0)
		goto out;

	ret_val = hw->eeprom.ops.read(hw, data_offset, &block_crc);
	data_offset++;
	while (!end_data) {
		/*
		 * Read control word from PHY init contents offset
		 */
		ret_val = hw->eeprom.ops.read(hw, data_offset, &eword);
		control = (eword & IXGBE_CONTROL_MASK_NL) >>
		           IXGBE_CONTROL_SHIFT_NL;
		edata = eword & IXGBE_DATA_MASK_NL;
		switch (control) {
		case IXGBE_DELAY_NL:
			data_offset++;
			hw_dbg(hw, "DELAY: %d MS\n", edata);
			usleep_range(edata * 1000, edata * 2000);
			break;
		case IXGBE_DATA_NL:
			hw_dbg(hw, "DATA:\n");
			data_offset++;
			hw->eeprom.ops.read(hw, data_offset++,
			                    &phy_offset);
			for (i = 0; i < edata; i++) {
				hw->eeprom.ops.read(hw, data_offset, &eword);
				hw->phy.ops.write_reg(hw, phy_offset,
				                      MDIO_MMD_PMAPMD, eword);
				hw_dbg(hw, "Wrote %4.4x to %4.4x\n", eword,
				       phy_offset);
				data_offset++;
				phy_offset++;
			}
			break;
		case IXGBE_CONTROL_NL:
			data_offset++;
			hw_dbg(hw, "CONTROL:\n");
			if (edata == IXGBE_CONTROL_EOL_NL) {
				hw_dbg(hw, "EOL\n");
				end_data = true;
			} else if (edata == IXGBE_CONTROL_SOL_NL) {
				hw_dbg(hw, "SOL\n");
			} else {
				hw_dbg(hw, "Bad control value\n");
				ret_val = IXGBE_ERR_PHY;
				goto out;
			}
			break;
		default:
			hw_dbg(hw, "Bad control type\n");
			ret_val = IXGBE_ERR_PHY;
			goto out;
		}
	}

out:
	return ret_val;
}