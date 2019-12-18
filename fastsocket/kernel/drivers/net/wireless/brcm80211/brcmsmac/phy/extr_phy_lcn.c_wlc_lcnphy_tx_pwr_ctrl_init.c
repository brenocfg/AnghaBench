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
typedef  int u8 ;
struct phytbl_info {int tbl_width; int* tbl_ptr; int tbl_len; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct lcnphy_txgains {int gm_gain; int pga_gain; int pad_gain; scalar_t__ dac_gain; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int* txpa_2g; TYPE_1__* sh; int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/  hwpwrctrl_capable; int /*<<< orphan*/  d11core; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 int /*<<< orphan*/  LCNPHY_TX_PWR_CTRL_HW ; 
 int /*<<< orphan*/  LCN_TARGET_PWR ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  TEMPSENSE ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_clear_tx_power_offsets (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_idle_tssi_est (struct brcms_phy_pub*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_bbmult (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_target_tx_pwr (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int wlc_lcnphy_tssi2dbm (int,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_vbat_temp_sense_setup (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_tx_pwr_ctrl_init(struct brcms_phy_pub *ppi)
{
	struct lcnphy_txgains tx_gains;
	u8 bbmult;
	struct phytbl_info tab;
	s32 a1, b0, b1;
	s32 tssi, pwr, maxtargetpwr, mintargetpwr;
	bool suspend;
	struct brcms_phy *pi = (struct brcms_phy *) ppi;

	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend)
		wlapi_suspend_mac_and_wait(pi->sh->physhim);

	if (!pi->hwpwrctrl_capable) {
		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			tx_gains.gm_gain = 4;
			tx_gains.pga_gain = 12;
			tx_gains.pad_gain = 12;
			tx_gains.dac_gain = 0;

			bbmult = 150;
		} else {
			tx_gains.gm_gain = 7;
			tx_gains.pga_gain = 15;
			tx_gains.pad_gain = 14;
			tx_gains.dac_gain = 0;

			bbmult = 150;
		}
		wlc_lcnphy_set_tx_gain(pi, &tx_gains);
		wlc_lcnphy_set_bbmult(pi, bbmult);
		wlc_lcnphy_vbat_temp_sense_setup(pi, TEMPSENSE);
	} else {

		wlc_lcnphy_idle_tssi_est(ppi);

		wlc_lcnphy_clear_tx_power_offsets(pi);

		b0 = pi->txpa_2g[0];
		b1 = pi->txpa_2g[1];
		a1 = pi->txpa_2g[2];
		maxtargetpwr = wlc_lcnphy_tssi2dbm(10, a1, b0, b1);
		mintargetpwr = wlc_lcnphy_tssi2dbm(125, a1, b0, b1);

		tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
		tab.tbl_width = 32;
		tab.tbl_ptr = &pwr;
		tab.tbl_len = 1;
		tab.tbl_offset = 0;
		for (tssi = 0; tssi < 128; tssi++) {
			pwr = wlc_lcnphy_tssi2dbm(tssi, a1, b0, b1);

			pwr = (pwr < mintargetpwr) ? mintargetpwr : pwr;
			wlc_lcnphy_write_table(pi, &tab);
			tab.tbl_offset++;
		}

		mod_phy_reg(pi, 0x410, (0x1 << 7), (0) << 7);

		write_phy_reg(pi, 0x4a8, 10);

		wlc_lcnphy_set_target_tx_pwr(pi, LCN_TARGET_PWR);

		wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_HW);
	}
	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);
}