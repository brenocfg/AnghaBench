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
struct TYPE_2__ {int radio_ver; int /*<<< orphan*/  channel; } ;
struct b43_wldev {TYPE_1__ phy; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int B43_MACCTL_ENABLED ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_CTL1 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_2059_init (struct b43_wldev*) ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_switch_channel (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b43_phy_ht_op_software_rfkill(struct b43_wldev *dev,
					bool blocked)
{
	if (b43_read32(dev, B43_MMIO_MACCTL) & B43_MACCTL_ENABLED)
		b43err(dev->wl, "MAC not suspended\n");

	/* In the following PHY ops we copy wl's dummy behaviour.
	 * TODO: Find out if reads (currently hidden in masks/masksets) are
	 * needed and replace following ops with just writes or w&r.
	 * Note: B43_PHY_HT_RF_CTL1 register is tricky, wrong operation can
	 * cause delayed (!) machine lock up. */
	if (blocked) {
		b43_phy_mask(dev, B43_PHY_HT_RF_CTL1, 0);
	} else {
		b43_phy_mask(dev, B43_PHY_HT_RF_CTL1, 0);
		b43_phy_maskset(dev, B43_PHY_HT_RF_CTL1, 0, 0x1);
		b43_phy_mask(dev, B43_PHY_HT_RF_CTL1, 0);
		b43_phy_maskset(dev, B43_PHY_HT_RF_CTL1, 0, 0x2);

		if (dev->phy.radio_ver == 0x2059)
			b43_radio_2059_init(dev);
		else
			B43_WARN_ON(1);

		b43_switch_channel(dev, dev->phy.channel);
	}
}