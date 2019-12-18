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
typedef  int u32 ;
struct ath_hw {int modes_index; int /*<<< orphan*/  enabled_cals; int /*<<< orphan*/  txchainmask; int /*<<< orphan*/  rxchainmask; int /*<<< orphan*/  iniCckfirJapan2484; int /*<<< orphan*/  iniAdditional; int /*<<< orphan*/  iniModesFastClock; int /*<<< orphan*/  iniModesTxGain; int /*<<< orphan*/  ini_modes_rx_gain_bounds; int /*<<< orphan*/  iniModesRxGain; int /*<<< orphan*/  ini_radio_post_sys2ant; int /*<<< orphan*/ * iniRadio; int /*<<< orphan*/ * iniBB; int /*<<< orphan*/ * iniMac; int /*<<< orphan*/ * iniSOC; } ;
struct ath9k_channel {int chanmode; int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GLB_SWREG_DISCONT_EN_BT_WLAN ; 
 int /*<<< orphan*/  AR_GLB_SWREG_DISCONT_MODE ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_CTL ; 
 int AR_PHY_CL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 unsigned int ATH_INI_NUM_SPLIT ; 
 unsigned int ATH_INI_POST ; 
#define  CHANNEL_A 136 
#define  CHANNEL_A_HT20 135 
#define  CHANNEL_A_HT40MINUS 134 
#define  CHANNEL_A_HT40PLUS 133 
#define  CHANNEL_B 132 
#define  CHANNEL_G 131 
#define  CHANNEL_G_HT20 130 
#define  CHANNEL_G_HT40MINUS 129 
#define  CHANNEL_G_HT40PLUS 128 
 int EINVAL ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE_ARRAY (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  TX_CL_CAL ; 
 int /*<<< orphan*/  TX_IQ_CAL ; 
 int /*<<< orphan*/  ar9003_hw_override_ini (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_prog_ini (struct ath_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9003_hw_set_chain_masks (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_set_channel_regs (struct ath_hw*,struct ath9k_channel*) ; 
 int ar9550_hw_get_modes_txgain_index (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_apply_txpower (struct ath_hw*,struct ath9k_channel*,int) ; 

__attribute__((used)) static int ar9003_hw_process_ini(struct ath_hw *ah,
				 struct ath9k_channel *chan)
{
	unsigned int regWrites = 0, i;
	u32 modesIndex;

	switch (chan->chanmode) {
	case CHANNEL_A:
	case CHANNEL_A_HT20:
		modesIndex = 1;
		break;
	case CHANNEL_A_HT40PLUS:
	case CHANNEL_A_HT40MINUS:
		modesIndex = 2;
		break;
	case CHANNEL_G:
	case CHANNEL_G_HT20:
	case CHANNEL_B:
		modesIndex = 4;
		break;
	case CHANNEL_G_HT40PLUS:
	case CHANNEL_G_HT40MINUS:
		modesIndex = 3;
		break;

	default:
		return -EINVAL;
	}

	for (i = 0; i < ATH_INI_NUM_SPLIT; i++) {
		ar9003_hw_prog_ini(ah, &ah->iniSOC[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniMac[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniBB[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniRadio[i], modesIndex);
		if (i == ATH_INI_POST && AR_SREV_9462_20(ah))
			ar9003_hw_prog_ini(ah,
					   &ah->ini_radio_post_sys2ant,
					   modesIndex);
	}

	REG_WRITE_ARRAY(&ah->iniModesRxGain, 1, regWrites);
	if (AR_SREV_9550(ah))
		REG_WRITE_ARRAY(&ah->ini_modes_rx_gain_bounds, modesIndex,
				regWrites);

	if (AR_SREV_9550(ah)) {
		int modes_txgain_index;

		modes_txgain_index = ar9550_hw_get_modes_txgain_index(ah, chan);
		if (modes_txgain_index < 0)
			return -EINVAL;

		REG_WRITE_ARRAY(&ah->iniModesTxGain, modes_txgain_index,
				regWrites);
	} else {
		REG_WRITE_ARRAY(&ah->iniModesTxGain, modesIndex, regWrites);
	}

	/*
	 * For 5GHz channels requiring Fast Clock, apply
	 * different modal values.
	 */
	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock,
				modesIndex, regWrites);

	REG_WRITE_ARRAY(&ah->iniAdditional, 1, regWrites);

	if (chan->channel == 2484)
		ar9003_hw_prog_ini(ah, &ah->iniCckfirJapan2484, 1);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah))
		REG_WRITE(ah, AR_GLB_SWREG_DISCONT_MODE,
			  AR_GLB_SWREG_DISCONT_EN_BT_WLAN);

	ah->modes_index = modesIndex;
	ar9003_hw_override_ini(ah);
	ar9003_hw_set_channel_regs(ah, chan);
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);
	ath9k_hw_apply_txpower(ah, chan, false);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		if (REG_READ_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				   AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL))
			ah->enabled_cals |= TX_IQ_CAL;
		else
			ah->enabled_cals &= ~TX_IQ_CAL;

		if (REG_READ(ah, AR_PHY_CL_CAL_CTL) & AR_PHY_CL_CAL_ENABLE)
			ah->enabled_cals |= TX_CL_CAL;
		else
			ah->enabled_cals &= ~TX_CL_CAL;
	}

	return 0;
}