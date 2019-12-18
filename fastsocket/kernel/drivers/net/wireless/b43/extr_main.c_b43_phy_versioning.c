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
typedef  int u32 ;
typedef  int u16 ;
struct b43_phy {int radio_manuf; int radio_ver; int radio_rev; int analog; int type; int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; struct b43_phy phy; } ;
struct TYPE_2__ {int core_rev; int chip_id; int chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_PHY_VER ; 
 int /*<<< orphan*/  B43_MMIO_RADIO24_CONTROL ; 
 int /*<<< orphan*/  B43_MMIO_RADIO24_DATA ; 
 int /*<<< orphan*/  B43_MMIO_RADIO_CONTROL ; 
 int /*<<< orphan*/  B43_MMIO_RADIO_DATA_HIGH ; 
 int /*<<< orphan*/  B43_MMIO_RADIO_DATA_LOW ; 
#define  B43_PHYTYPE_A 134 
#define  B43_PHYTYPE_B 133 
#define  B43_PHYTYPE_G 132 
#define  B43_PHYTYPE_HT 131 
#define  B43_PHYTYPE_LCN 130 
#define  B43_PHYTYPE_LP 129 
#define  B43_PHYTYPE_N 128 
 int B43_PHYVER_ANALOG ; 
 int B43_PHYVER_ANALOG_SHIFT ; 
 int B43_PHYVER_TYPE ; 
 int B43_PHYVER_TYPE_SHIFT ; 
 int B43_PHYVER_VERSION ; 
 int B43_RADIOCTL_ID ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  b43_phy_name (struct b43_wldev*,int) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  b43info (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43_phy_versioning(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u32 tmp;
	u8 analog_type;
	u8 phy_type;
	u8 phy_rev;
	u16 radio_manuf;
	u16 radio_ver;
	u16 radio_rev;
	int unsupported = 0;

	/* Get PHY versioning */
	tmp = b43_read16(dev, B43_MMIO_PHY_VER);
	analog_type = (tmp & B43_PHYVER_ANALOG) >> B43_PHYVER_ANALOG_SHIFT;
	phy_type = (tmp & B43_PHYVER_TYPE) >> B43_PHYVER_TYPE_SHIFT;
	phy_rev = (tmp & B43_PHYVER_VERSION);
	switch (phy_type) {
	case B43_PHYTYPE_A:
		if (phy_rev >= 4)
			unsupported = 1;
		break;
	case B43_PHYTYPE_B:
		if (phy_rev != 2 && phy_rev != 4 && phy_rev != 6
		    && phy_rev != 7)
			unsupported = 1;
		break;
	case B43_PHYTYPE_G:
		if (phy_rev > 9)
			unsupported = 1;
		break;
#ifdef CONFIG_B43_PHY_N
	case B43_PHYTYPE_N:
		if (phy_rev > 9)
			unsupported = 1;
		break;
#endif
#ifdef CONFIG_B43_PHY_LP
	case B43_PHYTYPE_LP:
		if (phy_rev > 2)
			unsupported = 1;
		break;
#endif
#ifdef CONFIG_B43_PHY_HT
	case B43_PHYTYPE_HT:
		if (phy_rev > 1)
			unsupported = 1;
		break;
#endif
#ifdef CONFIG_B43_PHY_LCN
	case B43_PHYTYPE_LCN:
		if (phy_rev > 1)
			unsupported = 1;
		break;
#endif
	default:
		unsupported = 1;
	}
	if (unsupported) {
		b43err(dev->wl, "FOUND UNSUPPORTED PHY (Analog %u, Type %d (%s), Revision %u)\n",
		       analog_type, phy_type, b43_phy_name(dev, phy_type),
		       phy_rev);
		return -EOPNOTSUPP;
	}
	b43info(dev->wl, "Found PHY: Analog %u, Type %d (%s), Revision %u\n",
		analog_type, phy_type, b43_phy_name(dev, phy_type), phy_rev);

	/* Get RADIO versioning */
	if (dev->dev->core_rev >= 24) {
		u16 radio24[3];

		for (tmp = 0; tmp < 3; tmp++) {
			b43_write16(dev, B43_MMIO_RADIO24_CONTROL, tmp);
			radio24[tmp] = b43_read16(dev, B43_MMIO_RADIO24_DATA);
		}

		/* Broadcom uses "id" for our "ver" and has separated "ver" */
		/* radio_ver = (radio24[0] & 0xF0) >> 4; */

		radio_manuf = 0x17F;
		radio_ver = (radio24[2] << 8) | radio24[1];
		radio_rev = (radio24[0] & 0xF);
	} else {
		if (dev->dev->chip_id == 0x4317) {
			if (dev->dev->chip_rev == 0)
				tmp = 0x3205017F;
			else if (dev->dev->chip_rev == 1)
				tmp = 0x4205017F;
			else
				tmp = 0x5205017F;
		} else {
			b43_write16(dev, B43_MMIO_RADIO_CONTROL,
				    B43_RADIOCTL_ID);
			tmp = b43_read16(dev, B43_MMIO_RADIO_DATA_LOW);
			b43_write16(dev, B43_MMIO_RADIO_CONTROL,
				    B43_RADIOCTL_ID);
			tmp |= (u32)b43_read16(dev, B43_MMIO_RADIO_DATA_HIGH)
				<< 16;
		}
		radio_manuf = (tmp & 0x00000FFF);
		radio_ver = (tmp & 0x0FFFF000) >> 12;
		radio_rev = (tmp & 0xF0000000) >> 28;
	}

	if (radio_manuf != 0x17F /* Broadcom */)
		unsupported = 1;
	switch (phy_type) {
	case B43_PHYTYPE_A:
		if (radio_ver != 0x2060)
			unsupported = 1;
		if (radio_rev != 1)
			unsupported = 1;
		if (radio_manuf != 0x17F)
			unsupported = 1;
		break;
	case B43_PHYTYPE_B:
		if ((radio_ver & 0xFFF0) != 0x2050)
			unsupported = 1;
		break;
	case B43_PHYTYPE_G:
		if (radio_ver != 0x2050)
			unsupported = 1;
		break;
	case B43_PHYTYPE_N:
		if (radio_ver != 0x2055 && radio_ver != 0x2056)
			unsupported = 1;
		break;
	case B43_PHYTYPE_LP:
		if (radio_ver != 0x2062 && radio_ver != 0x2063)
			unsupported = 1;
		break;
	case B43_PHYTYPE_HT:
		if (radio_ver != 0x2059)
			unsupported = 1;
		break;
	case B43_PHYTYPE_LCN:
		if (radio_ver != 0x2064)
			unsupported = 1;
		break;
	default:
		B43_WARN_ON(1);
	}
	if (unsupported) {
		b43err(dev->wl, "FOUND UNSUPPORTED RADIO "
		       "(Manuf 0x%X, Version 0x%X, Revision %u)\n",
		       radio_manuf, radio_ver, radio_rev);
		return -EOPNOTSUPP;
	}
	b43dbg(dev->wl, "Found Radio: Manuf 0x%X, Version 0x%X, Revision %u\n",
	       radio_manuf, radio_ver, radio_rev);

	phy->radio_manuf = radio_manuf;
	phy->radio_ver = radio_ver;
	phy->radio_rev = radio_rev;

	phy->analog = analog_type;
	phy->type = phy_type;
	phy->rev = phy_rev;

	return 0;
}