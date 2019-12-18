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
typedef  int u32 ;
struct TYPE_2__ {int hw_caps; int /*<<< orphan*/  tx_chainmask; int /*<<< orphan*/  rx_chainmask; } ;
struct ath_hw {int enabled_cals; int ah_flags; int /*<<< orphan*/ * cal_list_curr; int /*<<< orphan*/ * cal_list; int /*<<< orphan*/  iq_caldata; int /*<<< orphan*/ * cal_list_last; int /*<<< orphan*/  txchainmask; int /*<<< orphan*/  rxchainmask; TYPE_1__ caps; struct ath9k_hw_cal_data* caldata; } ;
struct ath_common {int dummy; } ;
struct ath9k_hw_cal_data {scalar_t__ CalValid; scalar_t__ done_txiqcal_once; scalar_t__ done_txclcal_once; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int AH_FASTCC ; 
 int AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_PHY_ACTIVE ; 
 int AR_PHY_ACTIVE_DIS ; 
 int AR_PHY_ACTIVE_EN ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_CAL ; 
 int AR_PHY_AGC_CONTROL_FLTR_CAL ; 
 int AR_PHY_AGC_CONTROL_OFFSET_CAL ; 
 int AR_PHY_AGC_CONTROL_PKDET_CAL ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_CTL ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_1 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT ; 
 int ATH9K_HW_CAP_RTT ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int /*<<< orphan*/  DELPT ; 
 int /*<<< orphan*/  INIT_CAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSERT_CAL (struct ath_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int TX_CL_CAL ; 
 int TX_IQ_CAL ; 
 int TX_IQ_ON_AGC_CAL ; 
 int /*<<< orphan*/  ar9003_hw_cl_cal_post_proc (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_do_manual_peak_cal (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_clear_hist (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_enable (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_fill_hist (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_restore (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_set_mask (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_set_chain_masks (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_tx_iq_cal_post_proc (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_tx_iq_cal_reload (struct ath_hw*) ; 
 int ar9003_hw_tx_iq_cal_run (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_init_cal_done (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_init_cal_req (struct ath_hw*,int*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_reset_calibration (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_done (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_req (struct ath_hw*) ; 
 int ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ar9003_hw_init_cal(struct ath_hw *ah,
			       struct ath9k_channel *chan)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_cal_data *caldata = ah->caldata;
	bool txiqcal_done = false;
	bool is_reusable = true, status = true;
	bool run_rtt_cal = false, run_agc_cal, sep_iq_cal = false;
	bool rtt = !!(ah->caps.hw_caps & ATH9K_HW_CAP_RTT);
	u32 agc_ctrl = 0, agc_supp_cals = AR_PHY_AGC_CONTROL_OFFSET_CAL |
					  AR_PHY_AGC_CONTROL_FLTR_CAL   |
					  AR_PHY_AGC_CONTROL_PKDET_CAL;

	/* Use chip chainmask only for calibration */
	ar9003_hw_set_chain_masks(ah, ah->caps.rx_chainmask, ah->caps.tx_chainmask);

	if (rtt) {
		if (!ar9003_hw_rtt_restore(ah, chan))
			run_rtt_cal = true;

		if (run_rtt_cal)
			ath_dbg(common, CALIBRATE, "RTT calibration to be done\n");
	}

	run_agc_cal = run_rtt_cal;

	if (run_rtt_cal) {
		ar9003_hw_rtt_enable(ah);
		ar9003_hw_rtt_set_mask(ah, 0x00);
		ar9003_hw_rtt_clear_hist(ah);
	}

	if (rtt && !run_rtt_cal) {
		agc_ctrl = REG_READ(ah, AR_PHY_AGC_CONTROL);
		agc_supp_cals &= agc_ctrl;
		agc_ctrl &= ~(AR_PHY_AGC_CONTROL_OFFSET_CAL |
			     AR_PHY_AGC_CONTROL_FLTR_CAL |
			     AR_PHY_AGC_CONTROL_PKDET_CAL);
		REG_WRITE(ah, AR_PHY_AGC_CONTROL, agc_ctrl);
	}

	if (ah->enabled_cals & TX_CL_CAL) {
		if (caldata && caldata->done_txclcal_once)
			REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL,
				    AR_PHY_CL_CAL_ENABLE);
		else {
			REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL,
				    AR_PHY_CL_CAL_ENABLE);
			run_agc_cal = true;
		}
	}

	if ((IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan)) ||
	    !(ah->enabled_cals & TX_IQ_CAL))
		goto skip_tx_iqcal;

	/* Do Tx IQ Calibration */
	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_1,
		      AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT,
		      DELPT);

	/*
	 * For AR9485 or later chips, TxIQ cal runs as part of
	 * AGC calibration
	 */
	if (ah->enabled_cals & TX_IQ_ON_AGC_CAL) {
		if (caldata && !caldata->done_txiqcal_once)
			REG_SET_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);
		else
			REG_CLR_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);
		txiqcal_done = run_agc_cal = true;
	} else if (caldata && !caldata->done_txiqcal_once) {
		run_agc_cal = true;
		sep_iq_cal = true;
	}

skip_tx_iqcal:
	if (ath9k_hw_mci_is_enabled(ah) && IS_CHAN_2GHZ(chan) && run_agc_cal)
		ar9003_mci_init_cal_req(ah, &is_reusable);

	if (sep_iq_cal) {
		txiqcal_done = ar9003_hw_tx_iq_cal_run(ah);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
		udelay(5);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	}

	if (run_agc_cal || !(ah->ah_flags & AH_FASTCC)) {
		/* Calibrate the AGC */
		REG_WRITE(ah, AR_PHY_AGC_CONTROL,
			  REG_READ(ah, AR_PHY_AGC_CONTROL) |
			  AR_PHY_AGC_CONTROL_CAL);

		/* Poll for offset calibration complete */
		status = ath9k_hw_wait(ah, AR_PHY_AGC_CONTROL,
				       AR_PHY_AGC_CONTROL_CAL,
				       0, AH_WAIT_TIMEOUT);

		ar9003_hw_do_manual_peak_cal(ah, chan);
	}

	if (ath9k_hw_mci_is_enabled(ah) && IS_CHAN_2GHZ(chan) && run_agc_cal)
		ar9003_mci_init_cal_done(ah);

	if (rtt && !run_rtt_cal) {
		agc_ctrl |= agc_supp_cals;
		REG_WRITE(ah, AR_PHY_AGC_CONTROL, agc_ctrl);
	}

	if (!status) {
		if (run_rtt_cal)
			ar9003_hw_rtt_disable(ah);

		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms; noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		return false;
	}

	if (txiqcal_done)
		ar9003_hw_tx_iq_cal_post_proc(ah, is_reusable);
	else if (caldata && caldata->done_txiqcal_once)
		ar9003_hw_tx_iq_cal_reload(ah);

	ar9003_hw_cl_cal_post_proc(ah, is_reusable);

	if (run_rtt_cal && caldata) {
		if (is_reusable) {
			if (!ath9k_hw_rfbus_req(ah))
				ath_err(ath9k_hw_common(ah),
					"Could not stop baseband\n");
			else
				ar9003_hw_rtt_fill_hist(ah);

			ath9k_hw_rfbus_done(ah);
		}

		ar9003_hw_rtt_disable(ah);
	}

	/* Revert chainmask to runtime parameters */
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);

	/* Initialize list pointers */
	ah->cal_list = ah->cal_list_last = ah->cal_list_curr = NULL;

	INIT_CAL(&ah->iq_caldata);
	INSERT_CAL(ah, &ah->iq_caldata);
	ath_dbg(common, CALIBRATE, "enabling IQ Calibration\n");

	/* Initialize current pointer to first element in list */
	ah->cal_list_curr = ah->cal_list;

	if (ah->cal_list_curr)
		ath9k_hw_reset_calibration(ah, ah->cal_list_curr);

	if (caldata)
		caldata->CalValid = 0;

	return true;
}