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
struct of_platform_driver {int (* suspend ) (struct of_device*,int /*<<< orphan*/ ) ;} ;
struct of_device {int dummy; } ;
struct device {scalar_t__ driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int stub1 (struct of_device*,int /*<<< orphan*/ ) ; 
 struct of_device* to_of_device (struct device*) ; 
 struct of_platform_driver* to_of_platform_driver (scalar_t__) ; 

__attribute__((used)) static int of_platform_device_suspend(struct device *dev, pm_message_t state)
{
	struct of_device *of_dev = to_of_device(dev);
	struct of_platform_driver *drv = to_of_platform_driver(dev->driver);
	int error = 0;

	if (dev->driver && drv->suspend)
		error = drv->suspend(of_dev, state);
	return error;
}