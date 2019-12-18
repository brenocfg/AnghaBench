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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_product_id ; 
 int /*<<< orphan*/  dev_attr_vendor_id ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2o_event_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_exec_driver ; 
 int /*<<< orphan*/  to_i2o_device (struct device*) ; 

__attribute__((used)) static int i2o_exec_remove(struct device *dev)
{
	device_remove_file(dev, &dev_attr_product_id);
	device_remove_file(dev, &dev_attr_vendor_id);

	i2o_event_register(to_i2o_device(dev), &i2o_exec_driver, 0, 0);

	return 0;
}