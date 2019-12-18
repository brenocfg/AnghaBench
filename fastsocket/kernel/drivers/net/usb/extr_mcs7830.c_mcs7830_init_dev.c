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
struct usbnet {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int mcs7830_get_address (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_rev_C_fixup (struct usbnet*) ; 
 int mcs7830_set_autoneg (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs7830_init_dev(struct usbnet *dev)
{
	int ret;
	int retry;

	/* Read MAC address from EEPROM */
	ret = -EINVAL;
	for (retry = 0; retry < 5 && ret; retry++)
		ret = mcs7830_get_address(dev);
	if (ret) {
		dev_warn(&dev->udev->dev, "Cannot read MAC address\n");
		goto out;
	}

	/* Set up PHY */
	ret = mcs7830_set_autoneg(dev, 0);
	if (ret) {
		dev_info(&dev->udev->dev, "Cannot set autoneg\n");
		goto out;
	}

	mcs7830_rev_C_fixup(dev);
	ret = 0;
out:
	return ret;
}