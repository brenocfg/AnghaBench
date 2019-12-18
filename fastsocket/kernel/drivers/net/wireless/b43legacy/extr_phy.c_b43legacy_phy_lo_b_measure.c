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
typedef  int u16 ;
struct b43legacy_phy {int radio_ver; int* minlowsig; int* minlowsigpos; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int b43legacy_phy_lo_b_r15_loop (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 

void b43legacy_phy_lo_b_measure(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 regstack[12] = { 0 };
	u16 mls;
	u16 fval;
	int i;
	int j;

	regstack[0] = b43legacy_phy_read(dev, 0x0015);
	regstack[1] = b43legacy_radio_read16(dev, 0x0052) & 0xFFF0;

	if (phy->radio_ver == 0x2053) {
		regstack[2] = b43legacy_phy_read(dev, 0x000A);
		regstack[3] = b43legacy_phy_read(dev, 0x002A);
		regstack[4] = b43legacy_phy_read(dev, 0x0035);
		regstack[5] = b43legacy_phy_read(dev, 0x0003);
		regstack[6] = b43legacy_phy_read(dev, 0x0001);
		regstack[7] = b43legacy_phy_read(dev, 0x0030);

		regstack[8] = b43legacy_radio_read16(dev, 0x0043);
		regstack[9] = b43legacy_radio_read16(dev, 0x007A);
		regstack[10] = b43legacy_read16(dev, 0x03EC);
		regstack[11] = b43legacy_radio_read16(dev, 0x0052) & 0x00F0;

		b43legacy_phy_write(dev, 0x0030, 0x00FF);
		b43legacy_write16(dev, 0x03EC, 0x3F3F);
		b43legacy_phy_write(dev, 0x0035, regstack[4] & 0xFF7F);
		b43legacy_radio_write16(dev, 0x007A, regstack[9] & 0xFFF0);
	}
	b43legacy_phy_write(dev, 0x0015, 0xB000);
	b43legacy_phy_write(dev, 0x002B, 0x0004);

	if (phy->radio_ver == 0x2053) {
		b43legacy_phy_write(dev, 0x002B, 0x0203);
		b43legacy_phy_write(dev, 0x002A, 0x08A3);
	}

	phy->minlowsig[0] = 0xFFFF;

	for (i = 0; i < 4; i++) {
		b43legacy_radio_write16(dev, 0x0052, regstack[1] | i);
		b43legacy_phy_lo_b_r15_loop(dev);
	}
	for (i = 0; i < 10; i++) {
		b43legacy_radio_write16(dev, 0x0052, regstack[1] | i);
		mls = b43legacy_phy_lo_b_r15_loop(dev) / 10;
		if (mls < phy->minlowsig[0]) {
			phy->minlowsig[0] = mls;
			phy->minlowsigpos[0] = i;
		}
	}
	b43legacy_radio_write16(dev, 0x0052, regstack[1]
				| phy->minlowsigpos[0]);

	phy->minlowsig[1] = 0xFFFF;

	for (i = -4; i < 5; i += 2) {
		for (j = -4; j < 5; j += 2) {
			if (j < 0)
				fval = (0x0100 * i) + j + 0x0100;
			else
				fval = (0x0100 * i) + j;
			b43legacy_phy_write(dev, 0x002F, fval);
			mls = b43legacy_phy_lo_b_r15_loop(dev) / 10;
			if (mls < phy->minlowsig[1]) {
				phy->minlowsig[1] = mls;
				phy->minlowsigpos[1] = fval;
			}
		}
	}
	phy->minlowsigpos[1] += 0x0101;

	b43legacy_phy_write(dev, 0x002F, phy->minlowsigpos[1]);
	if (phy->radio_ver == 0x2053) {
		b43legacy_phy_write(dev, 0x000A, regstack[2]);
		b43legacy_phy_write(dev, 0x002A, regstack[3]);
		b43legacy_phy_write(dev, 0x0035, regstack[4]);
		b43legacy_phy_write(dev, 0x0003, regstack[5]);
		b43legacy_phy_write(dev, 0x0001, regstack[6]);
		b43legacy_phy_write(dev, 0x0030, regstack[7]);

		b43legacy_radio_write16(dev, 0x0043, regstack[8]);
		b43legacy_radio_write16(dev, 0x007A, regstack[9]);

		b43legacy_radio_write16(dev, 0x0052,
					(b43legacy_radio_read16(dev, 0x0052)
					& 0x000F) | regstack[11]);

		b43legacy_write16(dev, 0x03EC, regstack[10]);
	}
	b43legacy_phy_write(dev, 0x0015, regstack[0]);
}