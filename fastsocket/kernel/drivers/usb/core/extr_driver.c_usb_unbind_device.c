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
struct usb_device_driver {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 
 struct usb_device_driver* to_usb_device_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_unbind_device(struct device *dev)
{
	struct usb_device_driver *udriver = to_usb_device_driver(dev->driver);

	udriver->disconnect(to_usb_device(dev));
	return 0;
}