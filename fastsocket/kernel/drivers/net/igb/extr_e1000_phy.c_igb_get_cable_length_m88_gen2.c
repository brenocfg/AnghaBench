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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,scalar_t__,int) ;int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,scalar_t__,int*) ;} ;
struct e1000_phy_info {int id; int min_cable_length; int max_cable_length; int cable_length; TYPE_1__ ops; scalar_t__ addr; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int GS40G_PAGE_SHIFT ; 
#define  I210_I_PHY_ID 131 
#define  I347AT4_E_PHY_ID 130 
 scalar_t__ I347AT4_PAGE_SELECT ; 
 scalar_t__ I347AT4_PCDC ; 
 int I347AT4_PCDC_CABLE_LENGTH_UNIT ; 
 scalar_t__ I347AT4_PCDL ; 
 int /*<<< orphan*/  M88E1000_CABLE_LENGTH_TABLE_SIZE ; 
 int M88E1000_PSSR_CABLE_LENGTH ; 
 int M88E1000_PSSR_CABLE_LENGTH_SHIFT ; 
#define  M88E1112_E_PHY_ID 129 
 scalar_t__ M88E1112_VCT_DSP_DISTANCE ; 
#define  M88E1543_E_PHY_ID 128 
 void** e1000_m88_cable_length_table ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub10 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub11 (struct e1000_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*,scalar_t__,int) ; 

s32 igb_get_cable_length_m88_gen2(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, phy_data2, index, default_page, is_cm;

	switch (hw->phy.id) {
	case I210_I_PHY_ID:
		/* Get cable length from PHY Cable Diagnostics Control Reg */
		ret_val = phy->ops.read_reg(hw, (0x7 << GS40G_PAGE_SHIFT) +
					    (I347AT4_PCDL + phy->addr),
					    &phy_data);
		if (ret_val)
			return ret_val;

		/* Check if the unit of cable length is meters or cm */
		ret_val = phy->ops.read_reg(hw, (0x7 << GS40G_PAGE_SHIFT) +
					    I347AT4_PCDC, &phy_data2);
		if (ret_val)
			return ret_val;

		is_cm = !(phy_data2 & I347AT4_PCDC_CABLE_LENGTH_UNIT);

		/* Populate the phy structure with cable length in meters */
		phy->min_cable_length = phy_data / (is_cm ? 100 : 1);
		phy->max_cable_length = phy_data / (is_cm ? 100 : 1);
		phy->cable_length = phy_data / (is_cm ? 100 : 1);
		break;
	case M88E1543_E_PHY_ID:
	case I347AT4_E_PHY_ID:
		/* Remember the original page select and set it to 7 */
		ret_val = phy->ops.read_reg(hw, I347AT4_PAGE_SELECT,
					    &default_page);
		if (ret_val)
			goto out;

		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT, 0x07);
		if (ret_val)
			goto out;

		/* Get cable length from PHY Cable Diagnostics Control Reg */
		ret_val = phy->ops.read_reg(hw, (I347AT4_PCDL + phy->addr),
					    &phy_data);
		if (ret_val)
			goto out;

		/* Check if the unit of cable length is meters or cm */
		ret_val = phy->ops.read_reg(hw, I347AT4_PCDC, &phy_data2);
		if (ret_val)
			goto out;

		is_cm = !(phy_data2 & I347AT4_PCDC_CABLE_LENGTH_UNIT);

		/* Populate the phy structure with cable length in meters */
		phy->min_cable_length = phy_data / (is_cm ? 100 : 1);
		phy->max_cable_length = phy_data / (is_cm ? 100 : 1);
		phy->cable_length = phy_data / (is_cm ? 100 : 1);

		/* Reset the page selec to its original value */
		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT,
					     default_page);
		if (ret_val)
			goto out;
		break;
	case M88E1112_E_PHY_ID:
		/* Remember the original page select and set it to 5 */
		ret_val = phy->ops.read_reg(hw, I347AT4_PAGE_SELECT,
					    &default_page);
		if (ret_val)
			goto out;

		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT, 0x05);
		if (ret_val)
			goto out;

		ret_val = phy->ops.read_reg(hw, M88E1112_VCT_DSP_DISTANCE,
					    &phy_data);
		if (ret_val)
			goto out;

		index = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
			M88E1000_PSSR_CABLE_LENGTH_SHIFT;
		if (index >= M88E1000_CABLE_LENGTH_TABLE_SIZE - 1) {
			ret_val = -E1000_ERR_PHY;
			goto out;
		}

		phy->min_cable_length = e1000_m88_cable_length_table[index];
		phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

		phy->cable_length = (phy->min_cable_length +
				     phy->max_cable_length) / 2;

		/* Reset the page select to its original value */
		ret_val = phy->ops.write_reg(hw, I347AT4_PAGE_SELECT,
					     default_page);
		if (ret_val)
			goto out;

		break;
	default:
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

out:
	return ret_val;
}