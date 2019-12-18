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
typedef  int u8 ;
typedef  int u16 ;
struct b43_phy {int radio_rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;

/* Variables and functions */
 int R2057_BANDGAP_RCAL_TRIM ; 
 int R2057_IPA2G_CASCONV_CORE0 ; 
 int R2057_IQTEST_SEL_PU ; 
 int R2057_RCAL_CONFIG ; 
 int /*<<< orphan*/  R2057_RCAL_STATUS ; 
 int /*<<< orphan*/  R2057_RCCAL_N1_1 ; 
 int R2057_TEMPSENSE_CONFIG ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_wait_value (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 b43_radio_2057_rcal(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u16 tmp;

	if (phy->radio_rev == 5) {
		b43_phy_mask(dev, 0x342, ~0x2);
		udelay(10);
		b43_radio_set(dev, R2057_IQTEST_SEL_PU, 0x1);
		b43_radio_maskset(dev, 0x1ca, ~0x2, 0x1);
	}

	b43_radio_set(dev, R2057_RCAL_CONFIG, 0x1);
	udelay(10);
	b43_radio_set(dev, R2057_RCAL_CONFIG, 0x3);
	if (!b43_radio_wait_value(dev, R2057_RCCAL_N1_1, 1, 1, 100, 1000000)) {
		b43err(dev->wl, "Radio 0x2057 rcal timeout\n");
		return 0;
	}
	b43_radio_mask(dev, R2057_RCAL_CONFIG, ~0x2);
	tmp = b43_radio_read(dev, R2057_RCAL_STATUS) & 0x3E;
	b43_radio_mask(dev, R2057_RCAL_CONFIG, ~0x1);

	if (phy->radio_rev == 5) {
		b43_radio_mask(dev, R2057_IPA2G_CASCONV_CORE0, ~0x1);
		b43_radio_mask(dev, 0x1ca, ~0x2);
	}
	if (phy->radio_rev <= 4 || phy->radio_rev == 6) {
		b43_radio_maskset(dev, R2057_TEMPSENSE_CONFIG, ~0x3C, tmp);
		b43_radio_maskset(dev, R2057_BANDGAP_RCAL_TRIM, ~0xF0,
				  tmp << 2);
	}

	return tmp & 0x3e;
}