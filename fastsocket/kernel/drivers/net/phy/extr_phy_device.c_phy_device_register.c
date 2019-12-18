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
struct phy_device {size_t addr; TYPE_1__* bus; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_scan_fixups (struct phy_device*) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

int phy_device_register(struct phy_device *phydev)
{
	int err;

	/* Don't register a phy if one is already registered at this
	 * address */
	if (phydev->bus->phy_map[phydev->addr])
		return -EINVAL;
	phydev->bus->phy_map[phydev->addr] = phydev;

	/* Run all of the fixups for this PHY */
	phy_scan_fixups(phydev);

	err = device_register(&phydev->dev);
	if (err) {
		pr_err("phy %d failed to register\n", phydev->addr);
		goto out;
	}

	return 0;

 out:
	phydev->bus->phy_map[phydev->addr] = NULL;
	return err;
}