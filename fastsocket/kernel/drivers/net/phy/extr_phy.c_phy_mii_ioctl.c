#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct phy_device {int advertising; TYPE_1__* drv; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  addr; } ;
struct mii_ioctl_data {int val_in; int const reg_num; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* config_init ) (struct phy_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EOPNOTSUPP ; 
#define  MII_ADVERTISE 132 
#define  MII_BMCR 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int const) ; 
 int /*<<< orphan*/  phy_scan_fixups (struct phy_device*) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int const,int) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*) ; 

int phy_mii_ioctl(struct phy_device *phydev,
		struct mii_ioctl_data *mii_data, int cmd)
{
	u16 val = mii_data->val_in;

	switch (cmd) {
	case SIOCGMIIPHY:
		mii_data->phy_id = phydev->addr;
		/* fall through */

	case SIOCGMIIREG:
		mii_data->val_out = phy_read(phydev, mii_data->reg_num);
		break;

	case SIOCSMIIREG:
		if (mii_data->phy_id == phydev->addr) {
			switch(mii_data->reg_num) {
			case MII_BMCR:
				if ((val & (BMCR_RESET|BMCR_ANENABLE)) == 0)
					phydev->autoneg = AUTONEG_DISABLE;
				else
					phydev->autoneg = AUTONEG_ENABLE;
				if ((!phydev->autoneg) && (val & BMCR_FULLDPLX))
					phydev->duplex = DUPLEX_FULL;
				else
					phydev->duplex = DUPLEX_HALF;
				if ((!phydev->autoneg) &&
						(val & BMCR_SPEED1000))
					phydev->speed = SPEED_1000;
				else if ((!phydev->autoneg) &&
						(val & BMCR_SPEED100))
					phydev->speed = SPEED_100;
				break;
			case MII_ADVERTISE:
				phydev->advertising = val;
				break;
			default:
				/* do nothing */
				break;
			}
		}

		phy_write(phydev, mii_data->reg_num, val);
		
		if (mii_data->reg_num == MII_BMCR 
				&& val & BMCR_RESET
				&& phydev->drv->config_init) {
			phy_scan_fixups(phydev);
			phydev->drv->config_init(phydev);
		}
		break;

	default:
		return -EOPNOTSUPP;
	}

	return 0;
}