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
struct sir_dev {struct dongle_driver* dongle_drv; } ;
struct dongle_driver {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* close ) (struct sir_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sir_dev*) ; 

int sirdev_put_dongle(struct sir_dev *dev)
{
	const struct dongle_driver *drv = dev->dongle_drv;

	if (drv) {
		if (drv->close)
			drv->close(dev);		/* close this dongle instance */

		dev->dongle_drv = NULL;			/* unlink the dongle driver */
		module_put(drv->owner);/* decrement driver's module refcount */
	}

	return 0;
}