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
typedef  size_t u8 ;
struct brcms_phy {int /*<<< orphan*/ * tx_power_offset; int /*<<< orphan*/ * adj_pwr_tbl_nphy; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_IS_SROM_REINTERPRET ; 
 size_t TXP_FIRST_CCK ; 
 size_t TXP_FIRST_MCS_20_CDD ; 
 size_t TXP_FIRST_MCS_20_SDM ; 
 size_t TXP_FIRST_MCS_20_STBC ; 
 size_t TXP_FIRST_MCS_40_CDD ; 
 size_t TXP_FIRST_MCS_40_SDM ; 
 size_t TXP_FIRST_MCS_40_SISO ; 
 size_t TXP_FIRST_MCS_40_STBC ; 
 size_t TXP_FIRST_OFDM ; 
 size_t TXP_FIRST_OFDM_40_SISO ; 
 size_t TXP_LAST_CCK ; 

__attribute__((used)) static void wlc_phy_txpwr_limit_to_tbl_nphy(struct brcms_phy *pi)
{
	u8 idx, idx2, i, delta_ind;

	for (idx = TXP_FIRST_CCK; idx <= TXP_LAST_CCK; idx++)
		pi->adj_pwr_tbl_nphy[idx] = pi->tx_power_offset[idx];

	for (i = 0; i < 4; i++) {
		idx2 = 0;

		delta_ind = 0;

		switch (i) {
		case 0:

			if (CHSPEC_IS40(pi->radio_chanspec)
			    && NPHY_IS_SROM_REINTERPRET) {
				idx = TXP_FIRST_MCS_40_SISO;
			} else {
				idx = (CHSPEC_IS40(pi->radio_chanspec)) ?
				      TXP_FIRST_OFDM_40_SISO : TXP_FIRST_OFDM;
				delta_ind = 1;
			}
			break;

		case 1:

			idx = (CHSPEC_IS40(pi->radio_chanspec)) ?
			      TXP_FIRST_MCS_40_CDD : TXP_FIRST_MCS_20_CDD;
			break;

		case 2:

			idx = (CHSPEC_IS40(pi->radio_chanspec)) ?
			      TXP_FIRST_MCS_40_STBC : TXP_FIRST_MCS_20_STBC;
			break;

		case 3:

			idx = (CHSPEC_IS40(pi->radio_chanspec)) ?
			      TXP_FIRST_MCS_40_SDM : TXP_FIRST_MCS_20_SDM;
			break;
		}

		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		idx = idx + delta_ind;
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];

		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];

		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];

		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx++];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		idx = idx + 1 - delta_ind;
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];

		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
		pi->adj_pwr_tbl_nphy[4 + 4 * (idx2++) + i] =
			pi->tx_power_offset[idx];
	}
}