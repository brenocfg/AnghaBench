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
struct b43legacy_phy {int* interfstack; int rev; int aci_enable; } ;
struct b43legacy_wldev {int /*<<< orphan*/  bad_frames_preempt; struct b43legacy_phy phy; } ;

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
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_shm_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilt_stackrestore (int) ; 
 int /*<<< orphan*/  phy_stackrestore (int) ; 

__attribute__((used)) static void
b43legacy_radio_interference_mitigation_disable(struct b43legacy_wldev *dev,
						int mode)
{
	struct b43legacy_phy *phy = &dev->phy;
	u32 tmp32;
	u32 *stack = phy->interfstack;

	switch (mode) {
	case B43legacy_RADIO_INTERFMODE_NONWLAN:
		if (phy->rev != 1) {
			b43legacy_phy_write(dev, 0x042B,
					    b43legacy_phy_read(dev, 0x042B)
					    & ~0x0800);
			b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
					    b43legacy_phy_read(dev,
					    B43legacy_PHY_G_CRS) | 0x4000);
			break;
		}
		phy_stackrestore(0x0078);
		b43legacy_calc_nrssi_threshold(dev);
		phy_stackrestore(0x0406);
		b43legacy_phy_write(dev, 0x042B,
				    b43legacy_phy_read(dev, 0x042B) & ~0x0800);
		if (!dev->bad_frames_preempt)
			b43legacy_phy_write(dev, B43legacy_PHY_RADIO_BITFIELD,
					    b43legacy_phy_read(dev,
					    B43legacy_PHY_RADIO_BITFIELD)
					    & ~(1 << 11));
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_read(dev, B43legacy_PHY_G_CRS)
				    | 0x4000);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x04A8);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A7);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		break;
	case B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		if (!(b43legacy_phy_read(dev, 0x0033) & 0x0800))
			break;

		phy->aci_enable = false;

		phy_stackrestore(B43legacy_PHY_RADIO_BITFIELD);
		phy_stackrestore(B43legacy_PHY_G_CRS);
		phy_stackrestore(0x0033);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A7);
		if (phy->rev >= 2) {
			phy_stackrestore(0x04C0);
			phy_stackrestore(0x04C1);
		} else
			phy_stackrestore(0x0406);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A8);
		if (phy->rev == 2) {
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x04AE);
		} else if (phy->rev >= 3) {
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x0415);
			phy_stackrestore(0x0416);
			phy_stackrestore(0x0417);
			ilt_stackrestore(0x1A00 + 0x2);
			ilt_stackrestore(0x1A00 + 0x3);
		}
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x04A8);
		phy_stackrestore(0x042B);
		phy_stackrestore(0x048C);
		tmp32 = b43legacy_shm_read32(dev, B43legacy_SHM_SHARED,
					     B43legacy_UCODEFLAGS_OFFSET);
		if (tmp32 & 0x800) {
			tmp32 &= ~0x800;
			b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      tmp32);
		}
		b43legacy_calc_nrssi_slope(dev);
		break;
	default:
		B43legacy_BUG_ON(1);
	}
}