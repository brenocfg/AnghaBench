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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct stub_device {int /*<<< orphan*/  ud; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_EVENT_REMOVED ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  stub_device_free (struct stub_device*) ; 
 int /*<<< orphan*/  stub_remove_files (int /*<<< orphan*/ *) ; 
 struct stub_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_stop_eh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_udbg (char*) ; 

__attribute__((used)) static void stub_disconnect(struct usb_interface *interface)
{
	struct stub_device *sdev = usb_get_intfdata(interface);

	usbip_udbg("Enter\n");

	/* get stub_device */
	if (!sdev) {
		err(" could not get device from inteface data");
		/* BUG(); */
		return;
	}

	usb_set_intfdata(interface, NULL);


	/*
	 * NOTE:
	 * rx/tx threads are invoked for each usb_device.
	 */
	stub_remove_files(&interface->dev);

	/* 1. shutdown the current connection */
	usbip_event_add(&sdev->ud, SDEV_EVENT_REMOVED);

	/* 2. wait for the stop of the event handler */
	usbip_stop_eh(&sdev->ud);

	/* 3. free sdev */
	stub_device_free(sdev);


	usbip_udbg("bye\n");
}