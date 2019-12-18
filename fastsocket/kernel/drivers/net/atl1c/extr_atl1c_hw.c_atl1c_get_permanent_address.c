#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct atl1c_hw {scalar_t__ nic_type; int /*<<< orphan*/  perm_mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANACTRL_HB_EN ; 
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ AT_TWSI_EEPROM_TIMEOUT ; 
 int /*<<< orphan*/  AT_WRITE_FLUSH (struct atl1c_hw*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MIIDBG_ANACTRL ; 
 int /*<<< orphan*/  MIIDBG_VOLT_CTRL ; 
 scalar_t__ OTP_CTRL_CLK_EN ; 
 int /*<<< orphan*/  REG_OTP_CTRL ; 
 int /*<<< orphan*/  REG_TWSI_CTRL ; 
 scalar_t__ TWSI_CTRL_SW_LDSTART ; 
 int /*<<< orphan*/  VOLT_CTRL_SWLOWEST ; 
 scalar_t__ athr_l1c ; 
 scalar_t__ athr_l2c ; 
 scalar_t__ athr_l2c_b ; 
 scalar_t__ athr_l2c_b2 ; 
 scalar_t__ atl1c_check_eeprom_exist (struct atl1c_hw*) ; 
 scalar_t__ atl1c_read_current_addr (struct atl1c_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl1c_read_phy_dbg (struct atl1c_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl1c_write_phy_dbg (struct atl1c_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int atl1c_get_permanent_address(struct atl1c_hw *hw)
{
	u32 i;
	u32 otp_ctrl_data;
	u32 twsi_ctrl_data;
	u16 phy_data;
	bool raise_vol = false;

	/* MAC-address from BIOS is the 1st priority */
	if (atl1c_read_current_addr(hw, hw->perm_mac_addr))
		return 0;

	/* init */
	AT_READ_REG(hw, REG_OTP_CTRL, &otp_ctrl_data);
	if (atl1c_check_eeprom_exist(hw)) {
		if (hw->nic_type == athr_l1c || hw->nic_type == athr_l2c) {
			/* Enable OTP CLK */
			if (!(otp_ctrl_data & OTP_CTRL_CLK_EN)) {
				otp_ctrl_data |= OTP_CTRL_CLK_EN;
				AT_WRITE_REG(hw, REG_OTP_CTRL, otp_ctrl_data);
				AT_WRITE_FLUSH(hw);
				msleep(1);
			}
		}
		/* raise voltage temporally for l2cb */
		if (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2) {
			atl1c_read_phy_dbg(hw, MIIDBG_ANACTRL, &phy_data);
			phy_data &= ~ANACTRL_HB_EN;
			atl1c_write_phy_dbg(hw, MIIDBG_ANACTRL, phy_data);
			atl1c_read_phy_dbg(hw, MIIDBG_VOLT_CTRL, &phy_data);
			phy_data |= VOLT_CTRL_SWLOWEST;
			atl1c_write_phy_dbg(hw, MIIDBG_VOLT_CTRL, phy_data);
			udelay(20);
			raise_vol = true;
		}

		AT_READ_REG(hw, REG_TWSI_CTRL, &twsi_ctrl_data);
		twsi_ctrl_data |= TWSI_CTRL_SW_LDSTART;
		AT_WRITE_REG(hw, REG_TWSI_CTRL, twsi_ctrl_data);
		for (i = 0; i < AT_TWSI_EEPROM_TIMEOUT; i++) {
			msleep(10);
			AT_READ_REG(hw, REG_TWSI_CTRL, &twsi_ctrl_data);
			if ((twsi_ctrl_data & TWSI_CTRL_SW_LDSTART) == 0)
				break;
		}
		if (i >= AT_TWSI_EEPROM_TIMEOUT)
			return -1;
	}
	/* Disable OTP_CLK */
	if ((hw->nic_type == athr_l1c || hw->nic_type == athr_l2c)) {
		otp_ctrl_data &= ~OTP_CTRL_CLK_EN;
		AT_WRITE_REG(hw, REG_OTP_CTRL, otp_ctrl_data);
		msleep(1);
	}
	if (raise_vol) {
		atl1c_read_phy_dbg(hw, MIIDBG_ANACTRL, &phy_data);
		phy_data |= ANACTRL_HB_EN;
		atl1c_write_phy_dbg(hw, MIIDBG_ANACTRL, phy_data);
		atl1c_read_phy_dbg(hw, MIIDBG_VOLT_CTRL, &phy_data);
		phy_data &= ~VOLT_CTRL_SWLOWEST;
		atl1c_write_phy_dbg(hw, MIIDBG_VOLT_CTRL, phy_data);
		udelay(20);
	}

	if (atl1c_read_current_addr(hw, hw->perm_mac_addr))
		return 0;

	return -1;
}