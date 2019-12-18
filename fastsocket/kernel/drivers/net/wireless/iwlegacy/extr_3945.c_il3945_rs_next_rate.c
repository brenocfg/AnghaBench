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
struct TYPE_2__ {int sta_supp_rates; } ;
struct il_priv {int band; TYPE_1__ _3945; } ;

/* Variables and functions */
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int IL_OFDM_RATES_MASK ; 
 int RATE_11M_IDX ; 
 int RATE_12M_IDX ; 
 int RATE_5M_IDX ; 
 int RATE_6M_IDX ; 
 int RATE_9M_IDX ; 
 int il3945_get_prev_ieee_rate (int) ; 
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 

int
il3945_rs_next_rate(struct il_priv *il, int rate)
{
	int next_rate = il3945_get_prev_ieee_rate(rate);

	switch (il->band) {
	case IEEE80211_BAND_5GHZ:
		if (rate == RATE_12M_IDX)
			next_rate = RATE_9M_IDX;
		else if (rate == RATE_6M_IDX)
			next_rate = RATE_6M_IDX;
		break;
	case IEEE80211_BAND_2GHZ:
		if (!(il->_3945.sta_supp_rates & IL_OFDM_RATES_MASK) &&
		    il_is_associated(il)) {
			if (rate == RATE_11M_IDX)
				next_rate = RATE_5M_IDX;
		}
		break;

	default:
		break;
	}

	return next_rate;
}