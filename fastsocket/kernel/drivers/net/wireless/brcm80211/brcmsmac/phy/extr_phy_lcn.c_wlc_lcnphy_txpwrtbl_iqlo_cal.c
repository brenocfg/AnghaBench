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
typedef  int uint ;
typedef  void* u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct phytbl_info {int tbl_width; int* tbl_ptr; int tbl_len; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct lcnphy_txgains {int gm_gain; int pga_gain; int pad_gain; scalar_t__ dac_gain; } ;
struct TYPE_6__ {void* txiqlocal_fq0; void* txiqlocal_fi0; void* txiqlocal_eq0; void* txiqlocal_ei0; scalar_t__ txiqlocal_didq; scalar_t__ txiqlocal_b; scalar_t__ txiqlocal_a; } ;
struct brcms_phy_lcnphy {TYPE_3__ lcnphy_cal_results; scalar_t__ lcnphy_hw_iqcal_en; scalar_t__ lcnphy_recal; } ;
struct TYPE_5__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_4__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_2__ pubpi; int /*<<< orphan*/  radio_chanspec; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCNPHY_CAL_FULL ; 
 int /*<<< orphan*/  LCNPHY_CAL_RECAL ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_IQ_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_LO_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_OFF ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_RATE_OFFSET ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int abs (int /*<<< orphan*/ ) ; 
 void* wlc_lcnphy_get_bbmult (struct brcms_phy*) ; 
 int wlc_lcnphy_get_current_tx_pwr_idx (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_get_pa_gain (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_radio_loft (struct brcms_phy*,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_iqcc (struct brcms_phy*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ wlc_lcnphy_get_tx_locc (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_bbmult (struct brcms_phy*,void*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_pa_gain (struct brcms_phy*,scalar_t__) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_gain (struct brcms_phy*,struct lcnphy_txgains*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,scalar_t__) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_iqlo_cal (struct brcms_phy*,struct lcnphy_txgains*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_iqlo_soft_cal_full (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_txpwrtbl_iqlo_cal(struct brcms_phy *pi)
{

	struct lcnphy_txgains target_gains, old_gains;
	u8 save_bb_mult;
	u16 a, b, didq, save_pa_gain = 0;
	uint idx, SAVE_txpwrindex = 0xFF;
	u32 val;
	u16 SAVE_txpwrctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	struct phytbl_info tab;
	u8 ei0, eq0, fi0, fq0;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	wlc_lcnphy_get_tx_gain(pi, &old_gains);
	save_pa_gain = wlc_lcnphy_get_pa_gain(pi);

	save_bb_mult = wlc_lcnphy_get_bbmult(pi);

	if (SAVE_txpwrctrl == LCNPHY_TX_PWR_CTRL_OFF)
		SAVE_txpwrindex = wlc_lcnphy_get_current_tx_pwr_idx(pi);

	wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF);

	target_gains.gm_gain = 7;
	target_gains.pga_gain = 0;
	target_gains.pad_gain = 21;
	target_gains.dac_gain = 0;
	wlc_lcnphy_set_tx_gain(pi, &target_gains);
	wlc_lcnphy_set_tx_pwr_by_index(pi, 16);

	if (LCNREV_IS(pi->pubpi.phy_rev, 1) || pi_lcn->lcnphy_hw_iqcal_en) {

		wlc_lcnphy_set_tx_pwr_by_index(pi, 30);

		wlc_lcnphy_tx_iqlo_cal(pi, &target_gains,
				       (pi_lcn->
					lcnphy_recal ? LCNPHY_CAL_RECAL :
					LCNPHY_CAL_FULL), false);
	} else {
		wlc_lcnphy_tx_iqlo_soft_cal_full(pi);
	}

	wlc_lcnphy_get_radio_loft(pi, &ei0, &eq0, &fi0, &fq0);
	if ((abs((s8) fi0) == 15) && (abs((s8) fq0) == 15)) {
		if (CHSPEC_IS5G(pi->radio_chanspec)) {
			target_gains.gm_gain = 255;
			target_gains.pga_gain = 255;
			target_gains.pad_gain = 0xf0;
			target_gains.dac_gain = 0;
		} else {
			target_gains.gm_gain = 7;
			target_gains.pga_gain = 45;
			target_gains.pad_gain = 186;
			target_gains.dac_gain = 0;
		}

		if (LCNREV_IS(pi->pubpi.phy_rev, 1)
		    || pi_lcn->lcnphy_hw_iqcal_en) {

			target_gains.pga_gain = 0;
			target_gains.pad_gain = 30;
			wlc_lcnphy_set_tx_pwr_by_index(pi, 16);
			wlc_lcnphy_tx_iqlo_cal(pi, &target_gains,
					       LCNPHY_CAL_FULL, false);
		} else {
			wlc_lcnphy_tx_iqlo_soft_cal_full(pi);
		}
	}

	wlc_lcnphy_get_tx_iqcc(pi, &a, &b);

	didq = wlc_lcnphy_get_tx_locc(pi);

	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_ptr = &val;

	tab.tbl_len = 1;
	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_RATE_OFFSET;

	for (idx = 0; idx < 128; idx++) {
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_IQ_OFFSET + idx;

		wlc_lcnphy_read_table(pi, &tab);
		val = (val & 0xfff00000) |
		      ((u32) (a & 0x3FF) << 10) | (b & 0x3ff);
		wlc_lcnphy_write_table(pi, &tab);

		val = didq;
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_LO_OFFSET + idx;
		wlc_lcnphy_write_table(pi, &tab);
	}

	pi_lcn->lcnphy_cal_results.txiqlocal_a = a;
	pi_lcn->lcnphy_cal_results.txiqlocal_b = b;
	pi_lcn->lcnphy_cal_results.txiqlocal_didq = didq;
	pi_lcn->lcnphy_cal_results.txiqlocal_ei0 = ei0;
	pi_lcn->lcnphy_cal_results.txiqlocal_eq0 = eq0;
	pi_lcn->lcnphy_cal_results.txiqlocal_fi0 = fi0;
	pi_lcn->lcnphy_cal_results.txiqlocal_fq0 = fq0;

	wlc_lcnphy_set_bbmult(pi, save_bb_mult);
	wlc_lcnphy_set_pa_gain(pi, save_pa_gain);
	wlc_lcnphy_set_tx_gain(pi, &old_gains);

	if (SAVE_txpwrctrl != LCNPHY_TX_PWR_CTRL_OFF)
		wlc_lcnphy_set_tx_pwr_ctrl(pi, SAVE_txpwrctrl);
	else
		wlc_lcnphy_set_tx_pwr_by_index(pi, SAVE_txpwrindex);
}