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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 size_t ALL_TARGET_HT20_0_8_16 ; 
 size_t ALL_TARGET_HT20_12 ; 
 size_t ALL_TARGET_HT20_13 ; 
 size_t ALL_TARGET_HT20_14 ; 
 size_t ALL_TARGET_HT20_15 ; 
 size_t ALL_TARGET_HT20_1_3_9_11_17_19 ; 
 size_t ALL_TARGET_HT20_20 ; 
 size_t ALL_TARGET_HT20_21 ; 
 size_t ALL_TARGET_HT20_22 ; 
 size_t ALL_TARGET_HT20_23 ; 
 size_t ALL_TARGET_HT20_4 ; 
 size_t ALL_TARGET_HT20_5 ; 
 size_t ALL_TARGET_HT20_6 ; 
 size_t ALL_TARGET_HT20_7 ; 
 size_t ALL_TARGET_HT40_0_8_16 ; 
 size_t ALL_TARGET_HT40_12 ; 
 size_t ALL_TARGET_HT40_13 ; 
 size_t ALL_TARGET_HT40_14 ; 
 size_t ALL_TARGET_HT40_15 ; 
 size_t ALL_TARGET_HT40_1_3_9_11_17_19 ; 
 size_t ALL_TARGET_HT40_20 ; 
 size_t ALL_TARGET_HT40_21 ; 
 size_t ALL_TARGET_HT40_22 ; 
 size_t ALL_TARGET_HT40_23 ; 
 size_t ALL_TARGET_HT40_4 ; 
 size_t ALL_TARGET_HT40_5 ; 
 size_t ALL_TARGET_HT40_6 ; 
 size_t ALL_TARGET_HT40_7 ; 
 size_t ALL_TARGET_LEGACY_11L ; 
 size_t ALL_TARGET_LEGACY_11S ; 
 size_t ALL_TARGET_LEGACY_1L_5L ; 
 size_t ALL_TARGET_LEGACY_36 ; 
 size_t ALL_TARGET_LEGACY_48 ; 
 size_t ALL_TARGET_LEGACY_54 ; 
 size_t ALL_TARGET_LEGACY_5S ; 
 size_t ALL_TARGET_LEGACY_6_24 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN ; 
 int POW_SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar9003_hw_tx_power_regwrite(struct ath_hw *ah, u8 * pPwrArray)
{
#define POW_SM(_r, _s)     (((_r) & 0x3f) << (_s))
	/* make sure forced gain is not set */
	REG_WRITE(ah, AR_PHY_TX_FORCED_GAIN, 0);

	/* Write the OFDM power per rate set */

	/* 6 (LSB), 9, 12, 18 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(0),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 0));

	/* 24 (LSB), 36, 48, 54 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(1),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_54], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_48], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_36], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 0));

	/* Write the CCK power per rate set */

	/* 1L (LSB), reserved, 2L, 2S (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(2),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 16) |
		  /* POW_SM(txPowerTimes2,  8) | this is reserved for AR9003 */
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 0));

	/* 5.5L (LSB), 5.5S, 11L, 11S (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(3),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_11S], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_11L], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_5S], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 0)
	    );

        /* Write the power for duplicated frames - HT40 */

        /* dup40_cck (LSB), dup40_ofdm, ext20_cck, ext20_ofdm (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(8),
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_6_24],  8) |
		  POW_SM(pPwrArray[ALL_TARGET_LEGACY_1L_5L],  0)
	    );

	/* Write the HT20 power per rate set */

	/* 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(4),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_5], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_4], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_1_3_9_11_17_19], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_0_8_16], 0)
	    );

	/* 6 (LSB), 7, 12, 13 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(5),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_13], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_12], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_7], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_6], 0)
	    );

	/* 14 (LSB), 15, 20, 21 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(9),
		  POW_SM(pPwrArray[ALL_TARGET_HT20_21], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_20], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_15], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_14], 0)
	    );

	/* Mixed HT20 and HT40 rates */

	/* HT20 22 (LSB), HT20 23, HT40 22, HT40 23 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(10),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_23], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_22], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_23], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT20_22], 0)
	    );

	/*
	 * Write the HT40 power per rate set
	 * correct PAR difference between HT40 and HT20/LEGACY
	 * 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB)
	 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(6),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_5], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_4], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_1_3_9_11_17_19], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_0_8_16], 0)
	    );

	/* 6 (LSB), 7, 12, 13 (MSB) */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(7),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_13], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_12], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_7], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_6], 0)
	    );

	/* 14 (LSB), 15, 20, 21 */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE(11),
		  POW_SM(pPwrArray[ALL_TARGET_HT40_21], 24) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_20], 16) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_15], 8) |
		  POW_SM(pPwrArray[ALL_TARGET_HT40_14], 0)
	    );

	return 0;
#undef POW_SM
}