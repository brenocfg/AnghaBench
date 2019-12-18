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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_hcd {TYPE_1__* driver; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* endpoint_reset ) (struct usb_hcd*,struct usb_host_endpoint*) ;} ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_host_endpoint*) ; 
 int usb_endpoint_dir_out (int /*<<< orphan*/ *) ; 
 int usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_settoggle (struct usb_device*,int,int,int /*<<< orphan*/ ) ; 

void usb_hcd_reset_endpoint(struct usb_device *udev,
			    struct usb_host_endpoint *ep)
{
	struct usb_hcd *hcd = bus_to_hcd(udev->bus);

	if (hcd->driver->endpoint_reset)
		hcd->driver->endpoint_reset(hcd, ep);
	else {
		int epnum = usb_endpoint_num(&ep->desc);
		int is_out = usb_endpoint_dir_out(&ep->desc);
		int is_control = usb_endpoint_xfer_control(&ep->desc);

		usb_settoggle(udev, epnum, is_out, 0);
		if (is_control)
			usb_settoggle(udev, epnum, !is_out, 0);
	}
}