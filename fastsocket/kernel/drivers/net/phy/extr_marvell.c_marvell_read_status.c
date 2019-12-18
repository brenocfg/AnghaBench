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
struct phy_device {scalar_t__ autoneg; scalar_t__ duplex; int pause; int asym_pause; void* speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_M1011_PHY_STATUS ; 
#define  MII_M1011_PHY_STATUS_100 129 
#define  MII_M1011_PHY_STATUS_1000 128 
 int MII_M1011_PHY_STATUS_FULLDUPLEX ; 
 int MII_M1011_PHY_STATUS_SPD_MASK ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int genphy_update_link (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_read_status(struct phy_device *phydev)
{
	int adv;
	int err;
	int lpa;
	int status = 0;

	/* Update the link, but return if there
	 * was an error */
	err = genphy_update_link(phydev);
	if (err)
		return err;

	if (AUTONEG_ENABLE == phydev->autoneg) {
		status = phy_read(phydev, MII_M1011_PHY_STATUS);
		if (status < 0)
			return status;

		lpa = phy_read(phydev, MII_LPA);
		if (lpa < 0)
			return lpa;

		adv = phy_read(phydev, MII_ADVERTISE);
		if (adv < 0)
			return adv;

		lpa &= adv;

		if (status & MII_M1011_PHY_STATUS_FULLDUPLEX)
			phydev->duplex = DUPLEX_FULL;
		else
			phydev->duplex = DUPLEX_HALF;

		status = status & MII_M1011_PHY_STATUS_SPD_MASK;
		phydev->pause = phydev->asym_pause = 0;

		switch (status) {
		case MII_M1011_PHY_STATUS_1000:
			phydev->speed = SPEED_1000;
			break;

		case MII_M1011_PHY_STATUS_100:
			phydev->speed = SPEED_100;
			break;

		default:
			phydev->speed = SPEED_10;
			break;
		}

		if (phydev->duplex == DUPLEX_FULL) {
			phydev->pause = lpa & LPA_PAUSE_CAP ? 1 : 0;
			phydev->asym_pause = lpa & LPA_PAUSE_ASYM ? 1 : 0;
		}
	} else {
		int bmcr = phy_read(phydev, MII_BMCR);

		if (bmcr < 0)
			return bmcr;

		if (bmcr & BMCR_FULLDPLX)
			phydev->duplex = DUPLEX_FULL;
		else
			phydev->duplex = DUPLEX_HALF;

		if (bmcr & BMCR_SPEED1000)
			phydev->speed = SPEED_1000;
		else if (bmcr & BMCR_SPEED100)
			phydev->speed = SPEED_100;
		else
			phydev->speed = SPEED_10;

		phydev->pause = phydev->asym_pause = 0;
	}

	return 0;
}