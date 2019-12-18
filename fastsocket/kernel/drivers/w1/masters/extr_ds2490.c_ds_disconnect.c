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
struct usb_interface {int dummy; } ;
struct ds_device {int /*<<< orphan*/  udev; int /*<<< orphan*/  ds_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_mutex ; 
 int /*<<< orphan*/  ds_w1_fini (struct ds_device*) ; 
 int /*<<< orphan*/  kfree (struct ds_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ds_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds_disconnect(struct usb_interface *intf)
{
	struct ds_device *dev;

	dev = usb_get_intfdata(intf);
	if (!dev)
		return;

	mutex_lock(&ds_mutex);
	list_del(&dev->ds_entry);
	mutex_unlock(&ds_mutex);

	ds_w1_fini(dev);

	usb_set_intfdata(intf, NULL);

	usb_put_dev(dev->udev);
	kfree(dev);
}