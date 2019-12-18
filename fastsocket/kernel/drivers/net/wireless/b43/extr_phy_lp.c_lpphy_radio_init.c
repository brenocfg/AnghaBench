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
struct TYPE_3__ {int radio_ver; } ;
struct b43_wldev {TYPE_2__* dev; TYPE_1__ phy; } ;
struct TYPE_4__ {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_FOURWIRE_CTL ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_2062_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_2063_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_sync_stx (struct b43_wldev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpphy_radio_init(struct b43_wldev *dev)
{
	/* The radio is attached through the 4wire bus. */
	b43_phy_set(dev, B43_LPPHY_FOURWIRE_CTL, 0x2);
	udelay(1);
	b43_phy_mask(dev, B43_LPPHY_FOURWIRE_CTL, 0xFFFD);
	udelay(1);

	if (dev->phy.radio_ver == 0x2062) {
		lpphy_2062_init(dev);
	} else {
		lpphy_2063_init(dev);
		lpphy_sync_stx(dev);
		b43_phy_write(dev, B43_PHY_OFDM(0xF0), 0x5F80);
		b43_phy_write(dev, B43_PHY_OFDM(0xF1), 0);
		if (dev->dev->chip_id == 0x4325) {
			// TODO SSB PMU recalibration
		}
	}
}