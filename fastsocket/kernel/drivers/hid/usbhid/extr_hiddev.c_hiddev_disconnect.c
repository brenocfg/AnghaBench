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
struct usbhid_device {int /*<<< orphan*/  intf; } ;
struct hiddev {int /*<<< orphan*/  wait; TYPE_1__* hid; scalar_t__ open; int /*<<< orphan*/  existancelock; scalar_t__ exist; } ;
struct hid_device {struct usbhid_device* driver_data; struct hiddev* hiddev; } ;
struct TYPE_2__ {size_t minor; } ;

/* Variables and functions */
 size_t HIDDEV_MINOR_BASE ; 
 int /*<<< orphan*/  hiddev_class ; 
 int /*<<< orphan*/ ** hiddev_table ; 
 int /*<<< orphan*/  kfree (struct hiddev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbhid_close (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hiddev_disconnect(struct hid_device *hid)
{
	struct hiddev *hiddev = hid->hiddev;
	struct usbhid_device *usbhid = hid->driver_data;

	mutex_lock(&hiddev->existancelock);
	hiddev->exist = 0;
	mutex_unlock(&hiddev->existancelock);

	hiddev_table[hiddev->hid->minor - HIDDEV_MINOR_BASE] = NULL;
	usb_deregister_dev(usbhid->intf, &hiddev_class);

	if (hiddev->open) {
		usbhid_close(hiddev->hid);
		wake_up_interruptible(&hiddev->wait);
	} else {
		kfree(hiddev);
	}
}