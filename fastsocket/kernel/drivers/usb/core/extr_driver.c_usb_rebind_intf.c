#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; } ;
struct TYPE_6__ {TYPE_1__ power; int /*<<< orphan*/  driver; } ;
struct usb_interface {TYPE_2__ dev; scalar_t__ needs_binding; } ;
struct usb_driver {int dummy; } ;

/* Variables and functions */
 scalar_t__ DPM_ON ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 int device_attach (TYPE_2__*) ; 
 struct usb_driver* to_usb_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 

void usb_rebind_intf(struct usb_interface *intf)
{
	int rc;

	/* Delayed unbind of an existing driver */
	if (intf->dev.driver) {
		struct usb_driver *driver =
				to_usb_driver(intf->dev.driver);

		dev_dbg(&intf->dev, "forced unbind\n");
		usb_driver_release_interface(driver, intf);
	}

	/* Try to rebind the interface */
	if (intf->dev.power.status == DPM_ON) {
		intf->needs_binding = 0;
		rc = device_attach(&intf->dev);
		if (rc < 0)
			dev_warn(&intf->dev, "rebind failed: %d\n", rc);
	}
}