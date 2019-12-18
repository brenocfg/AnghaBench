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
struct us_data {int /*<<< orphan*/  pusb_dev; int /*<<< orphan*/  dflags; int /*<<< orphan*/  pusb_intf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  US_FLIDX_DISCONNECTING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_lock_device_for_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 

int usb_stor_port_reset(struct us_data *us)
{
	int result;

	result = usb_lock_device_for_reset(us->pusb_dev, us->pusb_intf);
	if (result < 0)
		US_DEBUGP("unable to lock device for reset: %d\n", result);
	else {
		/* Were we disconnected while waiting for the lock? */
		if (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) {
			result = -EIO;
			US_DEBUGP("No reset during disconnect\n");
		} else {
			result = usb_reset_device(us->pusb_dev);
			US_DEBUGP("usb_reset_device returns %d\n",
					result);
		}
		usb_unlock_device(us->pusb_dev);
	}
	return result;
}