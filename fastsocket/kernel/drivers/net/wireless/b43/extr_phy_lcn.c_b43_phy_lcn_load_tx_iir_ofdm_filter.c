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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int /*<<< orphan*/  member_0; } ;
struct lcn_tx_iir_filter {int member_0; scalar_t__ type; int /*<<< orphan*/ * values; TYPE_1__ member_1; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lcn_tx_iir_filter*) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool b43_phy_lcn_load_tx_iir_ofdm_filter(struct b43_wldev *dev,
						u8 filter_type)
{
	int i, j;
	u16 phy_regs[] = { 0x90f, 0x900, 0x901, 0x906, 0x907, 0x908, 0x902,
			   0x903, 0x909, 0x90a, 0x90b, 0x904, 0x905, 0x90c,
			   0x90d, 0x90e };
	struct lcn_tx_iir_filter tx_iir_filters_ofdm[] = {
		{ 0, { 0, 0xa2, 0x0, 0x100, 0x100, 0x0, 0x0, 0x0, 0x100, 0x0,
		       0x0, 0x278, 0xfea0, 0x80, 0x100, 0x80 } },
		{ 1, { 0, 374, 0xFF79, 16, 32, 16, 799, 0xFE74, 50, 32, 50, 750,
		       0xFE2B, 212, 0xFFCE, 212 } },
		{ 2, { 0, 375, 0xFF16, 37, 76, 37, 799, 0xFE74, 32, 20, 32, 748,
		       0xFEF2, 128, 0xFFE2, 128 } },
	};

	for (i = 0; i < ARRAY_SIZE(tx_iir_filters_ofdm); i++) {
		if (tx_iir_filters_ofdm[i].type == filter_type) {
			for (j = 0; j < 16; j++)
				b43_phy_write(dev, phy_regs[j],
					      tx_iir_filters_ofdm[i].values[j]);
			return true;
		}
	}

	return false;
}