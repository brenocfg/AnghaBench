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
typedef  int u8 ;
typedef  int u16 ;
struct nphy_rf_control_override_rev3 {int val_mask; int val_shift; int /*<<< orphan*/  val_addr1; int /*<<< orphan*/  val_addr0; int /*<<< orphan*/  en_addr1; int /*<<< orphan*/  en_addr0; } ;
struct nphy_rf_control_override_rev2 {int bmask; int shift; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr0; } ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;

/* Variables and functions */
 int B43_NPHY_RFCTL_CMD ; 
 int B43_NPHY_RFCTL_CMD_START ; 
 int B43_NPHY_RFCTL_OVER ; 
 int B43_PHY_N (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int fls (int) ; 
 struct nphy_rf_control_override_rev2* tbl_rf_control_override_rev2 ; 
 struct nphy_rf_control_override_rev3* tbl_rf_control_override_rev3 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_nphy_rf_ctl_override(struct b43_wldev *dev, u16 field,
				     u16 value, u8 core, bool off)
{
	int i;
	u8 index = fls(field);
	u8 addr, en_addr, val_addr;
	/* we expect only one bit set */
	B43_WARN_ON(field & (~(1 << (index - 1))));

	if (dev->phy.rev >= 3) {
		const struct nphy_rf_control_override_rev3 *rf_ctrl;
		for (i = 0; i < 2; i++) {
			if (index == 0 || index == 16) {
				b43err(dev->wl,
					"Unsupported RF Ctrl Override call\n");
				return;
			}

			rf_ctrl = &tbl_rf_control_override_rev3[index - 1];
			en_addr = B43_PHY_N((i == 0) ?
				rf_ctrl->en_addr0 : rf_ctrl->en_addr1);
			val_addr = B43_PHY_N((i == 0) ?
				rf_ctrl->val_addr0 : rf_ctrl->val_addr1);

			if (off) {
				b43_phy_mask(dev, en_addr, ~(field));
				b43_phy_mask(dev, val_addr,
						~(rf_ctrl->val_mask));
			} else {
				if (core == 0 || ((1 << i) & core)) {
					b43_phy_set(dev, en_addr, field);
					b43_phy_maskset(dev, val_addr,
						~(rf_ctrl->val_mask),
						(value << rf_ctrl->val_shift));
				}
			}
		}
	} else {
		const struct nphy_rf_control_override_rev2 *rf_ctrl;
		if (off) {
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~(field));
			value = 0;
		} else {
			b43_phy_set(dev, B43_NPHY_RFCTL_OVER, field);
		}

		for (i = 0; i < 2; i++) {
			if (index <= 1 || index == 16) {
				b43err(dev->wl,
					"Unsupported RF Ctrl Override call\n");
				return;
			}

			if (index == 2 || index == 10 ||
			    (index >= 13 && index <= 15)) {
				core = 1;
			}

			rf_ctrl = &tbl_rf_control_override_rev2[index - 2];
			addr = B43_PHY_N((i == 0) ?
				rf_ctrl->addr0 : rf_ctrl->addr1);

			if ((1 << i) & core)
				b43_phy_maskset(dev, addr, ~(rf_ctrl->bmask),
						(value << rf_ctrl->shift));

			b43_phy_set(dev, B43_NPHY_RFCTL_OVER, 0x1);
			b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
					B43_NPHY_RFCTL_CMD_START);
			udelay(1);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, 0xFFFE);
		}
	}
}