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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_phy {int radio_manuf; int radio_ver; int radio_rev; int analog; int type; int rev; } ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; struct b43legacy_phy phy; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int chip_id; int chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int /*<<< orphan*/  B43legacy_MMIO_PHY_VER ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_CONTROL ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_DATA_HIGH ; 
 int /*<<< orphan*/  B43legacy_MMIO_RADIO_DATA_LOW ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int B43legacy_PHYVER_ANALOG ; 
 int B43legacy_PHYVER_ANALOG_SHIFT ; 
 int B43legacy_PHYVER_TYPE ; 
 int B43legacy_PHYVER_TYPE_SHIFT ; 
 int B43legacy_PHYVER_VERSION ; 
 int /*<<< orphan*/  B43legacy_RADIOCTL_ID ; 
 int EOPNOTSUPP ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int b43legacy_phy_versioning(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u32 tmp;
	u8 analog_type;
	u8 phy_type;
	u8 phy_rev;
	u16 radio_manuf;
	u16 radio_ver;
	u16 radio_rev;
	int unsupported = 0;

	/* Get PHY versioning */
	tmp = b43legacy_read16(dev, B43legacy_MMIO_PHY_VER);
	analog_type = (tmp & B43legacy_PHYVER_ANALOG)
		      >> B43legacy_PHYVER_ANALOG_SHIFT;
	phy_type = (tmp & B43legacy_PHYVER_TYPE) >> B43legacy_PHYVER_TYPE_SHIFT;
	phy_rev = (tmp & B43legacy_PHYVER_VERSION);
	switch (phy_type) {
	case B43legacy_PHYTYPE_B:
		if (phy_rev != 2 && phy_rev != 4
		    && phy_rev != 6 && phy_rev != 7)
			unsupported = 1;
		break;
	case B43legacy_PHYTYPE_G:
		if (phy_rev > 8)
			unsupported = 1;
		break;
	default:
		unsupported = 1;
	}
	if (unsupported) {
		b43legacyerr(dev->wl, "FOUND UNSUPPORTED PHY "
		       "(Analog %u, Type %u, Revision %u)\n",
		       analog_type, phy_type, phy_rev);
		return -EOPNOTSUPP;
	}
	b43legacydbg(dev->wl, "Found PHY: Analog %u, Type %u, Revision %u\n",
	       analog_type, phy_type, phy_rev);


	/* Get RADIO versioning */
	if (dev->dev->bus->chip_id == 0x4317) {
		if (dev->dev->bus->chip_rev == 0)
			tmp = 0x3205017F;
		else if (dev->dev->bus->chip_rev == 1)
			tmp = 0x4205017F;
		else
			tmp = 0x5205017F;
	} else {
		b43legacy_write16(dev, B43legacy_MMIO_RADIO_CONTROL,
				  B43legacy_RADIOCTL_ID);
		tmp = b43legacy_read16(dev, B43legacy_MMIO_RADIO_DATA_HIGH);
		tmp <<= 16;
		b43legacy_write16(dev, B43legacy_MMIO_RADIO_CONTROL,
				  B43legacy_RADIOCTL_ID);
		tmp |= b43legacy_read16(dev, B43legacy_MMIO_RADIO_DATA_LOW);
	}
	radio_manuf = (tmp & 0x00000FFF);
	radio_ver = (tmp & 0x0FFFF000) >> 12;
	radio_rev = (tmp & 0xF0000000) >> 28;
	switch (phy_type) {
	case B43legacy_PHYTYPE_B:
		if ((radio_ver & 0xFFF0) != 0x2050)
			unsupported = 1;
		break;
	case B43legacy_PHYTYPE_G:
		if (radio_ver != 0x2050)
			unsupported = 1;
		break;
	default:
		B43legacy_BUG_ON(1);
	}
	if (unsupported) {
		b43legacyerr(dev->wl, "FOUND UNSUPPORTED RADIO "
		       "(Manuf 0x%X, Version 0x%X, Revision %u)\n",
		       radio_manuf, radio_ver, radio_rev);
		return -EOPNOTSUPP;
	}
	b43legacydbg(dev->wl, "Found Radio: Manuf 0x%X, Version 0x%X,"
		     " Revision %u\n", radio_manuf, radio_ver, radio_rev);


	phy->radio_manuf = radio_manuf;
	phy->radio_ver = radio_ver;
	phy->radio_rev = radio_rev;

	phy->analog = analog_type;
	phy->type = phy_type;
	phy->rev = phy_rev;

	return 0;
}