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
struct usb_device {int portnum; int devnum; scalar_t__ wusb; struct usb_bus* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  devicemap; } ;
struct usb_bus {int devnum_next; TYPE_1__ devmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void choose_devnum(struct usb_device *udev)
{
	int		devnum;
	struct usb_bus	*bus = udev->bus;

	/* If khubd ever becomes multithreaded, this will need a lock */
	if (udev->wusb) {
		devnum = udev->portnum + 1;
		BUG_ON(test_bit(devnum, bus->devmap.devicemap));
	} else {
		/* Try to allocate the next devnum beginning at
		 * bus->devnum_next. */
		devnum = find_next_zero_bit(bus->devmap.devicemap, 128,
					    bus->devnum_next);
		if (devnum >= 128)
			devnum = find_next_zero_bit(bus->devmap.devicemap,
						    128, 1);
		bus->devnum_next = ( devnum >= 127 ? 1 : devnum + 1);
	}
	if (devnum < 128) {
		set_bit(devnum, bus->devmap.devicemap);
		udev->devnum = devnum;
	}
}