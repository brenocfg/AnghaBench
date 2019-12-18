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
struct b43_phy {int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int B43_ANTENNA_AUTO0 ; 
 int B43_ANTENNA_AUTO1 ; 
 int B43_HF_ANTDIVHELP ; 
 int /*<<< orphan*/  B43_PHY_ADIVRELATED ; 
 int /*<<< orphan*/  B43_PHY_ANTDWELL ; 
 int B43_PHY_ANTDWELL_AUTODIV1 ; 
 int /*<<< orphan*/  B43_PHY_BBANDCFG ; 
 int B43_PHY_BBANDCFG_RXANT ; 
 int B43_PHY_BBANDCFG_RXANT_SHIFT ; 
 int /*<<< orphan*/  B43_PHY_CLIPPWRDOWNT ; 
 int /*<<< orphan*/  B43_PHY_OFDM61 ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_aphy_op_set_rx_antenna(struct b43_wldev *dev, int antenna)
{//TODO
	struct b43_phy *phy = &dev->phy;
	u16 tmp;
	int autodiv = 0;

	if (antenna == B43_ANTENNA_AUTO0 || antenna == B43_ANTENNA_AUTO1)
		autodiv = 1;

	b43_hf_write(dev, b43_hf_read(dev) & ~B43_HF_ANTDIVHELP);

	b43_phy_maskset(dev, B43_PHY_BBANDCFG, ~B43_PHY_BBANDCFG_RXANT,
			(autodiv ? B43_ANTENNA_AUTO1 : antenna) <<
			B43_PHY_BBANDCFG_RXANT_SHIFT);

	if (autodiv) {
		tmp = b43_phy_read(dev, B43_PHY_ANTDWELL);
		if (antenna == B43_ANTENNA_AUTO1)
			tmp &= ~B43_PHY_ANTDWELL_AUTODIV1;
		else
			tmp |= B43_PHY_ANTDWELL_AUTODIV1;
		b43_phy_write(dev, B43_PHY_ANTDWELL, tmp);
	}
	if (phy->rev < 3)
		b43_phy_maskset(dev, B43_PHY_ANTDWELL, 0xFF00, 0x24);
	else {
		b43_phy_set(dev, B43_PHY_OFDM61, 0x10);
		if (phy->rev == 3) {
			b43_phy_write(dev, B43_PHY_CLIPPWRDOWNT, 0x1D);
			b43_phy_write(dev, B43_PHY_ADIVRELATED, 8);
		} else {
			b43_phy_write(dev, B43_PHY_CLIPPWRDOWNT, 0x3A);
			b43_phy_maskset(dev, B43_PHY_ADIVRELATED, 0xFF00, 8);
		}
	}

	b43_hf_write(dev, b43_hf_read(dev) | B43_HF_ANTDIVHELP);
}