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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ath_hw {size_t* totalAdcDcOffsetIOddPhase; size_t* totalAdcDcOffsetIEvenPhase; int* totalAdcDcOffsetQOddPhase; int* totalAdcDcOffsetQEvenPhase; TYPE_1__* cal_list_curr; } ;
struct ath_common {int dummy; } ;
struct ath9k_percal_data {int calCountMax; int calNumSamples; } ;
typedef  int int32_t ;
struct TYPE_2__ {struct ath9k_percal_data* calData; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_NEW_ADC_DC_GAIN_CORR (size_t) ; 
 size_t AR_PHY_NEW_ADC_DC_OFFSET_CORR_ENABLE ; 
 int /*<<< orphan*/  CALIBRATE ; 
 size_t REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,size_t) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,...) ; 

__attribute__((used)) static void ar9002_hw_adc_dccal_calibrate(struct ath_hw *ah, u8 numChains)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, val, i;
	int32_t qOddMeasOffset, qEvenMeasOffset, qDcMismatch, iDcMismatch;
	const struct ath9k_percal_data *calData =
		ah->cal_list_curr->calData;
	u32 numSamples =
		(1 << (calData->calCountMax + 5)) * calData->calNumSamples;

	for (i = 0; i < numChains; i++) {
		iOddMeasOffset = ah->totalAdcDcOffsetIOddPhase[i];
		iEvenMeasOffset = ah->totalAdcDcOffsetIEvenPhase[i];
		qOddMeasOffset = ah->totalAdcDcOffsetQOddPhase[i];
		qEvenMeasOffset = ah->totalAdcDcOffsetQEvenPhase[i];

		ath_dbg(common, CALIBRATE,
			"Starting ADC DC Offset Cal for Chain %d\n", i);

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_i = %d\n",
			i, iOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_i = %d\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_q = %d\n",
			i, qOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_q = %d\n",
			i, qEvenMeasOffset);

		iDcMismatch = (((iEvenMeasOffset - iOddMeasOffset) * 2) /
			       numSamples) & 0x1ff;
		qDcMismatch = (((qOddMeasOffset - qEvenMeasOffset) * 2) /
			       numSamples) & 0x1ff;

		ath_dbg(common, CALIBRATE,
			"Chn %d dc_offset_mismatch_i = 0x%08x\n",
			i, iDcMismatch);
		ath_dbg(common, CALIBRATE,
			"Chn %d dc_offset_mismatch_q = 0x%08x\n",
			i, qDcMismatch);

		val = REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
		val &= 0xc0000fff;
		val |= (qDcMismatch << 12) | (iDcMismatch << 21);
		REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val);

		ath_dbg(common, CALIBRATE,
			"ADC DC Offset Cal done for Chain %d\n", i);
	}

	REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
		  REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0)) |
		  AR_PHY_NEW_ADC_DC_OFFSET_CORR_ENABLE);
}