#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_2__ pubpi; TYPE_1__* sh; } ;
struct TYPE_3__ {int boardrev; } ;

/* Variables and functions */
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2064_REG09B ; 
 int /*<<< orphan*/  RADIO_2064_REG0F1 ; 
 int /*<<< orphan*/  RADIO_2064_REG0F2 ; 
 int /*<<< orphan*/  RADIO_2064_REG0F3 ; 
 int /*<<< orphan*/  RADIO_2064_REG0F7 ; 
 int /*<<< orphan*/  RADIO_2064_REG11F ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_clear_tx_power_offsets (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_bu_tweaks(struct brcms_phy *pi)
{
	or_phy_reg(pi, 0x805, 0x1);

	mod_phy_reg(pi, 0x42f, (0x7 << 0), (0x3) << 0);

	mod_phy_reg(pi, 0x030, (0x7 << 0), (0x3) << 0);

	write_phy_reg(pi, 0x414, 0x1e10);
	write_phy_reg(pi, 0x415, 0x0640);

	mod_phy_reg(pi, 0x4df, (0xff << 8), -9 << 8);

	or_phy_reg(pi, 0x44a, 0x44);
	write_phy_reg(pi, 0x44a, 0x80);
	mod_phy_reg(pi, 0x434, (0xff << 0), (0xFD) << 0);

	mod_phy_reg(pi, 0x420, (0xff << 0), (16) << 0);

	if (!(pi->sh->boardrev < 0x1204))
		mod_radio_reg(pi, RADIO_2064_REG09B, 0xF0, 0xF0);

	write_phy_reg(pi, 0x7d6, 0x0902);
	mod_phy_reg(pi, 0x429, (0xf << 0), (0x9) << 0);

	mod_phy_reg(pi, 0x429, (0x3f << 4), (0xe) << 4);

	if (LCNREV_IS(pi->pubpi.phy_rev, 1)) {
		mod_phy_reg(pi, 0x423, (0xff << 0), (0x46) << 0);

		mod_phy_reg(pi, 0x411, (0xff << 0), (1) << 0);

		mod_phy_reg(pi, 0x434, (0xff << 0), (0xFF) << 0);

		mod_phy_reg(pi, 0x656, (0xf << 0), (2) << 0);

		mod_phy_reg(pi, 0x44d, (0x1 << 2), (1) << 2);

		mod_radio_reg(pi, RADIO_2064_REG0F7, 0x4, 0x4);
		mod_radio_reg(pi, RADIO_2064_REG0F1, 0x3, 0);
		mod_radio_reg(pi, RADIO_2064_REG0F2, 0xF8, 0x90);
		mod_radio_reg(pi, RADIO_2064_REG0F3, 0x3, 0x2);
		mod_radio_reg(pi, RADIO_2064_REG0F3, 0xf0, 0xa0);

		mod_radio_reg(pi, RADIO_2064_REG11F, 0x2, 0x2);

		wlc_lcnphy_clear_tx_power_offsets(pi);
		mod_phy_reg(pi, 0x4d0, (0x1ff << 6), (10) << 6);

	}
}