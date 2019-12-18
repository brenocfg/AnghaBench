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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct phytbl_info {int tbl_width; int tbl_len; int* tbl_ptr; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct lcnphy_txgains {int gm_gain; int pga_gain; int pad_gain; int dac_gain; } ;
struct brcms_phy_lcnphy {scalar_t__ lcnphy_current_index; scalar_t__ lcnphy_tx_power_idx_override; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_1__ u; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_GAIN_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_IQ_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_LO_OFFSET ; 
 int /*<<< orphan*/  LCNPHY_TX_PWR_CTRL_OFF ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_PWR_OFFSET ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_enable_tx_gain_override (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_bbmult (struct brcms_phy*,scalar_t__) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_pa_gain (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_iqcc (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_locc (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 

void wlc_lcnphy_set_tx_pwr_by_index(struct brcms_phy *pi, int index)
{
	struct phytbl_info tab;
	u16 a, b;
	u8 bb_mult;
	u32 bbmultiqcomp, txgain, locoeffs, rfpower;
	struct lcnphy_txgains gains;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	pi_lcn->lcnphy_tx_power_idx_override = (s8) index;
	pi_lcn->lcnphy_current_index = (u8) index;

	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_len = 1;

	wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF);

	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_IQ_OFFSET + index;
	tab.tbl_ptr = &bbmultiqcomp;
	wlc_lcnphy_read_table(pi, &tab);

	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_GAIN_OFFSET + index;
	tab.tbl_width = 32;
	tab.tbl_ptr = &txgain;
	wlc_lcnphy_read_table(pi, &tab);

	gains.gm_gain = (u16) (txgain & 0xff);
	gains.pga_gain = (u16) (txgain >> 8) & 0xff;
	gains.pad_gain = (u16) (txgain >> 16) & 0xff;
	gains.dac_gain = (u16) (bbmultiqcomp >> 28) & 0x07;
	wlc_lcnphy_set_tx_gain(pi, &gains);
	wlc_lcnphy_set_pa_gain(pi, (u16) (txgain >> 24) & 0x7f);

	bb_mult = (u8) ((bbmultiqcomp >> 20) & 0xff);
	wlc_lcnphy_set_bbmult(pi, bb_mult);

	wlc_lcnphy_enable_tx_gain_override(pi);

	if (!wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi)) {

		a = (u16) ((bbmultiqcomp >> 10) & 0x3ff);
		b = (u16) (bbmultiqcomp & 0x3ff);
		wlc_lcnphy_set_tx_iqcc(pi, a, b);

		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_LO_OFFSET + index;
		tab.tbl_ptr = &locoeffs;
		wlc_lcnphy_read_table(pi, &tab);

		wlc_lcnphy_set_tx_locc(pi, (u16) locoeffs);

		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_PWR_OFFSET + index;
		tab.tbl_ptr = &rfpower;
		wlc_lcnphy_read_table(pi, &tab);
		mod_phy_reg(pi, 0x6a6, (0x1fff << 0), (rfpower * 8) << 0);

	}
}