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
struct lcnphy_txgains {int dummy; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int LCNPHY_TX_PWR_CTRL_OFF ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  RADIO_2064_REG007 ; 
 int /*<<< orphan*/  RADIO_2064_REG0FF ; 
 int /*<<< orphan*/  RADIO_2064_REG112 ; 
 int /*<<< orphan*/  RADIO_2064_REG11F ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_enable_tx_gain_override (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_gain_override (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_tssi_setup (struct brcms_phy*) ; 
 int wlc_lcnphy_tx_gain_override_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_do_dummy_tx (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wlc_lcnphy_idle_tssi_est(struct brcms_phy_pub *ppi)
{
	bool suspend, tx_gain_override_old;
	struct lcnphy_txgains old_gains;
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	u16 idleTssi, idleTssi0_2C, idleTssi0_OB, idleTssi0_regvalue_OB,
	    idleTssi0_regvalue_2C;
	u16 SAVE_txpwrctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	u16 SAVE_lpfgain = read_radio_reg(pi, RADIO_2064_REG112);
	u16 SAVE_jtag_bb_afe_switch =
		read_radio_reg(pi, RADIO_2064_REG007) & 1;
	u16 SAVE_jtag_auxpga = read_radio_reg(pi, RADIO_2064_REG0FF) & 0x10;
	u16 SAVE_iqadc_aux_en = read_radio_reg(pi, RADIO_2064_REG11F) & 4;
	idleTssi = read_phy_reg(pi, 0x4ab);
	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend)
		wlapi_suspend_mac_and_wait(pi->sh->physhim);
	wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF);

	tx_gain_override_old = wlc_lcnphy_tx_gain_override_enabled(pi);
	wlc_lcnphy_get_tx_gain(pi, &old_gains);

	wlc_lcnphy_enable_tx_gain_override(pi);
	wlc_lcnphy_set_tx_pwr_by_index(pi, 127);
	write_radio_reg(pi, RADIO_2064_REG112, 0x6);
	mod_radio_reg(pi, RADIO_2064_REG007, 0x1, 1);
	mod_radio_reg(pi, RADIO_2064_REG0FF, 0x10, 1 << 4);
	mod_radio_reg(pi, RADIO_2064_REG11F, 0x4, 1 << 2);
	wlc_lcnphy_tssi_setup(pi);
	wlc_phy_do_dummy_tx(pi, true, OFF);
	idleTssi = ((read_phy_reg(pi, 0x4ab) & (0x1ff << 0))
		    >> 0);

	idleTssi0_2C = ((read_phy_reg(pi, 0x63e) & (0x1ff << 0))
			>> 0);

	if (idleTssi0_2C >= 256)
		idleTssi0_OB = idleTssi0_2C - 256;
	else
		idleTssi0_OB = idleTssi0_2C + 256;

	idleTssi0_regvalue_OB = idleTssi0_OB;
	if (idleTssi0_regvalue_OB >= 256)
		idleTssi0_regvalue_2C = idleTssi0_regvalue_OB - 256;
	else
		idleTssi0_regvalue_2C = idleTssi0_regvalue_OB + 256;
	mod_phy_reg(pi, 0x4a6, (0x1ff << 0), (idleTssi0_regvalue_2C) << 0);

	mod_phy_reg(pi, 0x44c, (0x1 << 12), (0) << 12);

	wlc_lcnphy_set_tx_gain_override(pi, tx_gain_override_old);
	wlc_lcnphy_set_tx_gain(pi, &old_gains);
	wlc_lcnphy_set_tx_pwr_ctrl(pi, SAVE_txpwrctrl);

	write_radio_reg(pi, RADIO_2064_REG112, SAVE_lpfgain);
	mod_radio_reg(pi, RADIO_2064_REG007, 0x1, SAVE_jtag_bb_afe_switch);
	mod_radio_reg(pi, RADIO_2064_REG0FF, 0x10, SAVE_jtag_auxpga);
	mod_radio_reg(pi, RADIO_2064_REG11F, 0x4, SAVE_iqadc_aux_en);
	mod_radio_reg(pi, RADIO_2064_REG112, 0x80, 1 << 7);
	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);
}