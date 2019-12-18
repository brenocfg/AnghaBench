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
typedef  int u32 ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath5k_hw {int ah_cal_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_BEACON_5210 ; 
 int AR5K_BEACON_ENABLE ; 
 int AR5K_CALIBRATION_FULL ; 
 int /*<<< orphan*/  AR5K_DIAG_SW_5210 ; 
 int AR5K_DIAG_SW_DIS_RX_5210 ; 
 int AR5K_DIAG_SW_DIS_TX_5210 ; 
 int /*<<< orphan*/  AR5K_PHY_ACT ; 
 int AR5K_PHY_ACT_ENABLE ; 
 int /*<<< orphan*/  AR5K_PHY_ADCSAT ; 
 int AR5K_PHY_ADCSAT_ICNT ; 
 int AR5K_PHY_ADCSAT_THR ; 
 int /*<<< orphan*/  AR5K_PHY_AGC ; 
 int /*<<< orphan*/  AR5K_PHY_AGCCOARSE ; 
 int AR5K_PHY_AGCCOARSE_HI ; 
 int AR5K_PHY_AGCCOARSE_LO ; 
 int /*<<< orphan*/  AR5K_PHY_AGCCTL ; 
 int AR5K_PHY_AGCCTL_CAL ; 
 int AR5K_PHY_AGC_DISABLE ; 
 int /*<<< orphan*/  AR5K_PHY_RFSTG ; 
 int AR5K_PHY_RFSTG_DISABLE ; 
 int /*<<< orphan*/  AR5K_PHY_SIG ; 
 int AR5K_PHY_SIG_FIRPWR ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int AR5K_REG_SM (int,int) ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int /*<<< orphan*/ ) ; 
 int ath5k_hw_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int ath5k_hw_register_timeout (struct ath5k_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ath5k_hw_rf5110_calibrate(struct ath5k_hw *ah,
		struct ieee80211_channel *channel)
{
	u32 phy_sig, phy_agc, phy_sat, beacon;
	int ret;

	if (!(ah->ah_cal_mask & AR5K_CALIBRATION_FULL))
		return 0;

	/*
	 * Disable beacons and RX/TX queues, wait
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW_5210,
		AR5K_DIAG_SW_DIS_TX_5210 | AR5K_DIAG_SW_DIS_RX_5210);
	beacon = ath5k_hw_reg_read(ah, AR5K_BEACON_5210);
	ath5k_hw_reg_write(ah, beacon & ~AR5K_BEACON_ENABLE, AR5K_BEACON_5210);

	usleep_range(2000, 2500);

	/*
	 * Set the channel (with AGC turned off)
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);
	udelay(10);
	ret = ath5k_hw_channel(ah, channel);

	/*
	 * Activate PHY and wait
	 */
	ath5k_hw_reg_write(ah, AR5K_PHY_ACT_ENABLE, AR5K_PHY_ACT);
	usleep_range(1000, 1500);

	AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);

	if (ret)
		return ret;

	/*
	 * Calibrate the radio chip
	 */

	/* Remember normal state */
	phy_sig = ath5k_hw_reg_read(ah, AR5K_PHY_SIG);
	phy_agc = ath5k_hw_reg_read(ah, AR5K_PHY_AGCCOARSE);
	phy_sat = ath5k_hw_reg_read(ah, AR5K_PHY_ADCSAT);

	/* Update radio registers */
	ath5k_hw_reg_write(ah, (phy_sig & ~(AR5K_PHY_SIG_FIRPWR)) |
		AR5K_REG_SM(-1, AR5K_PHY_SIG_FIRPWR), AR5K_PHY_SIG);

	ath5k_hw_reg_write(ah, (phy_agc & ~(AR5K_PHY_AGCCOARSE_HI |
			AR5K_PHY_AGCCOARSE_LO)) |
		AR5K_REG_SM(-1, AR5K_PHY_AGCCOARSE_HI) |
		AR5K_REG_SM(-127, AR5K_PHY_AGCCOARSE_LO), AR5K_PHY_AGCCOARSE);

	ath5k_hw_reg_write(ah, (phy_sat & ~(AR5K_PHY_ADCSAT_ICNT |
			AR5K_PHY_ADCSAT_THR)) |
		AR5K_REG_SM(2, AR5K_PHY_ADCSAT_ICNT) |
		AR5K_REG_SM(12, AR5K_PHY_ADCSAT_THR), AR5K_PHY_ADCSAT);

	udelay(20);

	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);
	udelay(10);
	ath5k_hw_reg_write(ah, AR5K_PHY_RFSTG_DISABLE, AR5K_PHY_RFSTG);
	AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);

	usleep_range(1000, 1500);

	/*
	 * Enable calibration and wait until completion
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_CAL);

	ret = ath5k_hw_register_timeout(ah, AR5K_PHY_AGCCTL,
			AR5K_PHY_AGCCTL_CAL, 0, false);

	/* Reset to normal state */
	ath5k_hw_reg_write(ah, phy_sig, AR5K_PHY_SIG);
	ath5k_hw_reg_write(ah, phy_agc, AR5K_PHY_AGCCOARSE);
	ath5k_hw_reg_write(ah, phy_sat, AR5K_PHY_ADCSAT);

	if (ret) {
		ATH5K_ERR(ah, "calibration timeout (%uMHz)\n",
				channel->center_freq);
		return ret;
	}

	/*
	 * Re-enable RX/TX and beacons
	 */
	AR5K_REG_DISABLE_BITS(ah, AR5K_DIAG_SW_5210,
		AR5K_DIAG_SW_DIS_TX_5210 | AR5K_DIAG_SW_DIS_RX_5210);
	ath5k_hw_reg_write(ah, beacon, AR5K_BEACON_5210);

	return 0;
}