#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tid; } ;
struct i2o_device {TYPE_1__ lct_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_scan ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static int i2o_bus_remove(struct device *dev)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);

	device_remove_file(dev, &dev_attr_scan);

	put_device(dev);

	osm_info("device removed (TID: %03x)\n", i2o_dev->lct_data.tid);

	return 0;
}