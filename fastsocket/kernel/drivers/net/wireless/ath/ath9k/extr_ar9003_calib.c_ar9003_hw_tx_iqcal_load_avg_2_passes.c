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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tx_corr_coeff ;
struct coeff {int** mag_coeff; int** phs_coeff; int* iqc_coeff; } ;
struct ath_hw {int txchainmask; struct ath9k_hw_cal_data* caldata; } ;
struct ath9k_hw_cal_data {int** tx_corr_coeff; int* num_measures; int done_txiqcal_once; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_CALIBRATED_GAINS_0 ; 
 int /*<<< orphan*/  AR_PHY_RX_IQCAL_CORR_B0 ; 
 int /*<<< orphan*/  AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_3 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B0 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B1 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B2 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_STATUS_B0 ; 
 int /*<<< orphan*/  AR_SREV_9485 (struct ath_hw*) ; 
 int /*<<< orphan*/  MAX_MAG_DELTA ; 
 int MAX_MEASUREMENT ; 
 int /*<<< orphan*/  MAX_PHS_DELTA ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_hw_detect_outlier (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_hw_tx_iqcal_load_avg_2_passes(struct ath_hw *ah,
						 struct coeff *coeff,
						 bool is_reusable)
{
	int i, im, nmeasurement;
	u32 tx_corr_coeff[MAX_MEASUREMENT][AR9300_MAX_CHAINS];
	struct ath9k_hw_cal_data *caldata = ah->caldata;

	memset(tx_corr_coeff, 0, sizeof(tx_corr_coeff));
	for (i = 0; i < MAX_MEASUREMENT / 2; i++) {
		tx_corr_coeff[i * 2][0] = tx_corr_coeff[(i * 2) + 1][0] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B0(i);
		if (!AR_SREV_9485(ah)) {
			tx_corr_coeff[i * 2][1] =
			tx_corr_coeff[(i * 2) + 1][1] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B1(i);

			tx_corr_coeff[i * 2][2] =
			tx_corr_coeff[(i * 2) + 1][2] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B2(i);
		}
	}

	/* Load the average of 2 passes */
	for (i = 0; i < AR9300_MAX_CHAINS; i++) {
		if (!(ah->txchainmask & (1 << i)))
			continue;
		nmeasurement = REG_READ_FIELD(ah,
				AR_PHY_TX_IQCAL_STATUS_B0,
				AR_PHY_CALIBRATED_GAINS_0);

		if (nmeasurement > MAX_MEASUREMENT)
			nmeasurement = MAX_MEASUREMENT;

		/* detect outlier only if nmeasurement > 1 */
		if (nmeasurement > 1) {
			/* Detect magnitude outlier */
			ar9003_hw_detect_outlier(coeff->mag_coeff[i],
					nmeasurement, MAX_MAG_DELTA);

			/* Detect phase outlier */
			ar9003_hw_detect_outlier(coeff->phs_coeff[i],
					nmeasurement, MAX_PHS_DELTA);
		}

		for (im = 0; im < nmeasurement; im++) {

			coeff->iqc_coeff[0] = (coeff->mag_coeff[i][im] & 0x7f) |
				((coeff->phs_coeff[i][im] & 0x7f) << 7);

			if ((im % 2) == 0)
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE,
					coeff->iqc_coeff[0]);
			else
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE,
					coeff->iqc_coeff[0]);

			if (caldata)
				caldata->tx_corr_coeff[im][i] =
					coeff->iqc_coeff[0];
		}
		if (caldata)
			caldata->num_measures[i] = nmeasurement;
	}

	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_3,
		      AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_RX_IQCAL_CORR_B0,
		      AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN, 0x1);

	if (caldata)
		caldata->done_txiqcal_once = is_reusable;

	return;
}