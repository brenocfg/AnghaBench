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
struct usb_interface {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_active ; 
 int /*<<< orphan*/  dev_attr_bank ; 
 int /*<<< orphan*/  dev_attr_dump ; 
 int /*<<< orphan*/  dev_attr_model ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  dev_attr_raw ; 
 int /*<<< orphan*/  dev_attr_raw2 ; 
 int /*<<< orphan*/  dev_attr_tone ; 
 int /*<<< orphan*/  dev_attr_volume ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  variax_destruct (struct usb_interface*) ; 
 int /*<<< orphan*/  variax_remove_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 

void variax_disconnect(struct usb_interface *interface)
{
	struct device *dev;

	if (interface == NULL)
		return;
	dev = &interface->dev;

	if (dev != NULL) {
		/* remove sysfs entries: */
		variax_remove_files(0, 0, dev);
		device_remove_file(dev, &dev_attr_model);
		device_remove_file(dev, &dev_attr_volume);
		device_remove_file(dev, &dev_attr_tone);
		device_remove_file(dev, &dev_attr_name);
		device_remove_file(dev, &dev_attr_bank);
		device_remove_file(dev, &dev_attr_dump);
		device_remove_file(dev, &dev_attr_active);
#if CREATE_RAW_FILE
		device_remove_file(dev, &dev_attr_raw);
		device_remove_file(dev, &dev_attr_raw2);
#endif
	}

	variax_destruct(interface);
}