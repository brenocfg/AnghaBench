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
struct tg3 {int phy_flags; TYPE_1__* mdio_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/ * phy_map; } ;

/* Variables and functions */
 int TG3_PHYFLG_IS_CONNECTED ; 
 size_t TG3_PHY_MII_ADDR ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_phy_stop(struct tg3 *tp)
{
	if (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
		return;

	phy_stop(tp->mdio_bus->phy_map[TG3_PHY_MII_ADDR]);
}