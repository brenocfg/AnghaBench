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
typedef  int /*<<< orphan*/  u32 ;
struct b43_phy {int rev; struct b43_phy_g* g; } ;
struct b43_wldev {int /*<<< orphan*/  bad_frames_preempt; struct b43_phy phy; } ;
struct b43_phy_g {int aci_enable; int /*<<< orphan*/ * interfstack; } ;

/* Variables and functions */
 int B43_HF_ACIW ; 
#define  B43_INTERFMODE_MANUALWLAN 129 
#define  B43_INTERFMODE_NONWLAN 128 
 int B43_PHY_G_CRS ; 
 int B43_PHY_RADIO_BITFIELD ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_calc_nrssi_slope (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_calc_nrssi_threshold (struct b43_wldev*) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  ofdmtab_stackrestore (int,int) ; 
 int /*<<< orphan*/  phy_stackrestore (int) ; 
 int /*<<< orphan*/  radio_stackrestore (int) ; 

__attribute__((used)) static void
b43_radio_interference_mitigation_disable(struct b43_wldev *dev, int mode)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u32 *stack = gphy->interfstack;

	switch (mode) {
	case B43_INTERFMODE_NONWLAN:
		if (phy->rev != 1) {
			b43_phy_mask(dev, 0x042B, ~0x0800);
			b43_phy_set(dev, B43_PHY_G_CRS, 0x4000);
			break;
		}
		radio_stackrestore(0x0078);
		b43_calc_nrssi_threshold(dev);
		phy_stackrestore(0x0406);
		b43_phy_mask(dev, 0x042B, ~0x0800);
		if (!dev->bad_frames_preempt) {
			b43_phy_mask(dev, B43_PHY_RADIO_BITFIELD, ~(1 << 11));
		}
		b43_phy_set(dev, B43_PHY_G_CRS, 0x4000);
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
	case B43_INTERFMODE_MANUALWLAN:
		if (!(b43_phy_read(dev, 0x0033) & 0x0800))
			break;

		gphy->aci_enable = false;

		phy_stackrestore(B43_PHY_RADIO_BITFIELD);
		phy_stackrestore(B43_PHY_G_CRS);
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
			ofdmtab_stackrestore(0x1A00, 0x2);
			ofdmtab_stackrestore(0x1A00, 0x3);
		}
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x048A);
		phy_stackrestore(0x042B);
		phy_stackrestore(0x048C);
		b43_hf_write(dev, b43_hf_read(dev) & ~B43_HF_ACIW);
		b43_calc_nrssi_slope(dev);
		break;
	default:
		B43_WARN_ON(1);
	}
}