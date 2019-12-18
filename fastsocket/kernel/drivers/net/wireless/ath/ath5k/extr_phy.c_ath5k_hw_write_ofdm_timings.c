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
struct ieee80211_channel {scalar_t__ hw_value; int center_freq; } ;
struct ath5k_hw {scalar_t__ ah_version; int ah_bwmode; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5212 ; 
#define  AR5K_BWMODE_10MHZ 130 
#define  AR5K_BWMODE_40MHZ 129 
#define  AR5K_BWMODE_5MHZ 128 
 scalar_t__ AR5K_MODE_11B ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_3 ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_3_DSC_EXP ; 
 int /*<<< orphan*/  AR5K_PHY_TIMING_3_DSC_MAN ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ilog2 (int) ; 

__attribute__((used)) static inline int
ath5k_hw_write_ofdm_timings(struct ath5k_hw *ah,
				struct ieee80211_channel *channel)
{
	/* Get exponent and mantissa and set it */
	u32 coef_scaled, coef_exp, coef_man,
		ds_coef_exp, ds_coef_man, clock;

	BUG_ON(!(ah->ah_version == AR5K_AR5212) ||
		(channel->hw_value == AR5K_MODE_11B));

	/* Get coefficient
	 * ALGO: coef = (5 * clock / carrier_freq) / 2
	 * we scale coef by shifting clock value by 24 for
	 * better precision since we use integers */
	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		clock = 40 * 2;
		break;
	case AR5K_BWMODE_10MHZ:
		clock = 40 / 2;
		break;
	case AR5K_BWMODE_5MHZ:
		clock = 40 / 4;
		break;
	default:
		clock = 40;
		break;
	}
	coef_scaled = ((5 * (clock << 24)) / 2) / channel->center_freq;

	/* Get exponent
	 * ALGO: coef_exp = 14 - highest set bit position */
	coef_exp = ilog2(coef_scaled);

	/* Doesn't make sense if it's zero*/
	if (!coef_scaled || !coef_exp)
		return -EINVAL;

	/* Note: we've shifted coef_scaled by 24 */
	coef_exp = 14 - (coef_exp - 24);


	/* Get mantissa (significant digits)
	 * ALGO: coef_mant = floor(coef_scaled* 2^coef_exp+0.5) */
	coef_man = coef_scaled +
		(1 << (24 - coef_exp - 1));

	/* Calculate delta slope coefficient exponent
	 * and mantissa (remove scaling) and set them on hw */
	ds_coef_man = coef_man >> (24 - coef_exp);
	ds_coef_exp = coef_exp - 16;

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_3,
		AR5K_PHY_TIMING_3_DSC_MAN, ds_coef_man);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_3,
		AR5K_PHY_TIMING_3_DSC_EXP, ds_coef_exp);

	return 0;
}