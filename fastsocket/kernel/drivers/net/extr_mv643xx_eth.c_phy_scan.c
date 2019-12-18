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
struct phy_device {int dummy; } ;
struct mv643xx_eth_private {TYPE_1__* shared; } ;
struct mii_bus {struct phy_device** phy_map; } ;
struct TYPE_4__ {struct mii_bus* smi_bus; } ;
struct TYPE_3__ {TYPE_2__* smi; } ;

/* Variables and functions */
 int MV643XX_ETH_PHY_ADDR_DEFAULT ; 
 int /*<<< orphan*/  mdiobus_scan (struct mii_bus*,int) ; 
 int phy_addr_get (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  phy_addr_set (struct mv643xx_eth_private*,int) ; 

__attribute__((used)) static struct phy_device *phy_scan(struct mv643xx_eth_private *mp,
				   int phy_addr)
{
	struct mii_bus *bus = mp->shared->smi->smi_bus;
	struct phy_device *phydev;
	int start;
	int num;
	int i;

	if (phy_addr == MV643XX_ETH_PHY_ADDR_DEFAULT) {
		start = phy_addr_get(mp) & 0x1f;
		num = 32;
	} else {
		start = phy_addr & 0x1f;
		num = 1;
	}

	phydev = NULL;
	for (i = 0; i < num; i++) {
		int addr = (start + i) & 0x1f;

		if (bus->phy_map[addr] == NULL)
			mdiobus_scan(bus, addr);

		if (phydev == NULL) {
			phydev = bus->phy_map[addr];
			if (phydev != NULL)
				phy_addr_set(mp, addr);
		}
	}

	return phydev;
}