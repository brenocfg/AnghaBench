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
struct superhyway_driver {struct superhyway_device_id* id_table; } ;
struct superhyway_device_id {int dummy; } ;
struct superhyway_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ superhyway_match_id (struct superhyway_device_id const*,struct superhyway_device*) ; 
 struct superhyway_device* to_superhyway_device (struct device*) ; 
 struct superhyway_driver* to_superhyway_driver (struct device_driver*) ; 

__attribute__((used)) static int superhyway_bus_match(struct device *dev, struct device_driver *drv)
{
	struct superhyway_device *shyway_dev = to_superhyway_device(dev);
	struct superhyway_driver *shyway_drv = to_superhyway_driver(drv);
	const struct superhyway_device_id *ids = shyway_drv->id_table;

	if (!ids)
		return -EINVAL;
	if (superhyway_match_id(ids, shyway_dev))
		return 1;

	return -ENODEV;
}