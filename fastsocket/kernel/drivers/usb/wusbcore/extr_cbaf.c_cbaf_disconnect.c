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
struct cbaf {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbaf_dev_attr_group ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct cbaf*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cbaf* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbaf_disconnect(struct usb_interface *iface)
{
	struct cbaf *cbaf = usb_get_intfdata(iface);
	struct device *dev = &iface->dev;
	sysfs_remove_group(&dev->kobj, &cbaf_dev_attr_group);
	usb_set_intfdata(iface, NULL);
	usb_put_intf(iface);
	kfree(cbaf->buffer);
	/* paranoia: clean up crypto keys */
	kzfree(cbaf);
}