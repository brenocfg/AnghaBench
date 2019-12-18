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
struct usb_device {int /*<<< orphan*/  devnum; TYPE_1__* bus; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static char *usb_devnode(struct device *dev, mode_t *mode)
{
	struct usb_device *usb_dev;

	usb_dev = to_usb_device(dev);
	return kasprintf(GFP_KERNEL, "bus/usb/%03d/%03d",
			 usb_dev->bus->busnum, usb_dev->devnum);
}