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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;
typedef  enum lcnphy_tssi_mode { ____Placeholder_lcnphy_tssi_mode } lcnphy_tssi_mode ;

/* Variables and functions */
 int LCNPHY_TSSI_EXT ; 
 int LCNPHY_TSSI_POST_PA ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2064_REG005 ; 
 int /*<<< orphan*/  RADIO_2064_REG028 ; 
 int /*<<< orphan*/  RADIO_2064_REG03A ; 
 int /*<<< orphan*/  RADIO_2064_REG07F ; 
 int /*<<< orphan*/  RADIO_2064_REG086 ; 
 int /*<<< orphan*/  RADIO_2064_REG112 ; 
 int /*<<< orphan*/  RADIO_2064_REG11A ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_lcnphy_set_tssi_mux(struct brcms_phy *pi, enum lcnphy_tssi_mode pos)
{
	mod_phy_reg(pi, 0x4d7, (0x1 << 0), (0x1) << 0);

	mod_phy_reg(pi, 0x4d7, (0x1 << 6), (1) << 6);

	if (LCNPHY_TSSI_POST_PA == pos) {
		mod_phy_reg(pi, 0x4d9, (0x1 << 2), (0) << 2);

		mod_phy_reg(pi, 0x4d9, (0x1 << 3), (1) << 3);

		if (LCNREV_IS(pi->pubpi.phy_rev, 2)) {
			mod_radio_reg(pi, RADIO_2064_REG086, 0x4, 0x4);
		} else {
			mod_radio_reg(pi, RADIO_2064_REG03A, 1, 0x1);
			mod_radio_reg(pi, RADIO_2064_REG11A, 0x8, 0x8);
		}
	} else {
		mod_phy_reg(pi, 0x4d9, (0x1 << 2), (0x1) << 2);

		mod_phy_reg(pi, 0x4d9, (0x1 << 3), (0) << 3);

		if (LCNREV_IS(pi->pubpi.phy_rev, 2)) {
			mod_radio_reg(pi, RADIO_2064_REG086, 0x4, 0x4);
		} else {
			mod_radio_reg(pi, RADIO_2064_REG03A, 1, 0);
			mod_radio_reg(pi, RADIO_2064_REG11A, 0x8, 0x8);
		}
	}
	mod_phy_reg(pi, 0x637, (0x3 << 14), (0) << 14);

	if (LCNPHY_TSSI_EXT == pos) {
		write_radio_reg(pi, RADIO_2064_REG07F, 1);
		mod_radio_reg(pi, RADIO_2064_REG005, 0x7, 0x2);
		mod_radio_reg(pi, RADIO_2064_REG112, 0x80, 0x1 << 7);
		mod_radio_reg(pi, RADIO_2064_REG028, 0x1f, 0x3);
	}
}