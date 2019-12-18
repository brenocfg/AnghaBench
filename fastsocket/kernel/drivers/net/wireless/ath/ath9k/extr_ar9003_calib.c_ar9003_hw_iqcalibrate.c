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
typedef  unsigned int u_int32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int* totalPowerMeasI; int* totalPowerMeasQ; int* totalIqCorrMeas; } ;
struct ath_common {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
#define  AR_PHY_RX_IQCAL_CORR_B0 130 
#define  AR_PHY_RX_IQCAL_CORR_B1 129 
#define  AR_PHY_RX_IQCAL_CORR_B2 128 
 int AR_PHY_RX_IQCAL_CORR_IQCORR_ENABLE ; 
 int AR_PHY_RX_IQCAL_CORR_IQCORR_Q_I_COFF ; 
 int AR_PHY_RX_IQCAL_CORR_IQCORR_Q_Q_COFF ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int REG_READ (struct ath_hw*,unsigned int const) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,unsigned int const,int,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,unsigned int const,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,unsigned int const,...) ; 

__attribute__((used)) static void ar9003_hw_iqcalibrate(struct ath_hw *ah, u8 numChains)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 powerMeasQ, powerMeasI, iqCorrMeas;
	u32 qCoffDenom, iCoffDenom;
	int32_t qCoff, iCoff;
	int iqCorrNeg, i;
	static const u_int32_t offset_array[3] = {
		AR_PHY_RX_IQCAL_CORR_B0,
		AR_PHY_RX_IQCAL_CORR_B1,
		AR_PHY_RX_IQCAL_CORR_B2,
	};

	for (i = 0; i < numChains; i++) {
		powerMeasI = ah->totalPowerMeasI[i];
		powerMeasQ = ah->totalPowerMeasQ[i];
		iqCorrMeas = ah->totalIqCorrMeas[i];

		ath_dbg(common, CALIBRATE,
			"Starting IQ Cal and Correction for Chain %d\n", i);

		ath_dbg(common, CALIBRATE,
			"Original: Chn %d iq_corr_meas = 0x%08x\n",
			i, ah->totalIqCorrMeas[i]);

		iqCorrNeg = 0;

		if (iqCorrMeas > 0x80000000) {
			iqCorrMeas = (0xffffffff - iqCorrMeas) + 1;
			iqCorrNeg = 1;
		}

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_i = 0x%08x\n",
			i, powerMeasI);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_q = 0x%08x\n",
			i, powerMeasQ);
		ath_dbg(common, CALIBRATE, "iqCorrNeg is 0x%08x\n", iqCorrNeg);

		iCoffDenom = (powerMeasI / 2 + powerMeasQ / 2) / 256;
		qCoffDenom = powerMeasQ / 64;

		if ((iCoffDenom != 0) && (qCoffDenom != 0)) {
			iCoff = iqCorrMeas / iCoffDenom;
			qCoff = powerMeasI / qCoffDenom - 64;
			ath_dbg(common, CALIBRATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CALIBRATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			/* Force bounds on iCoff */
			if (iCoff >= 63)
				iCoff = 63;
			else if (iCoff <= -63)
				iCoff = -63;

			/* Negate iCoff if iqCorrNeg == 0 */
			if (iqCorrNeg == 0x0)
				iCoff = -iCoff;

			/* Force bounds on qCoff */
			if (qCoff >= 63)
				qCoff = 63;
			else if (qCoff <= -63)
				qCoff = -63;

			iCoff = iCoff & 0x7f;
			qCoff = qCoff & 0x7f;

			ath_dbg(common, CALIBRATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) before update = 0x%x\n",
				offset_array[i],
				REG_READ(ah, offset_array[i]));

			if (AR_SREV_9565(ah) &&
			    (iCoff == 63 || qCoff == 63 ||
			     iCoff == -63 || qCoff == -63))
				return;

			REG_RMW_FIELD(ah, offset_array[i],
				      AR_PHY_RX_IQCAL_CORR_IQCORR_Q_I_COFF,
				      iCoff);
			REG_RMW_FIELD(ah, offset_array[i],
				      AR_PHY_RX_IQCAL_CORR_IQCORR_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) QI COFF (bitfields 0x%08x) after update = 0x%x\n",
				offset_array[i],
				AR_PHY_RX_IQCAL_CORR_IQCORR_Q_I_COFF,
				REG_READ(ah, offset_array[i]));
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) QQ COFF (bitfields 0x%08x) after update = 0x%x\n",
				offset_array[i],
				AR_PHY_RX_IQCAL_CORR_IQCORR_Q_Q_COFF,
				REG_READ(ah, offset_array[i]));

			ath_dbg(common, CALIBRATE,
				"IQ Cal and Correction done for Chain %d\n", i);
		}
	}

	REG_SET_BIT(ah, AR_PHY_RX_IQCAL_CORR_B0,
		    AR_PHY_RX_IQCAL_CORR_IQCORR_ENABLE);
	ath_dbg(common, CALIBRATE,
		"IQ Cal and Correction (offset 0x%04x) enabled (bit position 0x%08x). New Value 0x%08x\n",
		(unsigned) (AR_PHY_RX_IQCAL_CORR_B0),
		AR_PHY_RX_IQCAL_CORR_IQCORR_ENABLE,
		REG_READ(ah, AR_PHY_RX_IQCAL_CORR_B0));
}