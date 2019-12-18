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
struct TYPE_2__ {int match_flags; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;

/* Variables and functions */
 int USB_DEVICE_ID_MATCH_PRODUCT ; 
 int USB_DEVICE_ID_MATCH_VENDOR ; 
 int debug ; 
 TYPE_1__* generic_device_ids ; 
 int /*<<< orphan*/  generic_driver ; 
 int /*<<< orphan*/  product ; 
 int usb_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_serial_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_serial_generic_device ; 
 int usb_serial_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vendor ; 

int usb_serial_generic_register(int _debug)
{
	int retval = 0;

	debug = _debug;
#ifdef CONFIG_USB_SERIAL_GENERIC
	generic_device_ids[0].idVendor = vendor;
	generic_device_ids[0].idProduct = product;
	generic_device_ids[0].match_flags =
		USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT;

	/* register our generic driver with ourselves */
	retval = usb_serial_register(&usb_serial_generic_device);
	if (retval)
		goto exit;
	retval = usb_register(&generic_driver);
	if (retval)
		usb_serial_deregister(&usb_serial_generic_device);
exit:
#endif
	return retval;
}