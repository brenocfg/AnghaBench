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
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;
struct usb_dt9812 {int /*<<< orphan*/  kref; TYPE_1__* slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt9812_delete ; 
 int /*<<< orphan*/  dt9812_mutex ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 struct usb_dt9812* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dt9812_disconnect(struct usb_interface *interface)
{
	struct usb_dt9812 *dev;
	int minor = interface->minor;

	down(&dt9812_mutex);
	dev = usb_get_intfdata(interface);
	if (dev->slot) {
		down(&dev->slot->mutex);
		dev->slot->usb = NULL;
		up(&dev->slot->mutex);
		dev->slot = NULL;
	}
	usb_set_intfdata(interface, NULL);
	up(&dt9812_mutex);

	/* queue final destruction */
	kref_put(&dev->kref, dt9812_delete);

	dev_info(&interface->dev, "USB Dt9812 #%d now disconnected\n", minor);
}