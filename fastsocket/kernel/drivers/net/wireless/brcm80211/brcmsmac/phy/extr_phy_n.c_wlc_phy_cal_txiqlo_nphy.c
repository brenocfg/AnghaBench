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
typedef  int u32 ;
typedef  int u16 ;
struct nphy_txgains {int dummy; } ;
struct nphy_iqcal_params {int cal_gain; int* ncorr; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int phyhang_avoid; scalar_t__ mphase_cal_phase_id; int* mphase_txcal_bestcoeffs; int nphy_txiqlocal_coeffsvalid; int* nphy_txiqlocal_bestc; int mphase_txcal_cmdidx; int mphase_txcal_numcmds; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/  nphy_txiqlocal_chanspec; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ MPHASE_CAL_STATE_TXPHASE0 ; 
 int MPHASE_CAL_STATE_TXPHASE4 ; 
 int MPHASE_CAL_STATE_TXPHASE5 ; 
 int NPHY_N_GCTL ; 
 int /*<<< orphan*/  NPHY_TBL_ID_IQLOCAL ; 
 int /*<<< orphan*/  NPHY_TBL_ID_RFSEQ ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 scalar_t__ WARN (int,char*) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_iqcal_gainparams_nphy (struct brcms_phy*,int,struct nphy_txgains,struct nphy_iqcal_params*) ; 
 int /*<<< orphan*/  wlc_phy_runsamples_nphy (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_stopplayback_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_tx_iq_war_nphy (struct brcms_phy*) ; 
 int wlc_phy_tx_tone_nphy (struct brcms_phy*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_txcal_phycleanup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txcal_physetup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txcal_radio_cleanup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txcal_radio_setup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_update_txcal_ladder_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

int
wlc_phy_cal_txiqlo_nphy(struct brcms_phy *pi, struct nphy_txgains target_gain,
			bool fullcal, bool mphase)
{
	u16 val;
	u16 tbl_buf[11];
	u8 cal_cnt;
	u16 cal_cmd;
	u8 num_cals, max_cal_cmds;
	u16 core_no, cal_type;
	u16 diq_start = 0;
	u8 phy_bw;
	u16 max_val;
	u16 tone_freq;
	u16 gain_save[2];
	u16 cal_gain[2];
	struct nphy_iqcal_params cal_params[2];
	u32 tbl_len;
	void *tbl_ptr;
	bool ladder_updated[2];
	u8 mphase_cal_lastphase = 0;
	int bcmerror = 0;
	bool phyhang_avoid_state = false;

	u16 tbl_tx_iqlo_cal_loft_ladder_20[] = {
		0x0300, 0x0500, 0x0700, 0x0900, 0x0d00, 0x1100, 0x1900, 0x1901,
		0x1902,
		0x1903, 0x1904, 0x1905, 0x1906, 0x1907, 0x2407, 0x3207, 0x4607,
		0x6407
	};

	u16 tbl_tx_iqlo_cal_iqimb_ladder_20[] = {
		0x0200, 0x0300, 0x0600, 0x0900, 0x0d00, 0x1100, 0x1900, 0x2400,
		0x3200,
		0x4600, 0x6400, 0x6401, 0x6402, 0x6403, 0x6404, 0x6405, 0x6406,
		0x6407
	};

	u16 tbl_tx_iqlo_cal_loft_ladder_40[] = {
		0x0200, 0x0300, 0x0400, 0x0700, 0x0900, 0x0c00, 0x1200, 0x1201,
		0x1202,
		0x1203, 0x1204, 0x1205, 0x1206, 0x1207, 0x1907, 0x2307, 0x3207,
		0x4707
	};

	u16 tbl_tx_iqlo_cal_iqimb_ladder_40[] = {
		0x0100, 0x0200, 0x0400, 0x0700, 0x0900, 0x0c00, 0x1200, 0x1900,
		0x2300,
		0x3200, 0x4700, 0x4701, 0x4702, 0x4703, 0x4704, 0x4705, 0x4706,
		0x4707
	};

	u16 tbl_tx_iqlo_cal_startcoefs[] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000
	};

	u16 tbl_tx_iqlo_cal_cmds_fullcal[] = {
		0x8123, 0x8264, 0x8086, 0x8245, 0x8056,
		0x9123, 0x9264, 0x9086, 0x9245, 0x9056
	};

	u16 tbl_tx_iqlo_cal_cmds_recal[] = {
		0x8101, 0x8253, 0x8053, 0x8234, 0x8034,
		0x9101, 0x9253, 0x9053, 0x9234, 0x9034
	};

	u16 tbl_tx_iqlo_cal_startcoefs_nphyrev3[] = {
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000
	};

	u16 tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3[] = {
		0x8434, 0x8334, 0x8084, 0x8267, 0x8056, 0x8234,
		0x9434, 0x9334, 0x9084, 0x9267, 0x9056, 0x9234
	};

	u16 tbl_tx_iqlo_cal_cmds_recal_nphyrev3[] = {
		0x8423, 0x8323, 0x8073, 0x8256, 0x8045, 0x8223,
		0x9423, 0x9323, 0x9073, 0x9256, 0x9045, 0x9223
	};

	wlc_phy_stay_in_carriersearch_nphy(pi, true);

	if (NREV_GE(pi->pubpi.phy_rev, 4)) {
		phyhang_avoid_state = pi->phyhang_avoid;
		pi->phyhang_avoid = false;
	}

	if (CHSPEC_IS40(pi->radio_chanspec))
		phy_bw = 40;
	else
		phy_bw = 20;

	wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_RFSEQ, 2, 0x110, 16, gain_save);

	for (core_no = 0; core_no <= 1; core_no++) {
		wlc_phy_iqcal_gainparams_nphy(pi, core_no, target_gain,
					      &cal_params[core_no]);
		cal_gain[core_no] = cal_params[core_no].cal_gain;
	}

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, 2, 0x110, 16, cal_gain);

	wlc_phy_txcal_radio_setup_nphy(pi);

	wlc_phy_txcal_physetup_nphy(pi);

	ladder_updated[0] = ladder_updated[1] = false;
	if (!(NREV_GE(pi->pubpi.phy_rev, 6) ||
	      (NREV_IS(pi->pubpi.phy_rev, 5) && PHY_IPA(pi)
	       && (CHSPEC_IS2G(pi->radio_chanspec))))) {

		if (phy_bw == 40) {
			tbl_ptr = tbl_tx_iqlo_cal_loft_ladder_40;
			tbl_len = ARRAY_SIZE(tbl_tx_iqlo_cal_loft_ladder_40);
		} else {
			tbl_ptr = tbl_tx_iqlo_cal_loft_ladder_20;
			tbl_len = ARRAY_SIZE(tbl_tx_iqlo_cal_loft_ladder_20);
		}
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, tbl_len, 0,
					 16, tbl_ptr);

		if (phy_bw == 40) {
			tbl_ptr = tbl_tx_iqlo_cal_iqimb_ladder_40;
			tbl_len = ARRAY_SIZE(tbl_tx_iqlo_cal_iqimb_ladder_40);
		} else {
			tbl_ptr = tbl_tx_iqlo_cal_iqimb_ladder_20;
			tbl_len = ARRAY_SIZE(tbl_tx_iqlo_cal_iqimb_ladder_20);
		}
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, tbl_len, 32,
					 16, tbl_ptr);
	}

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		write_phy_reg(pi, 0xc2, 0x8ad9);
	else
		write_phy_reg(pi, 0xc2, 0x8aa9);

	max_val = 250;
	tone_freq = (phy_bw == 20) ? 2500 : 5000;

	if (pi->mphase_cal_phase_id > MPHASE_CAL_STATE_TXPHASE0) {
		wlc_phy_runsamples_nphy(pi, phy_bw * 8, 0xffff, 0, 1, 0, false);
		bcmerror = 0;
	} else {
		bcmerror =
			wlc_phy_tx_tone_nphy(pi, tone_freq, max_val, 1, 0,
					     false);
	}

	if (bcmerror == 0) {

		if (pi->mphase_cal_phase_id > MPHASE_CAL_STATE_TXPHASE0) {
			tbl_ptr = pi->mphase_txcal_bestcoeffs;
			tbl_len = ARRAY_SIZE(pi->mphase_txcal_bestcoeffs);
			if (NREV_LT(pi->pubpi.phy_rev, 3))
				tbl_len -= 2;
		} else {
			if ((!fullcal) && (pi->nphy_txiqlocal_coeffsvalid)) {

				tbl_ptr = pi->nphy_txiqlocal_bestc;
				tbl_len = ARRAY_SIZE(pi->nphy_txiqlocal_bestc);
				if (NREV_LT(pi->pubpi.phy_rev, 3))
					tbl_len -= 2;
			} else {

				fullcal = true;

				if (NREV_GE(pi->pubpi.phy_rev, 3)) {
					tbl_ptr =
					    tbl_tx_iqlo_cal_startcoefs_nphyrev3;
					tbl_len = ARRAY_SIZE(
					   tbl_tx_iqlo_cal_startcoefs_nphyrev3);
				} else {
					tbl_ptr = tbl_tx_iqlo_cal_startcoefs;
					tbl_len = ARRAY_SIZE(
						    tbl_tx_iqlo_cal_startcoefs);
				}
			}
		}
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, tbl_len, 64,
					 16, tbl_ptr);

		if (fullcal) {
			max_cal_cmds = (NREV_GE(pi->pubpi.phy_rev, 3)) ?
				       ARRAY_SIZE(
				tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3) :
				       ARRAY_SIZE(tbl_tx_iqlo_cal_cmds_fullcal);
		} else {
			max_cal_cmds = (NREV_GE(pi->pubpi.phy_rev, 3)) ?
				       ARRAY_SIZE(
				tbl_tx_iqlo_cal_cmds_recal_nphyrev3) :
				       ARRAY_SIZE(tbl_tx_iqlo_cal_cmds_recal);
		}

		if (mphase) {
			cal_cnt = pi->mphase_txcal_cmdidx;
			if ((cal_cnt + pi->mphase_txcal_numcmds) < max_cal_cmds)
				num_cals = cal_cnt + pi->mphase_txcal_numcmds;
			else
				num_cals = max_cal_cmds;
		} else {
			cal_cnt = 0;
			num_cals = max_cal_cmds;
		}

		for (; cal_cnt < num_cals; cal_cnt++) {

			if (fullcal) {
				cal_cmd = (NREV_GE(pi->pubpi.phy_rev, 3)) ?
					  tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3
					  [cal_cnt] :
					  tbl_tx_iqlo_cal_cmds_fullcal[cal_cnt];
			} else {
				cal_cmd = (NREV_GE(pi->pubpi.phy_rev, 3)) ?
					  tbl_tx_iqlo_cal_cmds_recal_nphyrev3[
					cal_cnt]
					  : tbl_tx_iqlo_cal_cmds_recal[cal_cnt];
			}

			core_no = ((cal_cmd & 0x3000) >> 12);
			cal_type = ((cal_cmd & 0x0F00) >> 8);

			if (NREV_GE(pi->pubpi.phy_rev, 6) ||
			    (NREV_IS(pi->pubpi.phy_rev, 5) &&
			     PHY_IPA(pi)
			     && (CHSPEC_IS2G(pi->radio_chanspec)))) {
				if (!ladder_updated[core_no]) {
					wlc_phy_update_txcal_ladder_nphy(
						pi,
						core_no);
					ladder_updated[core_no] = true;
				}
			}

			val =
				(cal_params[core_no].
				 ncorr[cal_type] << 8) | NPHY_N_GCTL;
			write_phy_reg(pi, 0xc1, val);

			if ((cal_type == 1) || (cal_type == 3)
			    || (cal_type == 4)) {

				wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL,
							1, 69 + core_no, 16,
							tbl_buf);

				diq_start = tbl_buf[0];

				tbl_buf[0] = 0;
				wlc_phy_table_write_nphy(pi,
							 NPHY_TBL_ID_IQLOCAL, 1,
							 69 + core_no, 16,
							 tbl_buf);
			}

			write_phy_reg(pi, 0xc0, cal_cmd);

			SPINWAIT(((read_phy_reg(pi, 0xc0) & 0xc000) != 0),
				 20000);
			if (WARN(read_phy_reg(pi, 0xc0) & 0xc000,
				 "HW error: txiq calib"))
				return -EIO;

			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL,
						tbl_len, 96, 16, tbl_buf);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL,
						 tbl_len, 64, 16, tbl_buf);

			if ((cal_type == 1) || (cal_type == 3)
			    || (cal_type == 4)) {

				tbl_buf[0] = diq_start;

			}

		}

		if (mphase) {
			pi->mphase_txcal_cmdidx = num_cals;
			if (pi->mphase_txcal_cmdidx >= max_cal_cmds)
				pi->mphase_txcal_cmdidx = 0;
		}

		mphase_cal_lastphase =
			(NREV_LE(pi->pubpi.phy_rev, 2)) ?
			MPHASE_CAL_STATE_TXPHASE4 : MPHASE_CAL_STATE_TXPHASE5;

		if (!mphase
		    || (pi->mphase_cal_phase_id == mphase_cal_lastphase)) {

			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL, 4, 96,
						16, tbl_buf);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 4, 80,
						 16, tbl_buf);

			if (NREV_LT(pi->pubpi.phy_rev, 2)) {

				tbl_buf[0] = 0;
				tbl_buf[1] = 0;
				tbl_buf[2] = 0;
				tbl_buf[3] = 0;

			}
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 4, 88,
						 16, tbl_buf);

			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL, 2, 101,
						16, tbl_buf);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 2, 85,
						 16, tbl_buf);

			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 2, 93,
						 16, tbl_buf);

			tbl_len = ARRAY_SIZE(pi->nphy_txiqlocal_bestc);
			if (NREV_LT(pi->pubpi.phy_rev, 3))
				tbl_len -= 2;

			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL,
						tbl_len, 96, 16,
						pi->nphy_txiqlocal_bestc);

			pi->nphy_txiqlocal_coeffsvalid = true;
			pi->nphy_txiqlocal_chanspec = pi->radio_chanspec;
		} else {
			tbl_len = ARRAY_SIZE(pi->mphase_txcal_bestcoeffs);
			if (NREV_LT(pi->pubpi.phy_rev, 3))
				tbl_len -= 2;

			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_IQLOCAL,
						tbl_len, 96, 16,
						pi->mphase_txcal_bestcoeffs);
		}

		wlc_phy_stopplayback_nphy(pi);

		write_phy_reg(pi, 0xc2, 0x0000);

	}

	wlc_phy_txcal_phycleanup_nphy(pi);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, 2, 0x110, 16,
				 gain_save);

	wlc_phy_txcal_radio_cleanup_nphy(pi);

	if (NREV_LT(pi->pubpi.phy_rev, 2)) {
		if (!mphase
		    || (pi->mphase_cal_phase_id == mphase_cal_lastphase))
			wlc_phy_tx_iq_war_nphy(pi);
	}

	if (NREV_GE(pi->pubpi.phy_rev, 4))
		pi->phyhang_avoid = phyhang_avoid_state;

	wlc_phy_stay_in_carriersearch_nphy(pi, false);

	return bcmerror;
}