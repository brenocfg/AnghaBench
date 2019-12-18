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
struct superhyway_driver {int (* probe ) (struct superhyway_device*,struct superhyway_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct superhyway_device_id {int dummy; } ;
struct superhyway_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct superhyway_device*,struct superhyway_device_id const*) ; 
 struct superhyway_device_id* superhyway_match_id (int /*<<< orphan*/ ,struct superhyway_device*) ; 
 struct superhyway_device* to_superhyway_device (struct device*) ; 
 struct superhyway_driver* to_superhyway_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int superhyway_device_probe(struct device *dev)
{
	struct superhyway_device *shyway_dev = to_superhyway_device(dev);
	struct superhyway_driver *shyway_drv = to_superhyway_driver(dev->driver);

	if (shyway_drv && shyway_drv->probe) {
		const struct superhyway_device_id *id;

		id = superhyway_match_id(shyway_drv->id_table, shyway_dev);
		if (id)
			return shyway_drv->probe(shyway_dev, id);
	}

	return -ENODEV;
}