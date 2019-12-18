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
struct umc_driver {scalar_t__ cap_id; int (* match ) (struct umc_driver*,struct umc_dev*) ;} ;
struct umc_dev {scalar_t__ cap_id; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int stub1 (struct umc_driver*,struct umc_dev*) ; 
 struct umc_dev* to_umc_dev (struct device*) ; 
 struct umc_driver* to_umc_driver (struct device_driver*) ; 

__attribute__((used)) static int umc_bus_match(struct device *dev, struct device_driver *drv)
{
	struct umc_dev *umc = to_umc_dev(dev);
	struct umc_driver *umc_driver = to_umc_driver(drv);

	if (umc->cap_id == umc_driver->cap_id) {
		if (umc_driver->match)
			return umc_driver->match(umc_driver, umc);
		else
			return 1;
	}
	return 0;
}