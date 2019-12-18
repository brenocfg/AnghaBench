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
struct vstusb_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  submitted; scalar_t__ present; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct vstusb_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_vstusb_class ; 
 int /*<<< orphan*/  vstusb_delete ; 

__attribute__((used)) static void vstusb_disconnect(struct usb_interface *intf)
{
	struct vstusb_device *vstdev = usb_get_intfdata(intf);

	usb_deregister_dev(intf, &usb_vstusb_class);
	usb_set_intfdata(intf, NULL);

	if (vstdev) {

		mutex_lock(&vstdev->lock);
		vstdev->present = 0;

		usb_kill_anchored_urbs(&vstdev->submitted);

		mutex_unlock(&vstdev->lock);

		kref_put(&vstdev->kref, vstusb_delete);
	}

}