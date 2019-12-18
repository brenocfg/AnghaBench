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
struct i2o_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (struct i2o_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static void i2o_device_release(struct device *dev)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);

	pr_debug("i2o: device %s released\n", dev_name(dev));

	kfree(i2o_dev);
}