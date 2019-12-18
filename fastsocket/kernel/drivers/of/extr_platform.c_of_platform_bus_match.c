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
struct of_platform_driver {struct of_device_id* match_table; } ;
struct of_device_id {int dummy; } ;
struct of_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * of_match_device (struct of_device_id const*,struct of_device*) ; 
 struct of_device* to_of_device (struct device*) ; 
 struct of_platform_driver* to_of_platform_driver (struct device_driver*) ; 

__attribute__((used)) static int of_platform_bus_match(struct device *dev, struct device_driver *drv)
{
	struct of_device *of_dev = to_of_device(dev);
	struct of_platform_driver *of_drv = to_of_platform_driver(drv);
	const struct of_device_id *matches = of_drv->match_table;

	if (!matches)
		return 0;

	return of_match_device(matches, of_dev) != NULL;
}