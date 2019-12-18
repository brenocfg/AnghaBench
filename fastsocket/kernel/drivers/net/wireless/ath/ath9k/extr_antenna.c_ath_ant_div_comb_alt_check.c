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
typedef  int u8 ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO ; 
 int ATH_ANT_DIV_COMB_LNA1 ; 
 int ATH_ANT_DIV_COMB_LNA2 ; 

__attribute__((used)) static inline bool ath_ant_div_comb_alt_check(u8 div_group, int alt_ratio,
					      int curr_main_set, int curr_alt_set,
					      int alt_rssi_avg, int main_rssi_avg)
{
	bool result = false;
	switch (div_group) {
	case 0:
		if (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)
			result = true;
		break;
	case 1:
	case 2:
		if ((((curr_main_set == ATH_ANT_DIV_COMB_LNA2) &&
		      (curr_alt_set == ATH_ANT_DIV_COMB_LNA1) &&
		      (alt_rssi_avg >= (main_rssi_avg - 5))) ||
		     ((curr_main_set == ATH_ANT_DIV_COMB_LNA1) &&
		      (curr_alt_set == ATH_ANT_DIV_COMB_LNA2) &&
		      (alt_rssi_avg >= (main_rssi_avg - 2)))) &&
		    (alt_rssi_avg >= 4))
			result = true;
		else
			result = false;
		break;
	}

	return result;
}