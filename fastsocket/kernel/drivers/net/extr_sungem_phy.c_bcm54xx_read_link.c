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
struct mii_phy {scalar_t__ duplex; int pause; int /*<<< orphan*/  speed; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int LPA_PAUSE ; 
 int /*<<< orphan*/  MII_BCM5400_AUXSTATUS ; 
 int MII_BCM5400_AUXSTATUS_LINKMODE_MASK ; 
 int MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 scalar_t__** phy_BCM5400_link_table ; 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm54xx_read_link(struct mii_phy *phy)
{
	int link_mode;
	u16 val;

	if (phy->autoneg) {
	    	val = phy_read(phy, MII_BCM5400_AUXSTATUS);
		link_mode = ((val & MII_BCM5400_AUXSTATUS_LINKMODE_MASK) >>
			     MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT);
		phy->duplex = phy_BCM5400_link_table[link_mode][0] ?
			DUPLEX_FULL : DUPLEX_HALF;
		phy->speed = phy_BCM5400_link_table[link_mode][2] ?
				SPEED_1000 :
				(phy_BCM5400_link_table[link_mode][1] ?
				 SPEED_100 : SPEED_10);
		val = phy_read(phy, MII_LPA);
		phy->pause = (phy->duplex == DUPLEX_FULL) &&
			((val & LPA_PAUSE) != 0);
	}
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this case from occurring
	 */

	return 0;
}