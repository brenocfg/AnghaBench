#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct device {TYPE_1__* driver; } ;
struct phy_device {TYPE_2__* drv; int /*<<< orphan*/  interface; int /*<<< orphan*/  dev_flags; struct net_device* attached_dev; struct device dev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_4__ {int (* probe ) (struct device*) ;} ;
struct TYPE_6__ {TYPE_1__ driver; } ;
struct TYPE_5__ {int (* config_init ) (struct phy_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_bind_driver (struct device*) ; 
 TYPE_3__ genphy_driver ; 
 int phy_scan_fixups (struct phy_device*) ; 
 int stub1 (struct device*) ; 
 int stub2 (struct phy_device*) ; 

int phy_attach_direct(struct net_device *dev, struct phy_device *phydev,
		      u32 flags, phy_interface_t interface)
{
	struct device *d = &phydev->dev;

	/* Assume that if there is no driver, that it doesn't
	 * exist, and we should use the genphy driver. */
	if (NULL == d->driver) {
		int err;
		d->driver = &genphy_driver.driver;

		err = d->driver->probe(d);
		if (err >= 0)
			err = device_bind_driver(d);

		if (err)
			return err;
	}

	if (phydev->attached_dev) {
		dev_err(&dev->dev, "PHY already attached\n");
		return -EBUSY;
	}

	phydev->attached_dev = dev;

	phydev->dev_flags = flags;

	phydev->interface = interface;

	/* Do initial configuration here, now that
	 * we have certain key parameters
	 * (dev_flags and interface) */
	if (phydev->drv->config_init) {
		int err;

		err = phy_scan_fixups(phydev);

		if (err < 0)
			return err;

		err = phydev->drv->config_init(phydev);

		if (err < 0)
			return err;
	}

	return 0;
}