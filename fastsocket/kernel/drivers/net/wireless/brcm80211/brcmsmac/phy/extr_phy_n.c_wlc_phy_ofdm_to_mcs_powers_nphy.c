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

void
wlc_phy_ofdm_to_mcs_powers_nphy(u8 *power, u8 rate_mcs_start,
				u8 rate_mcs_end, u8 rate_ofdm_start)
{
	u8 rate1, rate2;

	rate2 = rate_ofdm_start;
	for (rate1 = rate_mcs_start; rate1 <= rate_mcs_end - 1; rate1++) {
		power[rate1] = power[rate2];
		rate2 += (rate1 == rate_mcs_start) ? 2 : 1;
	}
	power[rate_mcs_end] = power[rate_mcs_end - 1];
}