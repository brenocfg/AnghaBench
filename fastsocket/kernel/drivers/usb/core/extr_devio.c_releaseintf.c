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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct dev_state {int /*<<< orphan*/  ifclaimed; struct usb_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ test_and_clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,unsigned int) ; 
 int /*<<< orphan*/  usbfs_driver ; 

__attribute__((used)) static int releaseintf(struct dev_state *ps, unsigned int ifnum)
{
	struct usb_device *dev;
	struct usb_interface *intf;
	int err;

	err = -EINVAL;
	if (ifnum >= 8*sizeof(ps->ifclaimed))
		return err;
	dev = ps->dev;
	intf = usb_ifnum_to_if(dev, ifnum);
	if (!intf)
		err = -ENOENT;
	else if (test_and_clear_bit(ifnum, &ps->ifclaimed)) {
		usb_driver_release_interface(&usbfs_driver, intf);
		err = 0;
	}
	return err;
}