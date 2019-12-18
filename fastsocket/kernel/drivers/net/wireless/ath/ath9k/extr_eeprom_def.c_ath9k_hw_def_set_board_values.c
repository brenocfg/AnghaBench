#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct modal_eep_header {int antCtrlCommon; int* antCtrlChain; int ob; int db; int ob_ch1; int db_ch1; int xpaBiasLvl; int lna_ctl; int switchSettling; int adcDesiredSize; int pgaDesiredSize; int txEndToRxOn; int thresh62; int txFrameToDataStart; int txFrameToPaOn; int swSettleHt40; int miscBits; int /*<<< orphan*/  txFrameToXpaOn; int /*<<< orphan*/  txEndToXpaOff; int /*<<< orphan*/ * iqCalQCh; int /*<<< orphan*/ * iqCalICh; } ;
struct TYPE_4__ {int dacLpMode; int desiredScaleCCK; scalar_t__ dacHiPwrMode_5G; } ;
struct ar5416_eeprom_def {TYPE_2__ baseEepHeader; struct modal_eep_header* modalHeader; } ;
struct TYPE_3__ {struct ar5416_eeprom_def def; } ;
struct ath_hw {int rxchainmask; int txchainmask; TYPE_1__ eeprom; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR5416_EEP_MINOR_VER_19 ; 
 scalar_t__ AR5416_EEP_MINOR_VER_2 ; 
 scalar_t__ AR5416_EEP_MINOR_VER_20 ; 
 scalar_t__ AR5416_EEP_MINOR_VER_3 ; 
 int AR5416_MAX_CHAINS ; 
 scalar_t__ AR5416_VER_MASK ; 
 int /*<<< orphan*/  AR9280_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH0 ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH0_DB ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH0_DB_S ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH0_OB ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH0_OB_S ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH1 ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH1_DB ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH1_DB_S ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH1_OB ; 
 int /*<<< orphan*/  AR_AN_RF2G1_CH1_OB_S ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH0 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH0_DB5 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH0_DB5_S ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH0_OB5 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH0_OB5_S ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH1 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH1_DB5 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH1_DB5_S ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH1_OB5 ; 
 int /*<<< orphan*/  AR_AN_RF5G1_CH1_OB5_S ; 
 int /*<<< orphan*/  AR_AN_TOP1 ; 
 int /*<<< orphan*/  AR_AN_TOP1_DACIPMODE ; 
 int /*<<< orphan*/  AR_AN_TOP2 ; 
 int /*<<< orphan*/  AR_AN_TOP2_LOCALBIAS ; 
 int /*<<< orphan*/  AR_AN_TOP2_LOCALBIAS_S ; 
 int /*<<< orphan*/  AR_AN_TOP2_XPABIAS_LVL ; 
 int /*<<< orphan*/  AR_AN_TOP2_XPABIAS_LVL_S ; 
 int /*<<< orphan*/  AR_PHY_CCA ; 
 int /*<<< orphan*/  AR_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_CCK_TX_CTRL ; 
 int /*<<< orphan*/  AR_PHY_CCK_TX_CTRL_TX_DAC_SCALE_CCK ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ_ADC ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ_PGA ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_FORCE_XPA_CFG ; 
 int /*<<< orphan*/  AR_PHY_FRAME_CTL ; 
 int /*<<< orphan*/  AR_PHY_FRAME_CTL_TX_CLIP ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL2 ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL3 ; 
 scalar_t__ AR_PHY_RF_CTL4 ; 
 int AR_PHY_RF_CTL4_FRAME_XPAA_ON ; 
 int AR_PHY_RF_CTL4_FRAME_XPAB_ON ; 
 int AR_PHY_RF_CTL4_TX_END_XPAA_OFF ; 
 int AR_PHY_RF_CTL4_TX_END_XPAB_OFF ; 
 int /*<<< orphan*/  AR_PHY_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_SETTLING_SWITCH ; 
 scalar_t__ AR_PHY_SWITCH_CHAIN_0 ; 
 scalar_t__ AR_PHY_SWITCH_COM ; 
 scalar_t__ AR_PHY_TIMING_CTRL4 (int /*<<< orphan*/ ) ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF ; 
 int /*<<< orphan*/  AR_PHY_TX_DESIRED_SCALE_CCK ; 
 int /*<<< orphan*/  AR_PHY_TX_END_DATA_START ; 
 int /*<<< orphan*/  AR_PHY_TX_END_PA_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_END_TO_A2_RX_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL9 ; 
 int /*<<< orphan*/  AR_PHY_XPA_CFG ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int LNA_CTL_FORCE_XPA ; 
 int LNA_CTL_LOCAL_BIAS ; 
 int REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_analog_shift_rmw (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_def_set_gain (struct ath_hw*,struct modal_eep_header*,struct ar5416_eeprom_def*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ath9k_hw_def_set_board_values(struct ath_hw *ah,
					  struct ath9k_channel *chan)
{
	struct modal_eep_header *pModal;
	struct ar5416_eeprom_def *eep = &ah->eeprom.def;
	int i, regChainOffset;
	u8 txRxAttenLocal;

	pModal = &(eep->modalHeader[IS_CHAN_2GHZ(chan)]);
	txRxAttenLocal = IS_CHAN_2GHZ(chan) ? 23 : 44;

	REG_WRITE(ah, AR_PHY_SWITCH_COM, pModal->antCtrlCommon & 0xffff);

	for (i = 0; i < AR5416_MAX_CHAINS; i++) {
		if (AR_SREV_9280(ah)) {
			if (i >= 2)
				break;
		}

		if ((ah->rxchainmask == 5 || ah->txchainmask == 5) && (i != 0))
			regChainOffset = (i == 1) ? 0x2000 : 0x1000;
		else
			regChainOffset = i * 0x1000;

		REG_WRITE(ah, AR_PHY_SWITCH_CHAIN_0 + regChainOffset,
			  pModal->antCtrlChain[i]);

		REG_WRITE(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset,
			  (REG_READ(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset) &
			   ~(AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF |
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF)) |
			  SM(pModal->iqCalICh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
			  SM(pModal->iqCalQCh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF));

		ath9k_hw_def_set_gain(ah, pModal, eep, txRxAttenLocal,
				      regChainOffset, i);
	}

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		if (IS_CHAN_2GHZ(chan)) {
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF2G1_CH0,
						  AR_AN_RF2G1_CH0_OB,
						  AR_AN_RF2G1_CH0_OB_S,
						  pModal->ob);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF2G1_CH0,
						  AR_AN_RF2G1_CH0_DB,
						  AR_AN_RF2G1_CH0_DB_S,
						  pModal->db);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF2G1_CH1,
						  AR_AN_RF2G1_CH1_OB,
						  AR_AN_RF2G1_CH1_OB_S,
						  pModal->ob_ch1);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF2G1_CH1,
						  AR_AN_RF2G1_CH1_DB,
						  AR_AN_RF2G1_CH1_DB_S,
						  pModal->db_ch1);
		} else {
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF5G1_CH0,
						  AR_AN_RF5G1_CH0_OB5,
						  AR_AN_RF5G1_CH0_OB5_S,
						  pModal->ob);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF5G1_CH0,
						  AR_AN_RF5G1_CH0_DB5,
						  AR_AN_RF5G1_CH0_DB5_S,
						  pModal->db);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF5G1_CH1,
						  AR_AN_RF5G1_CH1_OB5,
						  AR_AN_RF5G1_CH1_OB5_S,
						  pModal->ob_ch1);
			ath9k_hw_analog_shift_rmw(ah, AR_AN_RF5G1_CH1,
						  AR_AN_RF5G1_CH1_DB5,
						  AR_AN_RF5G1_CH1_DB5_S,
						  pModal->db_ch1);
		}
		ath9k_hw_analog_shift_rmw(ah, AR_AN_TOP2,
					  AR_AN_TOP2_XPABIAS_LVL,
					  AR_AN_TOP2_XPABIAS_LVL_S,
					  pModal->xpaBiasLvl);
		ath9k_hw_analog_shift_rmw(ah, AR_AN_TOP2,
					  AR_AN_TOP2_LOCALBIAS,
					  AR_AN_TOP2_LOCALBIAS_S,
					  !!(pModal->lna_ctl &
					     LNA_CTL_LOCAL_BIAS));
		REG_RMW_FIELD(ah, AR_PHY_XPA_CFG, AR_PHY_FORCE_XPA_CFG,
			      !!(pModal->lna_ctl & LNA_CTL_FORCE_XPA));
	}

	REG_RMW_FIELD(ah, AR_PHY_SETTLING, AR_PHY_SETTLING_SWITCH,
		      pModal->switchSettling);
	REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ, AR_PHY_DESIRED_SZ_ADC,
		      pModal->adcDesiredSize);

	if (!AR_SREV_9280_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ,
			      AR_PHY_DESIRED_SZ_PGA,
			      pModal->pgaDesiredSize);

	REG_WRITE(ah, AR_PHY_RF_CTL4,
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAA_OFF)
		  | SM(pModal->txEndToXpaOff,
		       AR_PHY_RF_CTL4_TX_END_XPAB_OFF)
		  | SM(pModal->txFrameToXpaOn,
		       AR_PHY_RF_CTL4_FRAME_XPAA_ON)
		  | SM(pModal->txFrameToXpaOn,
		       AR_PHY_RF_CTL4_FRAME_XPAB_ON));

	REG_RMW_FIELD(ah, AR_PHY_RF_CTL3, AR_PHY_TX_END_TO_A2_RX_ON,
		      pModal->txEndToRxOn);

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		REG_RMW_FIELD(ah, AR_PHY_CCA, AR9280_PHY_CCA_THRESH62,
			      pModal->thresh62);
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0,
			      AR_PHY_EXT_CCA0_THRESH62,
			      pModal->thresh62);
	} else {
		REG_RMW_FIELD(ah, AR_PHY_CCA, AR_PHY_CCA_THRESH62,
			      pModal->thresh62);
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA,
			      AR_PHY_EXT_CCA_THRESH62,
			      pModal->thresh62);
	}

	if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_2) {
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
			      AR_PHY_TX_END_DATA_START,
			      pModal->txFrameToDataStart);
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL2, AR_PHY_TX_END_PA_ON,
			      pModal->txFrameToPaOn);
	}

	if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_3) {
		if (IS_CHAN_HT40(chan))
			REG_RMW_FIELD(ah, AR_PHY_SETTLING,
				      AR_PHY_SETTLING_SWITCH,
				      pModal->swSettleHt40);
	}

	if (AR_SREV_9280_20_OR_LATER(ah) &&
	    AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_19)
		REG_RMW_FIELD(ah, AR_PHY_CCK_TX_CTRL,
			      AR_PHY_CCK_TX_CTRL_TX_DAC_SCALE_CCK,
			      pModal->miscBits);


	if (AR_SREV_9280_20(ah) && AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_20) {
		if (IS_CHAN_2GHZ(chan))
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE,
					eep->baseEepHeader.dacLpMode);
		else if (eep->baseEepHeader.dacHiPwrMode_5G)
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE, 0);
		else
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE,
				      eep->baseEepHeader.dacLpMode);

		udelay(100);

		REG_RMW_FIELD(ah, AR_PHY_FRAME_CTL, AR_PHY_FRAME_CTL_TX_CLIP,
			      pModal->miscBits >> 2);

		REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL9,
			      AR_PHY_TX_DESIRED_SCALE_CCK,
			      eep->baseEepHeader.desiredScaleCCK);
	}
}