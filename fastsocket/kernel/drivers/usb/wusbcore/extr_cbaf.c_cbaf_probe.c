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
struct usb_interface {struct device dev; } ;
struct usb_device_id {int dummy; } ;
struct cbaf {int buffer_size; struct cbaf* buffer; int /*<<< orphan*/  usb_iface; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cbaf_check (struct cbaf*) ; 
 int /*<<< orphan*/  cbaf_dev_attr_group ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct cbaf*) ; 
 struct cbaf* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct cbaf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct cbaf*) ; 

__attribute__((used)) static int cbaf_probe(struct usb_interface *iface,
		      const struct usb_device_id *id)
{
	struct cbaf *cbaf;
	struct device *dev = &iface->dev;
	int result = -ENOMEM;

	cbaf = kzalloc(sizeof(*cbaf), GFP_KERNEL);
	if (cbaf == NULL)
		goto error_kzalloc;
	cbaf->buffer = kmalloc(512, GFP_KERNEL);
	if (cbaf->buffer == NULL)
		goto error_kmalloc_buffer;

	cbaf->buffer_size = 512;
	cbaf->usb_dev = usb_get_dev(interface_to_usbdev(iface));
	cbaf->usb_iface = usb_get_intf(iface);
	result = cbaf_check(cbaf);
	if (result < 0) {
		dev_err(dev, "This device is not WUSB-CBAF compliant"
			"and is not supported yet.\n");
		goto error_check;
	}

	result = sysfs_create_group(&dev->kobj, &cbaf_dev_attr_group);
	if (result < 0) {
		dev_err(dev, "Can't register sysfs attr group: %d\n", result);
		goto error_create_group;
	}
	usb_set_intfdata(iface, cbaf);
	return 0;

error_create_group:
error_check:
	kfree(cbaf->buffer);
error_kmalloc_buffer:
	kfree(cbaf);
error_kzalloc:
	return result;
}