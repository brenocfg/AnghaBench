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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_phy_switch_radio_nphy (struct brcms_phy*,int) ; 

void wlc_phy_switch_radio(struct brcms_phy_pub *pih, bool on)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;
	(void)bcma_read32(pi->d11core, D11REGOFFS(maccontrol));

	if (ISNPHY(pi)) {
		wlc_phy_switch_radio_nphy(pi, on);
	} else if (ISLCNPHY(pi)) {
		if (on) {
			and_phy_reg(pi, 0x44c,
				    ~((0x1 << 8) |
				      (0x1 << 9) |
				      (0x1 << 10) | (0x1 << 11) | (0x1 << 12)));
			and_phy_reg(pi, 0x4b0, ~((0x1 << 3) | (0x1 << 11)));
			and_phy_reg(pi, 0x4f9, ~(0x1 << 3));
		} else {
			and_phy_reg(pi, 0x44d,
				    ~((0x1 << 10) |
				      (0x1 << 11) |
				      (0x1 << 12) | (0x1 << 13) | (0x1 << 14)));
			or_phy_reg(pi, 0x44c,
				   (0x1 << 8) |
				   (0x1 << 9) |
				   (0x1 << 10) | (0x1 << 11) | (0x1 << 12));

			and_phy_reg(pi, 0x4b7, ~((0x7f << 8)));
			and_phy_reg(pi, 0x4b1, ~((0x1 << 13)));
			or_phy_reg(pi, 0x4b0, (0x1 << 3) | (0x1 << 11));
			and_phy_reg(pi, 0x4fa, ~((0x1 << 3)));
			or_phy_reg(pi, 0x4f9, (0x1 << 3));
		}
	}
}