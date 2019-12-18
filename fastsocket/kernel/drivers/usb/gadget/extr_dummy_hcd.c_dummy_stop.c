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
struct dummy {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_urbs ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy*) ; 
 struct dummy* hcd_to_dummy (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_gadget_unregister_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dummy_stop (struct usb_hcd *hcd)
{
	struct dummy		*dum;

	dum = hcd_to_dummy (hcd);

	device_remove_file (dummy_dev(dum), &dev_attr_urbs);
	usb_gadget_unregister_driver (dum->driver);
	dev_info (dummy_dev(dum), "stopped\n");
}