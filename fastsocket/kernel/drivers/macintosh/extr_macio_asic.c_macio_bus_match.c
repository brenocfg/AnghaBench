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
struct of_device_id {int dummy; } ;
struct macio_driver {struct of_device_id* match_table; } ;
struct macio_dev {int /*<<< orphan*/  ofdev; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * of_match_device (struct of_device_id const*,int /*<<< orphan*/ *) ; 
 struct macio_dev* to_macio_device (struct device*) ; 
 struct macio_driver* to_macio_driver (struct device_driver*) ; 

__attribute__((used)) static int macio_bus_match(struct device *dev, struct device_driver *drv) 
{
	struct macio_dev * macio_dev = to_macio_device(dev);
	struct macio_driver * macio_drv = to_macio_driver(drv);
	const struct of_device_id * matches = macio_drv->match_table;

	if (!matches) 
		return 0;

	return of_match_device(matches, &macio_dev->ofdev) != NULL;
}