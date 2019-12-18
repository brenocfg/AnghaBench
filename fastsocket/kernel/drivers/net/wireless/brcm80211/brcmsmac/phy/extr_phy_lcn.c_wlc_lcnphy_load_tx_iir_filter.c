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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int LCNPHY_NUM_DIG_FILT_COEFFS ; 
 int LCNPHY_NUM_TX_DIG_FILTERS_CCK ; 
 int LCNPHY_NUM_TX_DIG_FILTERS_OFDM ; 
 scalar_t__** LCNPHY_txdigfiltcoeffs_cck ; 
 scalar_t__** LCNPHY_txdigfiltcoeffs_ofdm ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,scalar_t__) ; 

__attribute__((used)) static int
wlc_lcnphy_load_tx_iir_filter(struct brcms_phy *pi, bool is_ofdm, s16 filt_type)
{
	s16 filt_index = -1;
	int j;

	u16 addr[] = {
		0x910,
		0x91e,
		0x91f,
		0x924,
		0x925,
		0x926,
		0x920,
		0x921,
		0x927,
		0x928,
		0x929,
		0x922,
		0x923,
		0x930,
		0x931,
		0x932
	};

	u16 addr_ofdm[] = {
		0x90f,
		0x900,
		0x901,
		0x906,
		0x907,
		0x908,
		0x902,
		0x903,
		0x909,
		0x90a,
		0x90b,
		0x904,
		0x905,
		0x90c,
		0x90d,
		0x90e
	};

	if (!is_ofdm) {
		for (j = 0; j < LCNPHY_NUM_TX_DIG_FILTERS_CCK; j++) {
			if (filt_type == LCNPHY_txdigfiltcoeffs_cck[j][0]) {
				filt_index = (s16) j;
				break;
			}
		}

		if (filt_index != -1) {
			for (j = 0; j < LCNPHY_NUM_DIG_FILT_COEFFS; j++)
				write_phy_reg(pi, addr[j],
					      LCNPHY_txdigfiltcoeffs_cck
					      [filt_index][j + 1]);
		}
	} else {
		for (j = 0; j < LCNPHY_NUM_TX_DIG_FILTERS_OFDM; j++) {
			if (filt_type == LCNPHY_txdigfiltcoeffs_ofdm[j][0]) {
				filt_index = (s16) j;
				break;
			}
		}

		if (filt_index != -1) {
			for (j = 0; j < LCNPHY_NUM_DIG_FILT_COEFFS; j++)
				write_phy_reg(pi, addr_ofdm[j],
					      LCNPHY_txdigfiltcoeffs_ofdm
					      [filt_index][j + 1]);
		}
	}

	return (filt_index != -1) ? 0 : -1;
}