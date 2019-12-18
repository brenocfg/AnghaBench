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
struct mii_phy {int autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_NCONFIG ; 
 int /*<<< orphan*/  phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm5461_enable_fiber(struct mii_phy* phy, int autoneg)
{
	/* select fiber mode, enable 1000 base-X registers */
	phy_write(phy, MII_NCONFIG, 0xfc0b);

	if (autoneg) {
		/* enable fiber with no autonegotiation */
		phy_write(phy, MII_ADVERTISE, 0x01e0);
		phy_write(phy, MII_BMCR, 0x1140);
	} else {
		/* enable fiber with autonegotiation */
		phy_write(phy, MII_BMCR, 0x0140);
	}

	phy->autoneg = autoneg;

	return 0;
}