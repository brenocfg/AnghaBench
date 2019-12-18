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
struct mii_phy {scalar_t__ pause; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; scalar_t__ autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int LPA_100FULL ; 
 int LPA_100HALF ; 
 int LPA_10FULL ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genmii_read_link(struct mii_phy *phy)
{
	u16 lpa;

	if (phy->autoneg) {
		lpa = phy_read(phy, MII_LPA);

		if (lpa & (LPA_10FULL | LPA_100FULL))
			phy->duplex = DUPLEX_FULL;
		else
			phy->duplex = DUPLEX_HALF;
		if (lpa & (LPA_100FULL | LPA_100HALF))
			phy->speed = SPEED_100;
		else
			phy->speed = SPEED_10;
		phy->pause = 0;
	}
	/* On non-aneg, we assume what we put in BMCR is the speed,
	 * though magic-aneg shouldn't prevent this case from occurring
	 */

	 return 0;
}