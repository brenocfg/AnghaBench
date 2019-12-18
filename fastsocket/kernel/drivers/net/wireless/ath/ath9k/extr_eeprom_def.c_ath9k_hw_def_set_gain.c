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
typedef  int /*<<< orphan*/  u8 ;
struct modal_eep_header {int /*<<< orphan*/ * rxTxMarginCh; int /*<<< orphan*/ * bswAtten; int /*<<< orphan*/ * bswMargin; int /*<<< orphan*/ * xatten2Db; int /*<<< orphan*/ * xatten2Margin; int /*<<< orphan*/ * txRxAttenCh; } ;
struct ath_hw {int dummy; } ;
struct ar5416_eeprom_def {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR5416_EEP_MINOR_VER_3 ; 
 scalar_t__ AR5416_VER_MASK ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_ATTEN ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_MARGIN ; 
 scalar_t__ AR_PHY_GAIN_2GHZ ; 
 int AR_PHY_GAIN_2GHZ_BSW_ATTEN ; 
 int AR_PHY_GAIN_2GHZ_BSW_MARGIN ; 
 int AR_PHY_GAIN_2GHZ_RXTX_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN ; 
 scalar_t__ AR_PHY_RXGAIN ; 
 int AR_PHY_RXGAIN_TXRX_ATTEN ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_hw_def_set_gain(struct ath_hw *ah,
				  struct modal_eep_header *pModal,
				  struct ar5416_eeprom_def *eep,
				  u8 txRxAttenLocal, int regChainOffset, int i)
{
	if (AR5416_VER_MASK >= AR5416_EEP_MINOR_VER_3) {
		txRxAttenLocal = pModal->txRxAttenCh[i];

		if (AR_SREV_9280_20_OR_LATER(ah)) {
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[i]);
		} else {
			REG_WRITE(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			  (REG_READ(ah, AR_PHY_GAIN_2GHZ + regChainOffset) &
			   ~AR_PHY_GAIN_2GHZ_BSW_MARGIN)
			  | SM(pModal-> bswMargin[i],
			       AR_PHY_GAIN_2GHZ_BSW_MARGIN));
			REG_WRITE(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			  (REG_READ(ah, AR_PHY_GAIN_2GHZ + regChainOffset) &
			   ~AR_PHY_GAIN_2GHZ_BSW_ATTEN)
			  | SM(pModal->bswAtten[i],
			       AR_PHY_GAIN_2GHZ_BSW_ATTEN));
		}
	}

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[i]);
	} else {
		REG_WRITE(ah,
			  AR_PHY_RXGAIN + regChainOffset,
			  (REG_READ(ah, AR_PHY_RXGAIN + regChainOffset) &
			   ~AR_PHY_RXGAIN_TXRX_ATTEN)
			  | SM(txRxAttenLocal, AR_PHY_RXGAIN_TXRX_ATTEN));
		REG_WRITE(ah,
			  AR_PHY_GAIN_2GHZ + regChainOffset,
			  (REG_READ(ah, AR_PHY_GAIN_2GHZ + regChainOffset) &
			   ~AR_PHY_GAIN_2GHZ_RXTX_MARGIN) |
			  SM(pModal->rxTxMarginCh[i], AR_PHY_GAIN_2GHZ_RXTX_MARGIN));
	}
}