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
struct wacom_features {int dummy; } ;
struct wacom {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; scalar_t__ open; TYPE_1__* wacom_wac; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {struct wacom_features* features; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wacom* usb_get_intfdata (struct usb_interface*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_led_control (struct wacom*) ; 
 int /*<<< orphan*/  wacom_query_tablet_data (struct usb_interface*,struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_retrieve_hid_descriptor (struct usb_interface*,struct wacom_features*) ; 

__attribute__((used)) static int wacom_resume(struct usb_interface *intf)
{
	struct wacom *wacom = usb_get_intfdata(intf);
	struct wacom_features *features = wacom->wacom_wac->features;
	int rv = 0;

	mutex_lock(&wacom->lock);

	/* switch to wacom mode if needed */
	if (!wacom_retrieve_hid_descriptor(intf, features))
		wacom_query_tablet_data(intf, features);
	wacom_led_control(wacom);

	if (wacom->open && usb_submit_urb(wacom->irq, GFP_NOIO) < 0)
		rv = -EIO;

	mutex_unlock(&wacom->lock);

	return rv;
}