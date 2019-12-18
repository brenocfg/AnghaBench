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
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_phy {int* interfstack; int rev; int aci_enable; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int B43legacy_PHY_G_CRS ; 
 int B43legacy_PHY_RADIO_BITFIELD ; 
#define  B43legacy_RADIO_INTERFMODE_MANUALWLAN 129 
#define  B43legacy_RADIO_INTERFMODE_NONWLAN 128 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_UCODEFLAGS_OFFSET ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_slope (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_threshold (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_ilt_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_shm_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int flip_4bit (int) ; 
 int /*<<< orphan*/  ilt_stacksave (int) ; 
 int /*<<< orphan*/  phy_stacksave (int) ; 
 int /*<<< orphan*/  radio_stacksave (int) ; 

__attribute__((used)) static void
b43legacy_radio_interference_mitigation_enable(struct b43legacy_wldev *dev,
					       int mode)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 tmp;
	u16 flipped;
	u32 tmp32;
	size_t stackidx = 0;
	u32 *stack = phy->interfstack;

	switch (mode) {
	case B43legacy_RADIO_INTERFMODE_NONWLAN:
		if (phy->rev != 1) {
			b43legacy_phy_write(dev, 0x042B,
					    b43legacy_phy_read(dev, 0x042B)
					    | 0x0800);
			b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
					    b43legacy_phy_read(dev,
					    B43legacy_PHY_G_CRS) & ~0x4000);
			break;
		}
		radio_stacksave(0x0078);
		tmp = (b43legacy_radio_read16(dev, 0x0078) & 0x001E);
		flipped = flip_4bit(tmp);
		if (flipped < 10 && flipped >= 8)
			flipped = 7;
		else if (flipped >= 10)
			flipped -= 3;
		flipped = flip_4bit(flipped);
		flipped = (flipped << 1) | 0x0020;
		b43legacy_radio_write16(dev, 0x0078, flipped);

		b43legacy_calc_nrssi_threshold(dev);

		phy_stacksave(0x0406);
		b43legacy_phy_write(dev, 0x0406, 0x7E28);

		b43legacy_phy_write(dev, 0x042B,
				    b43legacy_phy_read(dev, 0x042B) | 0x0800);
		b43legacy_phy_write(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_read(dev,
				    B43legacy_PHY_RADIO_BITFIELD) | 0x1000);

		phy_stacksave(0x04A0);
		b43legacy_phy_write(dev, 0x04A0,
				    (b43legacy_phy_read(dev, 0x04A0) & 0xC0C0)
				    | 0x0008);
		phy_stacksave(0x04A1);
		b43legacy_phy_write(dev, 0x04A1,
				    (b43legacy_phy_read(dev, 0x04A1) & 0xC0C0)
				    | 0x0605);
		phy_stacksave(0x04A2);
		b43legacy_phy_write(dev, 0x04A2,
				    (b43legacy_phy_read(dev, 0x04A2) & 0xC0C0)
				    | 0x0204);
		phy_stacksave(0x04A8);
		b43legacy_phy_write(dev, 0x04A8,
				    (b43legacy_phy_read(dev, 0x04A8) & 0xC0C0)
				    | 0x0803);
		phy_stacksave(0x04AB);
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB) & 0xC0C0)
				    | 0x0605);

		phy_stacksave(0x04A7);
		b43legacy_phy_write(dev, 0x04A7, 0x0002);
		phy_stacksave(0x04A3);
		b43legacy_phy_write(dev, 0x04A3, 0x287A);
		phy_stacksave(0x04A9);
		b43legacy_phy_write(dev, 0x04A9, 0x2027);
		phy_stacksave(0x0493);
		b43legacy_phy_write(dev, 0x0493, 0x32F5);
		phy_stacksave(0x04AA);
		b43legacy_phy_write(dev, 0x04AA, 0x2027);
		phy_stacksave(0x04AC);
		b43legacy_phy_write(dev, 0x04AC, 0x32F5);
		break;
	case B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		if (b43legacy_phy_read(dev, 0x0033) & 0x0800)
			break;

		phy->aci_enable = true;

		phy_stacksave(B43legacy_PHY_RADIO_BITFIELD);
		phy_stacksave(B43legacy_PHY_G_CRS);
		if (phy->rev < 2)
			phy_stacksave(0x0406);
		else {
			phy_stacksave(0x04C0);
			phy_stacksave(0x04C1);
		}
		phy_stacksave(0x0033);
		phy_stacksave(0x04A7);
		phy_stacksave(0x04A3);
		phy_stacksave(0x04A9);
		phy_stacksave(0x04AA);
		phy_stacksave(0x04AC);
		phy_stacksave(0x0493);
		phy_stacksave(0x04A1);
		phy_stacksave(0x04A0);
		phy_stacksave(0x04A2);
		phy_stacksave(0x048A);
		phy_stacksave(0x04A8);
		phy_stacksave(0x04AB);
		if (phy->rev == 2) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x04AE);
		} else if (phy->rev >= 3) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x0415);
			phy_stacksave(0x0416);
			phy_stacksave(0x0417);
			ilt_stacksave(0x1A00 + 0x2);
			ilt_stacksave(0x1A00 + 0x3);
		}
		phy_stacksave(0x042B);
		phy_stacksave(0x048C);

		b43legacy_phy_write(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_read(dev,
				    B43legacy_PHY_RADIO_BITFIELD) & ~0x1000);
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
				    (b43legacy_phy_read(dev,
				    B43legacy_PHY_G_CRS)
				    & 0xFFFC) | 0x0002);

		b43legacy_phy_write(dev, 0x0033, 0x0800);
		b43legacy_phy_write(dev, 0x04A3, 0x2027);
		b43legacy_phy_write(dev, 0x04A9, 0x1CA8);
		b43legacy_phy_write(dev, 0x0493, 0x287A);
		b43legacy_phy_write(dev, 0x04AA, 0x1CA8);
		b43legacy_phy_write(dev, 0x04AC, 0x287A);

		b43legacy_phy_write(dev, 0x04A0,
				    (b43legacy_phy_read(dev, 0x04A0)
				    & 0xFFC0) | 0x001A);
		b43legacy_phy_write(dev, 0x04A7, 0x000D);

		if (phy->rev < 2)
			b43legacy_phy_write(dev, 0x0406, 0xFF0D);
		else if (phy->rev == 2) {
			b43legacy_phy_write(dev, 0x04C0, 0xFFFF);
			b43legacy_phy_write(dev, 0x04C1, 0x00A9);
		} else {
			b43legacy_phy_write(dev, 0x04C0, 0x00C1);
			b43legacy_phy_write(dev, 0x04C1, 0x0059);
		}

		b43legacy_phy_write(dev, 0x04A1,
				    (b43legacy_phy_read(dev, 0x04A1)
				    & 0xC0FF) | 0x1800);
		b43legacy_phy_write(dev, 0x04A1,
				    (b43legacy_phy_read(dev, 0x04A1)
				    & 0xFFC0) | 0x0015);
		b43legacy_phy_write(dev, 0x04A8,
				    (b43legacy_phy_read(dev, 0x04A8)
				    & 0xCFFF) | 0x1000);
		b43legacy_phy_write(dev, 0x04A8,
				    (b43legacy_phy_read(dev, 0x04A8)
				    & 0xF0FF) | 0x0A00);
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB)
				    & 0xCFFF) | 0x1000);
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB)
				    & 0xF0FF) | 0x0800);
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB)
				    & 0xFFCF) | 0x0010);
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB)
				    & 0xFFF0) | 0x0005);
		b43legacy_phy_write(dev, 0x04A8,
				    (b43legacy_phy_read(dev, 0x04A8)
				    & 0xFFCF) | 0x0010);
		b43legacy_phy_write(dev, 0x04A8,
				    (b43legacy_phy_read(dev, 0x04A8)
				    & 0xFFF0) | 0x0006);
		b43legacy_phy_write(dev, 0x04A2,
				    (b43legacy_phy_read(dev, 0x04A2)
				    & 0xF0FF) | 0x0800);
		b43legacy_phy_write(dev, 0x04A0,
				    (b43legacy_phy_read(dev, 0x04A0)
				    & 0xF0FF) | 0x0500);
		b43legacy_phy_write(dev, 0x04A2,
				    (b43legacy_phy_read(dev, 0x04A2)
				    & 0xFFF0) | 0x000B);

		if (phy->rev >= 3) {
			b43legacy_phy_write(dev, 0x048A,
					    b43legacy_phy_read(dev, 0x048A)
					    & ~0x8000);
			b43legacy_phy_write(dev, 0x0415,
					    (b43legacy_phy_read(dev, 0x0415)
					    & 0x8000) | 0x36D8);
			b43legacy_phy_write(dev, 0x0416,
					    (b43legacy_phy_read(dev, 0x0416)
					    & 0x8000) | 0x36D8);
			b43legacy_phy_write(dev, 0x0417,
					    (b43legacy_phy_read(dev, 0x0417)
					    & 0xFE00) | 0x016D);
		} else {
			b43legacy_phy_write(dev, 0x048A,
					    b43legacy_phy_read(dev, 0x048A)
					    | 0x1000);
			b43legacy_phy_write(dev, 0x048A,
					    (b43legacy_phy_read(dev, 0x048A)
					    & 0x9FFF) | 0x2000);
			tmp32 = b43legacy_shm_read32(dev, B43legacy_SHM_SHARED,
					    B43legacy_UCODEFLAGS_OFFSET);
			if (!(tmp32 & 0x800)) {
				tmp32 |= 0x800;
				b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
					    B43legacy_UCODEFLAGS_OFFSET,
					    tmp32);
			}
		}
		if (phy->rev >= 2)
			b43legacy_phy_write(dev, 0x042B,
					    b43legacy_phy_read(dev, 0x042B)
					    | 0x0800);
		b43legacy_phy_write(dev, 0x048C,
				    (b43legacy_phy_read(dev, 0x048C)
				    & 0xF0FF) | 0x0200);
		if (phy->rev == 2) {
			b43legacy_phy_write(dev, 0x04AE,
					    (b43legacy_phy_read(dev, 0x04AE)
					    & 0xFF00) | 0x007F);
			b43legacy_phy_write(dev, 0x04AD,
					    (b43legacy_phy_read(dev, 0x04AD)
					    & 0x00FF) | 0x1300);
		} else if (phy->rev >= 6) {
			b43legacy_ilt_write(dev, 0x1A00 + 0x3, 0x007F);
			b43legacy_ilt_write(dev, 0x1A00 + 0x2, 0x007F);
			b43legacy_phy_write(dev, 0x04AD,
					    b43legacy_phy_read(dev, 0x04AD)
					    & 0x00FF);
		}
		b43legacy_calc_nrssi_slope(dev);
		break;
	default:
		B43legacy_BUG_ON(1);
	}
}