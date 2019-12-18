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
struct sa1111_driver {int (* suspend ) (struct sa1111_dev*,int /*<<< orphan*/ ) ;} ;
struct sa1111_dev {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct sa1111_dev* SA1111_DEV (struct device*) ; 
 struct sa1111_driver* SA1111_DRV (int /*<<< orphan*/ ) ; 
 int stub1 (struct sa1111_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1111_bus_suspend(struct device *dev, pm_message_t state)
{
	struct sa1111_dev *sadev = SA1111_DEV(dev);
	struct sa1111_driver *drv = SA1111_DRV(dev->driver);
	int ret = 0;

	if (drv && drv->suspend)
		ret = drv->suspend(sadev, state);
	return ret;
}