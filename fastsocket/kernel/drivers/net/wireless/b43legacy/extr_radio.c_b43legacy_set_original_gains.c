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
struct b43legacy_phy {int rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_dummy_transmission (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_ilt_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 

__attribute__((used)) static void b43legacy_set_original_gains(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 i;
	u16 tmp;
	u16 offset = 0x0400;
	u16 start = 0x0008;
	u16 end = 0x0018;

	if (phy->rev <= 1) {
		offset = 0x5000;
		start = 0x0010;
		end = 0x0020;
	}

	for (i = 0; i < 4; i++) {
		tmp = (i & 0xFFFC);
		tmp |= (i & 0x0001) << 1;
		tmp |= (i & 0x0002) >> 1;

		b43legacy_ilt_write(dev, offset + i, tmp);
	}

	for (i = start; i < end; i++)
		b43legacy_ilt_write(dev, offset + i, i - start);

	b43legacy_phy_write(dev, 0x04A0,
			    (b43legacy_phy_read(dev, 0x04A0) & 0xBFBF)
			    | 0x4040);
	b43legacy_phy_write(dev, 0x04A1,
			    (b43legacy_phy_read(dev, 0x04A1) & 0xBFBF)
			    | 0x4040);
	b43legacy_phy_write(dev, 0x04A2,
			    (b43legacy_phy_read(dev, 0x04A2) & 0xBFBF)
			    | 0x4000);
	b43legacy_dummy_transmission(dev);
}