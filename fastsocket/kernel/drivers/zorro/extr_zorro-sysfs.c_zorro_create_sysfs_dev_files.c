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
struct device {int /*<<< orphan*/  kobj; } ;
struct zorro_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_id ; 
 int /*<<< orphan*/  dev_attr_resource ; 
 int /*<<< orphan*/  dev_attr_serial ; 
 int /*<<< orphan*/  dev_attr_slotaddr ; 
 int /*<<< orphan*/  dev_attr_slotsize ; 
 int /*<<< orphan*/  dev_attr_type ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zorro_config_attr ; 

int zorro_create_sysfs_dev_files(struct zorro_dev *z)
{
	struct device *dev = &z->dev;
	int error;

	/* current configuration's attributes */
	if ((error = device_create_file(dev, &dev_attr_id)) ||
	    (error = device_create_file(dev, &dev_attr_type)) ||
	    (error = device_create_file(dev, &dev_attr_serial)) ||
	    (error = device_create_file(dev, &dev_attr_slotaddr)) ||
	    (error = device_create_file(dev, &dev_attr_slotsize)) ||
	    (error = device_create_file(dev, &dev_attr_resource)) ||
	    (error = sysfs_create_bin_file(&dev->kobj, &zorro_config_attr)))
		return error;

	return 0;
}