#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct tg3 {int phy_flags; TYPE_1__ link_config; TYPE_2__* mdio_bus; } ;
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int TG3_PHYFLG_IS_CONNECTED ; 
 int TG3_PHYFLG_IS_LOW_POWER ; 
 size_t TG3_PHY_MII_ADDR ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static void tg3_phy_start(struct tg3 *tp)
{
	struct phy_device *phydev;

	if (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
		return;

	phydev = tp->mdio_bus->phy_map[TG3_PHY_MII_ADDR];

	if (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER) {
		tp->phy_flags &= ~TG3_PHYFLG_IS_LOW_POWER;
		phydev->speed = tp->link_config.speed;
		phydev->duplex = tp->link_config.duplex;
		phydev->autoneg = tp->link_config.autoneg;
		phydev->advertising = tp->link_config.advertising;
	}

	phy_start(phydev);

	phy_start_aneg(phydev);
}