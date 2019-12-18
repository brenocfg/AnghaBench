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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void
wlc_phy_txpwr_nphy_srom_convert(u8 *srom_max, u16 *pwr_offset,
				u8 tmp_max_pwr, u8 rate_start,
				u8 rate_end)
{
	u8 rate;
	u8 word_num, nibble_num;
	u8 tmp_nibble;

	for (rate = rate_start; rate <= rate_end; rate++) {
		word_num = (rate - rate_start) >> 2;
		nibble_num = (rate - rate_start) & 0x3;
		tmp_nibble = (pwr_offset[word_num] >> 4 * nibble_num) & 0xf;

		srom_max[rate] = tmp_max_pwr - 2 * tmp_nibble;
	}
}