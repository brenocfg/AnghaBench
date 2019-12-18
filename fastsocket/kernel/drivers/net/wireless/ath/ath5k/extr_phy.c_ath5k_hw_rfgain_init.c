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
struct ath5k_ini_rfgain {scalar_t__ rfg_register; int /*<<< orphan*/ * rfg_value; } ;
struct ath5k_hw {int ah_radio; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_REG_WAIT (unsigned int) ; 
#define  AR5K_RF2316 134 
#define  AR5K_RF2317 133 
#define  AR5K_RF2413 132 
#define  AR5K_RF2425 131 
#define  AR5K_RF5111 130 
#define  AR5K_RF5112 129 
#define  AR5K_RF5413 128 
 unsigned int ARRAY_SIZE (struct ath5k_ini_rfgain*) ; 
 int EINVAL ; 
 int IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath5k_ini_rfgain* rfgain_2316 ; 
 struct ath5k_ini_rfgain* rfgain_2413 ; 
 struct ath5k_ini_rfgain* rfgain_2425 ; 
 struct ath5k_ini_rfgain* rfgain_5111 ; 
 struct ath5k_ini_rfgain* rfgain_5112 ; 
 struct ath5k_ini_rfgain* rfgain_5413 ; 

__attribute__((used)) static int
ath5k_hw_rfgain_init(struct ath5k_hw *ah, enum ieee80211_band band)
{
	const struct ath5k_ini_rfgain *ath5k_rfg;
	unsigned int i, size, index;

	switch (ah->ah_radio) {
	case AR5K_RF5111:
		ath5k_rfg = rfgain_5111;
		size = ARRAY_SIZE(rfgain_5111);
		break;
	case AR5K_RF5112:
		ath5k_rfg = rfgain_5112;
		size = ARRAY_SIZE(rfgain_5112);
		break;
	case AR5K_RF2413:
		ath5k_rfg = rfgain_2413;
		size = ARRAY_SIZE(rfgain_2413);
		break;
	case AR5K_RF2316:
		ath5k_rfg = rfgain_2316;
		size = ARRAY_SIZE(rfgain_2316);
		break;
	case AR5K_RF5413:
		ath5k_rfg = rfgain_5413;
		size = ARRAY_SIZE(rfgain_5413);
		break;
	case AR5K_RF2317:
	case AR5K_RF2425:
		ath5k_rfg = rfgain_2425;
		size = ARRAY_SIZE(rfgain_2425);
		break;
	default:
		return -EINVAL;
	}

	index = (band == IEEE80211_BAND_2GHZ) ? 1 : 0;

	for (i = 0; i < size; i++) {
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_write(ah, ath5k_rfg[i].rfg_value[index],
			(u32)ath5k_rfg[i].rfg_register);
	}

	return 0;
}