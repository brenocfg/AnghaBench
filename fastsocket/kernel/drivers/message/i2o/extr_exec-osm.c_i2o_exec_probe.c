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
struct i2o_device {TYPE_1__* iop; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct i2o_device* exec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_product_id ; 
 int /*<<< orphan*/  dev_attr_vendor_id ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int i2o_event_register (struct i2o_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2o_exec_driver ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static int i2o_exec_probe(struct device *dev)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);
	int rc;

	rc = i2o_event_register(i2o_dev, &i2o_exec_driver, 0, 0xffffffff);
	if (rc) goto err_out;

	rc = device_create_file(dev, &dev_attr_vendor_id);
	if (rc) goto err_evtreg;
	rc = device_create_file(dev, &dev_attr_product_id);
	if (rc) goto err_vid;

	i2o_dev->iop->exec = i2o_dev;

	return 0;

err_vid:
	device_remove_file(dev, &dev_attr_vendor_id);
err_evtreg:
	i2o_event_register(to_i2o_device(dev), &i2o_exec_driver, 0, 0);
err_out:
	return rc;
}