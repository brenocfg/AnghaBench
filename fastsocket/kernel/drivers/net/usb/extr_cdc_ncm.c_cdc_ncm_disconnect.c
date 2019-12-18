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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_disconnect (struct usb_interface*) ; 

__attribute__((used)) static void cdc_ncm_disconnect(struct usb_interface *intf)
{
	struct usbnet *dev = usb_get_intfdata(intf);

	if (dev == NULL)
		return;		/* already disconnected */

	usbnet_disconnect(intf);
}