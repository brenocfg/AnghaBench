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
typedef  int u16 ;
struct ssb_device_id {int dummy; } ;
struct ssb_device {TYPE_1__* bus; } ;
struct TYPE_2__ {int chip_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ssb_ohci_attach (struct ssb_device*) ; 
 scalar_t__ usb_disabled () ; 

__attribute__((used)) static int ssb_ohci_probe(struct ssb_device *dev,
		const struct ssb_device_id *id)
{
	int err;
	u16 chipid_top;

	/* USBcores are only connected on embedded devices. */
	chipid_top = (dev->bus->chip_id & 0xFF00);
	if (chipid_top != 0x4700 && chipid_top != 0x5300)
		return -ENODEV;

	/* TODO: Probably need checks here; is the core connected? */

	if (usb_disabled())
		return -ENODEV;

	/* We currently always attach SSB_DEV_USB11_HOSTDEV
	 * as HOST OHCI. If we want to attach it as Client device,
	 * we must branch here and call into the (yet to
	 * be written) Client mode driver. Same for remove(). */

	err = ssb_ohci_attach(dev);

	return err;
}