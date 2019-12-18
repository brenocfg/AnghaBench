#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_host_endpoint {TYPE_2__* ss_ep_comp; int /*<<< orphan*/  desc; } ;
struct usb_device {scalar_t__ speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  bmAttributes; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xhci_get_endpoint_mult(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	if (udev->speed != USB_SPEED_SUPER || !ep->ss_ep_comp ||
			!usb_endpoint_xfer_isoc(&ep->desc))
		return 0;
	return ep->ss_ep_comp->desc.bmAttributes;
}