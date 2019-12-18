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
struct locomo_driver {int (* suspend ) (struct locomo_dev*,int /*<<< orphan*/ ) ;} ;
struct locomo_dev {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct locomo_dev* LOCOMO_DEV (struct device*) ; 
 struct locomo_driver* LOCOMO_DRV (int /*<<< orphan*/ ) ; 
 int stub1 (struct locomo_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int locomo_bus_suspend(struct device *dev, pm_message_t state)
{
	struct locomo_dev *ldev = LOCOMO_DEV(dev);
	struct locomo_driver *drv = LOCOMO_DRV(dev->driver);
	int ret = 0;

	if (drv && drv->suspend)
		ret = drv->suspend(ldev, state);
	return ret;
}