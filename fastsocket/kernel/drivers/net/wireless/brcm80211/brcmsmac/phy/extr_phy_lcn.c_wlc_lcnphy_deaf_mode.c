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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 

void wlc_lcnphy_deaf_mode(struct brcms_phy *pi, bool mode)
{

	u8 phybw40;
	phybw40 = CHSPEC_IS40(pi->radio_chanspec);

	if (LCNREV_LT(pi->pubpi.phy_rev, 2)) {
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), (mode) << 5);
		mod_phy_reg(pi, 0x4b1, (0x1 << 9), 0 << 9);
	} else {
		mod_phy_reg(pi, 0x4b0, (0x1 << 5), (mode) << 5);
		mod_phy_reg(pi, 0x4b1, (0x1 << 9), 0 << 9);
	}

	if (phybw40 == 0) {
		mod_phy_reg((pi), 0x410,
			    (0x1 << 6) |
			    (0x1 << 5),
			    ((CHSPEC_IS2G(
				      pi->radio_chanspec)) ? (!mode) : 0) <<
			    6 | (!mode) << 5);
		mod_phy_reg(pi, 0x410, (0x1 << 7), (mode) << 7);
	}
}