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
struct usb_sevsegdev {int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_grp ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_sevsegdev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sevseg_disconnect(struct usb_interface *interface)
{
	struct usb_sevsegdev *mydev;

	mydev = usb_get_intfdata(interface);
	sysfs_remove_group(&interface->dev.kobj, &dev_attr_grp);
	usb_set_intfdata(interface, NULL);
	usb_put_dev(mydev->udev);
	kfree(mydev);
	dev_info(&interface->dev, "USB 7 Segment now disconnected\n");
}