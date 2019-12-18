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
struct phy_driver {int (* suspend ) (struct phy_device*) ;} ;
struct phy_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mdio_bus_phy_may_suspend (struct phy_device*) ; 
 int stub1 (struct phy_device*) ; 
 struct phy_device* to_phy_device (struct device*) ; 
 struct phy_driver* to_phy_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_bus_suspend(struct device * dev, pm_message_t state)
{
	struct phy_driver *phydrv = to_phy_driver(dev->driver);
	struct phy_device *phydev = to_phy_device(dev);

	if (!mdio_bus_phy_may_suspend(phydev))
		return 0;
	return phydrv->suspend(phydev);
}