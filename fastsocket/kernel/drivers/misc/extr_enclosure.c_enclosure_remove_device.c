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
struct enclosure_device {int components; struct enclosure_component* component; } ;
struct enclosure_component {int /*<<< orphan*/  cdev; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enclosure_remove_links (struct enclosure_component*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

int enclosure_remove_device(struct enclosure_device *edev, struct device *dev)
{
	struct enclosure_component *cdev;
	int i;

	if (!edev || !dev)
		return -EINVAL;

	for (i = 0; i < edev->components; i++) {
		cdev = &edev->component[i];
		if (cdev->dev == dev) {
			enclosure_remove_links(cdev);
			device_del(&cdev->cdev);
			put_device(dev);
			cdev->dev = NULL;
			return device_add(&cdev->cdev);
		}
	}
	return -ENODEV;
}