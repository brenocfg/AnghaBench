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
struct tc_driver {int dummy; } ;
struct tc_device_id {int dummy; } ;
struct tc_dev {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tc_device_id* tc_match_device (struct tc_driver*,struct tc_dev*) ; 
 struct tc_dev* to_tc_dev (struct device*) ; 
 struct tc_driver* to_tc_driver (struct device_driver*) ; 

__attribute__((used)) static int tc_bus_match(struct device *dev, struct device_driver *drv)
{
	struct tc_dev *tdev = to_tc_dev(dev);
	struct tc_driver *tdrv = to_tc_driver(drv);
	const struct tc_device_id *id;

	id = tc_match_device(tdrv, tdev);
	if (id)
		return 1;

	return 0;
}