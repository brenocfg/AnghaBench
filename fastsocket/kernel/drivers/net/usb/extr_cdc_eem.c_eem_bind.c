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
struct usbnet {TYPE_1__* net; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hard_header_len; } ;

/* Variables and functions */
 scalar_t__ EEM_HEAD ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  driver_of (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ ,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int eem_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int status = 0;

	status = usbnet_get_endpoints(dev, intf);
	if (status < 0) {
		usb_set_intfdata(intf, NULL);
		usb_driver_release_interface(driver_of(intf), intf);
		return status;
	}

	/* no jumbogram (16K) support for now */

	dev->net->hard_header_len += EEM_HEAD + ETH_FCS_LEN;

	return 0;
}