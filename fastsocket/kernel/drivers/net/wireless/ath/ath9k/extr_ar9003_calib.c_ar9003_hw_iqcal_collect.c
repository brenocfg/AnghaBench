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
struct ath_hw {int txchainmask; int /*<<< orphan*/ * totalIqCorrMeas; int /*<<< orphan*/ * totalPowerMeasQ; int /*<<< orphan*/ * totalPowerMeasI; int /*<<< orphan*/  cal_samples; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int AR5416_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_CAL_MEAS_0 (int) ; 
 int /*<<< orphan*/  AR_PHY_CAL_MEAS_1 (int) ; 
 int /*<<< orphan*/  AR_PHY_CAL_MEAS_2 (int) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 scalar_t__ REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_iqcal_collect(struct ath_hw *ah)
{
	int i;

	/* Accumulate IQ cal measures for active chains */
	for (i = 0; i < AR5416_MAX_CHAINS; i++) {
		if (ah->txchainmask & BIT(i)) {
			ah->totalPowerMeasI[i] +=
				REG_READ(ah, AR_PHY_CAL_MEAS_0(i));
			ah->totalPowerMeasQ[i] +=
				REG_READ(ah, AR_PHY_CAL_MEAS_1(i));
			ah->totalIqCorrMeas[i] +=
				(int32_t) REG_READ(ah, AR_PHY_CAL_MEAS_2(i));
			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"%d: Chn %d pmi=0x%08x;pmq=0x%08x;iqcm=0x%08x;\n",
				ah->cal_samples, i, ah->totalPowerMeasI[i],
				ah->totalPowerMeasQ[i],
				ah->totalIqCorrMeas[i]);
		}
	}
}