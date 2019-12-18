#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct b43legacy_phy {int radio_rev; scalar_t__ type; int channel; int analog; } ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_RSSI ; 
 scalar_t__ B43legacy_PHYTYPE_B ; 
 scalar_t__ B43legacy_PHYTYPE_G ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_UCODEFLAGS_OFFSET ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_slope (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_threshold (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_init_pctl (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_g_measure (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_init2050 (struct b43legacy_wldev*) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_set_txpower_bg (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_shm_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43legacy_phy_initb6(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 offset;
	u16 val;
	u8 old_channel;

	b43legacy_phy_write(dev, 0x003E, 0x817A);
	b43legacy_radio_write16(dev, 0x007A,
				(b43legacy_radio_read16(dev, 0x007A) | 0x0058));
	if (phy->radio_rev == 4 ||
	     phy->radio_rev == 5) {
		b43legacy_radio_write16(dev, 0x0051, 0x0037);
		b43legacy_radio_write16(dev, 0x0052, 0x0070);
		b43legacy_radio_write16(dev, 0x0053, 0x00B3);
		b43legacy_radio_write16(dev, 0x0054, 0x009B);
		b43legacy_radio_write16(dev, 0x005A, 0x0088);
		b43legacy_radio_write16(dev, 0x005B, 0x0088);
		b43legacy_radio_write16(dev, 0x005D, 0x0088);
		b43legacy_radio_write16(dev, 0x005E, 0x0088);
		b43legacy_radio_write16(dev, 0x007D, 0x0088);
		b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET,
				      (b43legacy_shm_read32(dev,
				      B43legacy_SHM_SHARED,
				      B43legacy_UCODEFLAGS_OFFSET)
				      | 0x00000200));
	}
	if (phy->radio_rev == 8) {
		b43legacy_radio_write16(dev, 0x0051, 0x0000);
		b43legacy_radio_write16(dev, 0x0052, 0x0040);
		b43legacy_radio_write16(dev, 0x0053, 0x00B7);
		b43legacy_radio_write16(dev, 0x0054, 0x0098);
		b43legacy_radio_write16(dev, 0x005A, 0x0088);
		b43legacy_radio_write16(dev, 0x005B, 0x006B);
		b43legacy_radio_write16(dev, 0x005C, 0x000F);
		if (dev->dev->bus->sprom.boardflags_lo & 0x8000) {
			b43legacy_radio_write16(dev, 0x005D, 0x00FA);
			b43legacy_radio_write16(dev, 0x005E, 0x00D8);
		} else {
			b43legacy_radio_write16(dev, 0x005D, 0x00F5);
			b43legacy_radio_write16(dev, 0x005E, 0x00B8);
		}
		b43legacy_radio_write16(dev, 0x0073, 0x0003);
		b43legacy_radio_write16(dev, 0x007D, 0x00A8);
		b43legacy_radio_write16(dev, 0x007C, 0x0001);
		b43legacy_radio_write16(dev, 0x007E, 0x0008);
	}
	val = 0x1E1F;
	for (offset = 0x0088; offset < 0x0098; offset++) {
		b43legacy_phy_write(dev, offset, val);
		val -= 0x0202;
	}
	val = 0x3E3F;
	for (offset = 0x0098; offset < 0x00A8; offset++) {
		b43legacy_phy_write(dev, offset, val);
		val -= 0x0202;
	}
	val = 0x2120;
	for (offset = 0x00A8; offset < 0x00C8; offset++) {
		b43legacy_phy_write(dev, offset, (val & 0x3F3F));
		val += 0x0202;
	}
	if (phy->type == B43legacy_PHYTYPE_G) {
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A) |
					0x0020);
		b43legacy_radio_write16(dev, 0x0051,
					b43legacy_radio_read16(dev, 0x0051) |
					0x0004);
		b43legacy_phy_write(dev, 0x0802,
				    b43legacy_phy_read(dev, 0x0802) | 0x0100);
		b43legacy_phy_write(dev, 0x042B,
				    b43legacy_phy_read(dev, 0x042B) | 0x2000);
		b43legacy_phy_write(dev, 0x5B, 0x0000);
		b43legacy_phy_write(dev, 0x5C, 0x0000);
	}

	old_channel = phy->channel;
	if (old_channel >= 8)
		b43legacy_radio_selectchannel(dev, 1, 0);
	else
		b43legacy_radio_selectchannel(dev, 13, 0);

	b43legacy_radio_write16(dev, 0x0050, 0x0020);
	b43legacy_radio_write16(dev, 0x0050, 0x0023);
	udelay(40);
	if (phy->radio_rev < 6 || phy->radio_rev == 8) {
		b43legacy_radio_write16(dev, 0x007C,
					(b43legacy_radio_read16(dev, 0x007C)
					| 0x0002));
		b43legacy_radio_write16(dev, 0x0050, 0x0020);
	}
	if (phy->radio_rev <= 2) {
		b43legacy_radio_write16(dev, 0x0050, 0x0020);
		b43legacy_radio_write16(dev, 0x005A, 0x0070);
		b43legacy_radio_write16(dev, 0x005B, 0x007B);
		b43legacy_radio_write16(dev, 0x005C, 0x00B0);
	}
	b43legacy_radio_write16(dev, 0x007A,
				(b43legacy_radio_read16(dev,
				0x007A) & 0x00F8) | 0x0007);

	b43legacy_radio_selectchannel(dev, old_channel, 0);

	b43legacy_phy_write(dev, 0x0014, 0x0200);
	if (phy->radio_rev >= 6)
		b43legacy_phy_write(dev, 0x002A, 0x88C2);
	else
		b43legacy_phy_write(dev, 0x002A, 0x8AC0);
	b43legacy_phy_write(dev, 0x0038, 0x0668);
	b43legacy_radio_set_txpower_bg(dev, 0xFFFF, 0xFFFF, 0xFFFF);
	if (phy->radio_rev == 4 || phy->radio_rev == 5)
		b43legacy_phy_write(dev, 0x005D, (b43legacy_phy_read(dev,
				    0x005D) & 0xFF80) | 0x0003);
	if (phy->radio_rev <= 2)
		b43legacy_radio_write16(dev, 0x005D, 0x000D);

	if (phy->analog == 4) {
		b43legacy_write16(dev, 0x03E4, 0x0009);
		b43legacy_phy_write(dev, 0x61, b43legacy_phy_read(dev, 0x61)
				    & 0xFFF);
	} else
		b43legacy_phy_write(dev, 0x0002, (b43legacy_phy_read(dev,
				    0x0002) & 0xFFC0) | 0x0004);
	if (phy->type == B43legacy_PHYTYPE_G)
		b43legacy_write16(dev, 0x03E6, 0x0);
	if (phy->type == B43legacy_PHYTYPE_B) {
		b43legacy_write16(dev, 0x03E6, 0x8140);
		b43legacy_phy_write(dev, 0x0016, 0x0410);
		b43legacy_phy_write(dev, 0x0017, 0x0820);
		b43legacy_phy_write(dev, 0x0062, 0x0007);
		b43legacy_radio_init2050(dev);
		b43legacy_phy_lo_g_measure(dev);
		if (dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_RSSI) {
			b43legacy_calc_nrssi_slope(dev);
			b43legacy_calc_nrssi_threshold(dev);
		}
		b43legacy_phy_init_pctl(dev);
	}
}