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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct txpwr_limits {void** cck; void** ofdm; void** mcs_20_siso; void** mcs_20_cdd; void** ofdm_cdd; void** mcs_40_siso; void** ofdm_40_siso; void** mcs_40_cdd; void** ofdm_40_cdd; void** mcs_20_stbc; void** mcs_40_stbc; void** mcs_20_mimo; void** mcs_40_mimo; void* mcs32; } ;
struct brcms_phy {void** txpwr_limit; } ;

/* Variables and functions */
 int BRCMS_NUM_RATES_MCS_1_STREAM ; 
 int BRCMS_NUM_RATES_MCS_2_STREAM ; 
 int BRCMS_NUM_RATES_OFDM ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int WL_TX_POWER_CCK_FIRST ; 
 int WL_TX_POWER_CCK_NUM ; 
 int WL_TX_POWER_MCS20_CDD_FIRST ; 
 int WL_TX_POWER_MCS20_SDM_FIRST ; 
 int WL_TX_POWER_MCS20_SISO_FIRST ; 
 int WL_TX_POWER_MCS20_STBC_FIRST ; 
 size_t WL_TX_POWER_MCS40_CDD_FIRST ; 
 int WL_TX_POWER_MCS40_SDM_FIRST ; 
 int WL_TX_POWER_MCS40_SISO_FIRST ; 
 int WL_TX_POWER_MCS40_STBC_FIRST ; 
 size_t WL_TX_POWER_MCS_32 ; 
 int WL_TX_POWER_OFDM20_CDD_FIRST ; 
 int WL_TX_POWER_OFDM40_CDD_FIRST ; 
 int WL_TX_POWER_OFDM40_SISO_FIRST ; 
 int WL_TX_POWER_OFDM_FIRST ; 
 int WL_TX_POWER_OFDM_NUM ; 
 void* min (void*,void*) ; 
 int /*<<< orphan*/  wlc_phy_mcs_to_ofdm_powers_nphy (void**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wlc_phy_ofdm_to_mcs_powers_nphy (void**,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
wlc_phy_txpower_reg_limit_calc(struct brcms_phy *pi, struct txpwr_limits *txpwr,
			       u16 chanspec)
{
	u8 tmp_txpwr_limit[2 * BRCMS_NUM_RATES_OFDM];
	u8 *txpwr_ptr1 = NULL, *txpwr_ptr2 = NULL;
	int rate_start_index = 0, rate1, rate2, k;

	for (rate1 = WL_TX_POWER_CCK_FIRST, rate2 = 0;
	     rate2 < WL_TX_POWER_CCK_NUM; rate1++, rate2++)
		pi->txpwr_limit[rate1] = txpwr->cck[rate2];

	for (rate1 = WL_TX_POWER_OFDM_FIRST, rate2 = 0;
	     rate2 < WL_TX_POWER_OFDM_NUM; rate1++, rate2++)
		pi->txpwr_limit[rate1] = txpwr->ofdm[rate2];

	if (ISNPHY(pi)) {

		for (k = 0; k < 4; k++) {
			switch (k) {
			case 0:

				txpwr_ptr1 = txpwr->mcs_20_siso;
				txpwr_ptr2 = txpwr->ofdm;
				rate_start_index = WL_TX_POWER_OFDM_FIRST;
				break;
			case 1:

				txpwr_ptr1 = txpwr->mcs_20_cdd;
				txpwr_ptr2 = txpwr->ofdm_cdd;
				rate_start_index = WL_TX_POWER_OFDM20_CDD_FIRST;
				break;
			case 2:

				txpwr_ptr1 = txpwr->mcs_40_siso;
				txpwr_ptr2 = txpwr->ofdm_40_siso;
				rate_start_index =
					WL_TX_POWER_OFDM40_SISO_FIRST;
				break;
			case 3:

				txpwr_ptr1 = txpwr->mcs_40_cdd;
				txpwr_ptr2 = txpwr->ofdm_40_cdd;
				rate_start_index = WL_TX_POWER_OFDM40_CDD_FIRST;
				break;
			}

			for (rate2 = 0; rate2 < BRCMS_NUM_RATES_OFDM;
			     rate2++) {
				tmp_txpwr_limit[rate2] = 0;
				tmp_txpwr_limit[BRCMS_NUM_RATES_OFDM + rate2] =
					txpwr_ptr1[rate2];
			}
			wlc_phy_mcs_to_ofdm_powers_nphy(
				tmp_txpwr_limit, 0,
				BRCMS_NUM_RATES_OFDM -
				1, BRCMS_NUM_RATES_OFDM);
			for (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_OFDM; rate1++, rate2++)
				pi->txpwr_limit[rate1] =
					min(txpwr_ptr2[rate2],
					    tmp_txpwr_limit[rate2]);
		}

		for (k = 0; k < 4; k++) {
			switch (k) {
			case 0:

				txpwr_ptr1 = txpwr->ofdm;
				txpwr_ptr2 = txpwr->mcs_20_siso;
				rate_start_index = WL_TX_POWER_MCS20_SISO_FIRST;
				break;
			case 1:

				txpwr_ptr1 = txpwr->ofdm_cdd;
				txpwr_ptr2 = txpwr->mcs_20_cdd;
				rate_start_index = WL_TX_POWER_MCS20_CDD_FIRST;
				break;
			case 2:

				txpwr_ptr1 = txpwr->ofdm_40_siso;
				txpwr_ptr2 = txpwr->mcs_40_siso;
				rate_start_index = WL_TX_POWER_MCS40_SISO_FIRST;
				break;
			case 3:

				txpwr_ptr1 = txpwr->ofdm_40_cdd;
				txpwr_ptr2 = txpwr->mcs_40_cdd;
				rate_start_index = WL_TX_POWER_MCS40_CDD_FIRST;
				break;
			}
			for (rate2 = 0; rate2 < BRCMS_NUM_RATES_OFDM;
			     rate2++) {
				tmp_txpwr_limit[rate2] = 0;
				tmp_txpwr_limit[BRCMS_NUM_RATES_OFDM + rate2] =
					txpwr_ptr1[rate2];
			}
			wlc_phy_ofdm_to_mcs_powers_nphy(
				tmp_txpwr_limit, 0,
				BRCMS_NUM_RATES_OFDM -
				1, BRCMS_NUM_RATES_OFDM);
			for (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_1_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] =
					min(txpwr_ptr2[rate2],
					    tmp_txpwr_limit[rate2]);
		}

		for (k = 0; k < 2; k++) {
			switch (k) {
			case 0:

				rate_start_index = WL_TX_POWER_MCS20_STBC_FIRST;
				txpwr_ptr1 = txpwr->mcs_20_stbc;
				break;
			case 1:

				rate_start_index = WL_TX_POWER_MCS40_STBC_FIRST;
				txpwr_ptr1 = txpwr->mcs_40_stbc;
				break;
			}
			for (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_1_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] = txpwr_ptr1[rate2];
		}

		for (k = 0; k < 2; k++) {
			switch (k) {
			case 0:

				rate_start_index = WL_TX_POWER_MCS20_SDM_FIRST;
				txpwr_ptr1 = txpwr->mcs_20_mimo;
				break;
			case 1:

				rate_start_index = WL_TX_POWER_MCS40_SDM_FIRST;
				txpwr_ptr1 = txpwr->mcs_40_mimo;
				break;
			}
			for (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_2_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] = txpwr_ptr1[rate2];
		}

		pi->txpwr_limit[WL_TX_POWER_MCS_32] = txpwr->mcs32;

		pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST] =
			min(pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST],
			    pi->txpwr_limit[WL_TX_POWER_MCS_32]);
		pi->txpwr_limit[WL_TX_POWER_MCS_32] =
			pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST];
	}
}