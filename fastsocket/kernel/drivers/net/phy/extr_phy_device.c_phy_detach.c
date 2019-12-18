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
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;
struct phy_device {TYPE_2__ dev; int /*<<< orphan*/ * attached_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver (TYPE_2__*) ; 
 TYPE_1__ genphy_driver ; 

void phy_detach(struct phy_device *phydev)
{
	phydev->attached_dev = NULL;

	/* If the device had no specific driver before (i.e. - it
	 * was using the generic driver), we unbind the device
	 * from the generic driver so that there's a chance a
	 * real driver could be loaded */
	if (phydev->dev.driver == &genphy_driver.driver)
		device_release_driver(&phydev->dev);
}