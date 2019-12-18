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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct c2port_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flash_access; int /*<<< orphan*/  access; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int __c2port_write_flash_erase (struct c2port_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct c2port_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t c2port_store_flash_erase(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct c2port_device *c2dev = dev_get_drvdata(dev);
	int ret;

	/* Check the device and flash access status */
	if (!c2dev->access || !c2dev->flash_access)
		return -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_write_flash_erase(c2dev);
	mutex_unlock(&c2dev->mutex);

	if (ret < 0) {
		dev_err(c2dev->dev, "cannot erase %s flash\n", c2dev->name);
		return ret;
	}

	return count;
}