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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ tx_intr_mitigation; scalar_t__ rx_intr_mitigation; } ;
struct TYPE_5__ {int hw_caps; } ;
struct ath_hw {int chip_fullsleep; int paprd_table_write_done; int htc_reset_init; scalar_t__ shared_chain_lnadiv; TYPE_3__ config; int /*<<< orphan*/  rfkill_gpio; TYPE_2__ caps; int /*<<< orphan*/  opmode; TYPE_1__* eep_ops; int /*<<< orphan*/  noise; struct ath9k_hw_cal_data* caldata; scalar_t__ curchan; } ;
struct ath_common {int dummy; } ;
struct ath9k_hw_cal_data {scalar_t__ channel; scalar_t__ channelFlags; scalar_t__ chanmode; int paprd_packet_sent; int done_txiqcal_once; int done_txclcal_once; } ;
struct ath9k_channel {scalar_t__ channel; scalar_t__ channelFlags; scalar_t__ chanmode; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_board_values ) (struct ath_hw*,struct ath9k_channel*) ;scalar_t__ (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AR9271_GATE_MAC_CTL ; 
 int AR9271_RADIO_RF_RST ; 
 int /*<<< orphan*/  AR9271_RESET_POWER_DOWN_CONTROL ; 
 int AR_AHB_CUSTOM_BURST_ASYNC_FIFO_VAL ; 
 int /*<<< orphan*/  AR_AHB_CUSTOM_BURST_EN ; 
 int /*<<< orphan*/  AR_AHB_MODE ; 
 int /*<<< orphan*/  AR_BTCOEX_WL_LNADIV ; 
 int /*<<< orphan*/  AR_BTCOEX_WL_LNADIV_FORCE_ON ; 
 int /*<<< orphan*/  AR_CFG_LED ; 
 int AR_CFG_LED_ASSOC_CTL ; 
 int AR_CFG_LED_BLINK_SLOW ; 
 int AR_CFG_LED_BLINK_THRESH_SEL ; 
 int AR_CFG_LED_MODE_SEL ; 
 int AR_CFG_SCLK_32KHZ ; 
 int /*<<< orphan*/  AR_DEF_ANTENNA ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int /*<<< orphan*/  AR_GPIO_JTAG_DISABLE ; 
 int /*<<< orphan*/  AR_MAC_PCU_LOGIC_ANALYZER ; 
 int /*<<< orphan*/  AR_MAC_PCU_LOGIC_ANALYZER_DISBUG20768 ; 
 int /*<<< orphan*/  AR_OBS ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2 ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2_ENABLE_AGGWEP ; 
 int /*<<< orphan*/  AR_RIMT ; 
 int /*<<< orphan*/  AR_RIMT_FIRST ; 
 int /*<<< orphan*/  AR_RIMT_LAST ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_13_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_BASE_RATE_11B ; 
 int /*<<< orphan*/  AR_STA_ID1_PRESERVE_SEQNUM ; 
 int /*<<< orphan*/  AR_TIMT ; 
 int /*<<< orphan*/  AR_TIMT_FIRST ; 
 int /*<<< orphan*/  AR_TIMT_LAST ; 
 int ATH9K_HW_CAP_RFSILENT ; 
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int /*<<< orphan*/  EEP_OL_PWRCTRL ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_OFDM (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9002_hw_enable_async_fifo (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_bb_watchdog_config (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_disable_phy_restart (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_check_bt (struct ath_hw*) ; 
 scalar_t__ ar9003_mci_end_reset (struct ath_hw*,struct ath9k_channel*,struct ath9k_hw_cal_data*) ; 
 int /*<<< orphan*/  ar9003_mci_reset (struct ath_hw*,int,int /*<<< orphan*/ ,int) ; 
 int ar9003_mci_start_reset (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_mci_stop_bt (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_ani_cache_ini_regs (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_apply_gpio_override (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_enable (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_btcoex_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_cfg_gpio_input (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_chip_reset (struct ath_hw*,struct ath9k_channel*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_do_fastcc (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_getchan_noise (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_getnf (struct ath_hw*,scalar_t__) ; 
 scalar_t__ ath9k_hw_gettsf64 (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_bb (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_init_cal (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_init_desc (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_interrupt_masks (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_init_mfp (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_qos (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_queues (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_loadnf (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_mark_phy_inactive (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int ath9k_hw_process_ini (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_reset_opmode (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  ath9k_hw_restore_chainmask (struct ath_hw*) ; 
 int ath9k_hw_rf_set_freq (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_set_clockrate (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_delta_slope (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_set_dma (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_settsf64 (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath9k_hw_spur_mitigate_freq (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_start_nfcal (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_init_nfcal_hist_buffer (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  memset (struct ath9k_hw_cal_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ath9k_hw_reset(struct ath_hw *ah, struct ath9k_channel *chan,
		   struct ath9k_hw_cal_data *caldata, bool fastcc)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 saveLedState;
	u32 saveDefAntenna;
	u32 macStaId1;
	u64 tsf = 0;
	int r;
	bool start_mci_reset = false;
	bool save_fullsleep = ah->chip_fullsleep;

	if (ath9k_hw_mci_is_enabled(ah)) {
		start_mci_reset = ar9003_mci_start_reset(ah, chan);
		if (start_mci_reset)
			return 0;
	}

	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE))
		return -EIO;

	if (ah->curchan && !ah->chip_fullsleep)
		ath9k_hw_getnf(ah, ah->curchan);

	ah->caldata = caldata;
	if (caldata && (chan->channel != caldata->channel ||
			chan->channelFlags != caldata->channelFlags ||
			chan->chanmode != caldata->chanmode)) {
		/* Operating channel changed, reset channel calibration data */
		memset(caldata, 0, sizeof(*caldata));
		ath9k_init_nfcal_hist_buffer(ah, chan);
	} else if (caldata) {
		caldata->paprd_packet_sent = false;
	}
	ah->noise = ath9k_hw_getchan_noise(ah, chan);

	if (fastcc) {
		r = ath9k_hw_do_fastcc(ah, chan);
		if (!r)
			return r;
	}

	if (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_stop_bt(ah, save_fullsleep);

	saveDefAntenna = REG_READ(ah, AR_DEF_ANTENNA);
	if (saveDefAntenna == 0)
		saveDefAntenna = 1;

	macStaId1 = REG_READ(ah, AR_STA_ID1) & AR_STA_ID1_BASE_RATE_11B;

	/* For chips on which RTC reset is done, save TSF before it gets cleared */
	if (AR_SREV_9100(ah) ||
	    (AR_SREV_9280(ah) && ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL)))
		tsf = ath9k_hw_gettsf64(ah);

	saveLedState = REG_READ(ah, AR_CFG_LED) &
		(AR_CFG_LED_ASSOC_CTL | AR_CFG_LED_MODE_SEL |
		 AR_CFG_LED_BLINK_THRESH_SEL | AR_CFG_LED_BLINK_SLOW);

	ath9k_hw_mark_phy_inactive(ah);

	ah->paprd_table_write_done = false;

	/* Only required on the first reset */
	if (AR_SREV_9271(ah) && ah->htc_reset_init) {
		REG_WRITE(ah,
			  AR9271_RESET_POWER_DOWN_CONTROL,
			  AR9271_RADIO_RF_RST);
		udelay(50);
	}

	if (!ath9k_hw_chip_reset(ah, chan)) {
		ath_err(common, "Chip reset failed\n");
		return -EINVAL;
	}

	/* Only required on the first reset */
	if (AR_SREV_9271(ah) && ah->htc_reset_init) {
		ah->htc_reset_init = false;
		REG_WRITE(ah,
			  AR9271_RESET_POWER_DOWN_CONTROL,
			  AR9271_GATE_MAC_CTL);
		udelay(50);
	}

	/* Restore TSF */
	if (tsf)
		ath9k_hw_settsf64(ah, tsf);

	if (AR_SREV_9280_20_OR_LATER(ah))
		REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL, AR_GPIO_JTAG_DISABLE);

	if (!AR_SREV_9300_20_OR_LATER(ah))
		ar9002_hw_enable_async_fifo(ah);

	r = ath9k_hw_process_ini(ah, chan);
	if (r)
		return r;

	if (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_reset(ah, false, IS_CHAN_2GHZ(chan), save_fullsleep);

	/*
	 * Some AR91xx SoC devices frequently fail to accept TSF writes
	 * right after the chip reset. When that happens, write a new
	 * value after the initvals have been applied, with an offset
	 * based on measured time difference
	 */
	if (AR_SREV_9100(ah) && (ath9k_hw_gettsf64(ah) < tsf)) {
		tsf += 1500;
		ath9k_hw_settsf64(ah, tsf);
	}

	ath9k_hw_init_mfp(ah);

	if (IS_CHAN_OFDM(chan) || IS_CHAN_HT(chan))
		ath9k_hw_set_delta_slope(ah, chan);

	ath9k_hw_spur_mitigate_freq(ah, chan);
	ah->eep_ops->set_board_values(ah, chan);

	ath9k_hw_reset_opmode(ah, macStaId1, saveDefAntenna);

	r = ath9k_hw_rf_set_freq(ah, chan);
	if (r)
		return r;

	ath9k_hw_set_clockrate(ah);

	ath9k_hw_init_queues(ah);
	ath9k_hw_init_interrupt_masks(ah, ah->opmode);
	ath9k_hw_ani_cache_ini_regs(ah);
	ath9k_hw_init_qos(ah);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_RFSILENT)
		ath9k_hw_cfg_gpio_input(ah, ah->rfkill_gpio);

	ath9k_hw_init_global_settings(ah);

	if (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah)) {
		REG_SET_BIT(ah, AR_MAC_PCU_LOGIC_ANALYZER,
			    AR_MAC_PCU_LOGIC_ANALYZER_DISBUG20768);
		REG_RMW_FIELD(ah, AR_AHB_MODE, AR_AHB_CUSTOM_BURST_EN,
			      AR_AHB_CUSTOM_BURST_ASYNC_FIFO_VAL);
		REG_SET_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_ENABLE_AGGWEP);
	}

	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PRESERVE_SEQNUM);

	ath9k_hw_set_dma(ah);

	if (!ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_OBS, 8);

	if (ah->config.rx_intr_mitigation) {
		REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_LAST, 500);
		REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_FIRST, 2000);
	}

	if (ah->config.tx_intr_mitigation) {
		REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_LAST, 300);
		REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_FIRST, 750);
	}

	ath9k_hw_init_bb(ah, chan);

	if (caldata) {
		caldata->done_txiqcal_once = false;
		caldata->done_txclcal_once = false;
	}
	if (!ath9k_hw_init_cal(ah, chan))
		return -EIO;

	if (ath9k_hw_mci_is_enabled(ah) && ar9003_mci_end_reset(ah, chan, caldata))
		return -EIO;

	ENABLE_REGWRITE_BUFFER(ah);

	ath9k_hw_restore_chainmask(ah);
	REG_WRITE(ah, AR_CFG_LED, saveLedState | AR_CFG_SCLK_32KHZ);

	REGWRITE_BUFFER_FLUSH(ah);

	ath9k_hw_init_desc(ah);

	if (ath9k_hw_btcoex_is_enabled(ah))
		ath9k_hw_btcoex_enable(ah);

	if (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_check_bt(ah);

	ath9k_hw_loadnf(ah, chan);
	ath9k_hw_start_nfcal(ah, true);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ar9003_hw_bb_watchdog_config(ah);
		ar9003_hw_disable_phy_restart(ah);
	}

	ath9k_hw_apply_gpio_override(ah);

	if (AR_SREV_9565(ah) && ah->shared_chain_lnadiv)
		REG_SET_BIT(ah, AR_BTCOEX_WL_LNADIV, AR_BTCOEX_WL_LNADIV_FORCE_ON);

	return 0;
}