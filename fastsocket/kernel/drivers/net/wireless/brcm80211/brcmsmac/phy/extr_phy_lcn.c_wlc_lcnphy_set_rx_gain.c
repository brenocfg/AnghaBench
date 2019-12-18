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
typedef  int u16 ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_rx_gain_override_enable (struct brcms_phy*,int) ; 

__attribute__((used)) static void wlc_lcnphy_set_rx_gain(struct brcms_phy *pi, u32 gain)
{
	u16 trsw, ext_lna, lna1, lna2, tia, biq0, biq1, gain0_15, gain16_19;

	trsw = (gain & ((u32) 1 << 28)) ? 0 : 1;
	ext_lna = (u16) (gain >> 29) & 0x01;
	lna1 = (u16) (gain >> 0) & 0x0f;
	lna2 = (u16) (gain >> 4) & 0x0f;
	tia = (u16) (gain >> 8) & 0xf;
	biq0 = (u16) (gain >> 12) & 0xf;
	biq1 = (u16) (gain >> 16) & 0xf;

	gain0_15 = (u16) ((lna1 & 0x3) | ((lna1 & 0x3) << 2) |
			  ((lna2 & 0x3) << 4) | ((lna2 & 0x3) << 6) |
			  ((tia & 0xf) << 8) | ((biq0 & 0xf) << 12));
	gain16_19 = biq1;

	mod_phy_reg(pi, 0x44d, (0x1 << 0), trsw << 0);
	mod_phy_reg(pi, 0x4b1, (0x1 << 9), ext_lna << 9);
	mod_phy_reg(pi, 0x4b1, (0x1 << 10), ext_lna << 10);
	mod_phy_reg(pi, 0x4b6, (0xffff << 0), gain0_15 << 0);
	mod_phy_reg(pi, 0x4b7, (0xf << 0), gain16_19 << 0);

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		mod_phy_reg(pi, 0x4b1, (0x3 << 11), lna1 << 11);
		mod_phy_reg(pi, 0x4e6, (0x3 << 3), lna1 << 3);
	}
	wlc_lcnphy_rx_gain_override_enable(pi, true);
}