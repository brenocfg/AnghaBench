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
struct usb_hcd {int dummy; } ;
struct usb_device {struct usb_device* serial; struct usb_device* manufacturer; struct usb_device* product; int /*<<< orphan*/  bus; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_device*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int /*<<< orphan*/  usb_destroy_configuration (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_release_bos_descriptor (struct usb_device*) ; 

__attribute__((used)) static void usb_release_dev(struct device *dev)
{
	struct usb_device *udev;
	struct usb_hcd *hcd;

	udev = to_usb_device(dev);
	hcd = bus_to_hcd(udev->bus);

	usb_destroy_configuration(udev);
	usb_release_bos_descriptor(udev);
	usb_put_hcd(hcd);
	kfree(udev->product);
	kfree(udev->manufacturer);
	kfree(udev->serial);
	kfree(udev);
}