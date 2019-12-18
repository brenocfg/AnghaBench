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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 

__attribute__((used)) static void
wlc_lcnphy_rx_gain_override_enable(struct brcms_phy *pi, bool enable)
{
	u16 ebit = enable ? 1 : 0;

	mod_phy_reg(pi, 0x4b0, (0x1 << 8), ebit << 8);

	mod_phy_reg(pi, 0x44c, (0x1 << 0), ebit << 0);

	if (LCNREV_LT(pi->pubpi.phy_rev, 2)) {
		mod_phy_reg(pi, 0x44c, (0x1 << 4), ebit << 4);
		mod_phy_reg(pi, 0x44c, (0x1 << 6), ebit << 6);
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), ebit << 5);
		mod_phy_reg(pi, 0x4b0, (0x1 << 6), ebit << 6);
	} else {
		mod_phy_reg(pi, 0x4b0, (0x1 << 12), ebit << 12);
		mod_phy_reg(pi, 0x4b0, (0x1 << 13), ebit << 13);
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), ebit << 5);
	}

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		mod_phy_reg(pi, 0x4b0, (0x1 << 10), ebit << 10);
		mod_phy_reg(pi, 0x4e5, (0x1 << 3), ebit << 3);
	}
}