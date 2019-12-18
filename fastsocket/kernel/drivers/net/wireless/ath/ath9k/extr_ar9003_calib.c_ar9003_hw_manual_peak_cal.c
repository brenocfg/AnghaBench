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
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC2G_DBDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC5G_DBDAC_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_CAL_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_ON_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_OUT ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_GAINSTAGES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_GAINSTAGES_LNA2G_GAIN_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_GAINSTAGES_LNA5G_GAIN_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_GAINSTAGES_LNAON_CALDC ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_GAINSTAGES_RX_OVERRIDE ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXTX2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXTX2_RXON ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXTX2_RXON_OVR ; 
 int BIT (int) ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9003_hw_manual_peak_cal(struct ath_hw *ah, u8 chain, bool is_2g)
{
	int offset[8], total = 0, test;
	int agc_out, i;

	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_RX_OVERRIDE, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_LNAON_CALDC, 0x0);
	if (is_2g)
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
			      AR_PHY_65NM_RXRF_GAINSTAGES_LNA2G_GAIN_OVR, 0x0);
	else
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
			      AR_PHY_65NM_RXRF_GAINSTAGES_LNA5G_GAIN_OVR, 0x0);

	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON_OVR, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON, 0x0);

	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_ON_OVR, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_CAL_OVR, 0x1);
	if (is_2g)
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC2G_DBDAC_OVR, 0x0);
	else
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC5G_DBDAC_OVR, 0x0);

	for (i = 6; i > 0; i--) {
		offset[i] = BIT(i - 1);
		test = total + offset[i];

		if (is_2g)
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      test);
		else
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      test);
		udelay(100);
		agc_out = REG_READ_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
					 AR_PHY_65NM_RXRF_AGC_AGC_OUT);
		offset[i] = (agc_out) ? 0 : 1;
		total += (offset[i] << (i - 1));
	}

	if (is_2g)
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR, total);
	else
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR, total);

	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_RX_OVERRIDE, 0);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON_OVR, 0);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_CAL_OVR, 0);
}