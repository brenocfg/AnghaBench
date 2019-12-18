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
struct TYPE_2__ {scalar_t__ bInterval; } ;
struct usb_host_endpoint {TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 unsigned int xhci_microframes_to_exponent (struct usb_device*,struct usb_host_endpoint*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int xhci_parse_microframe_interval(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	if (ep->desc.bInterval == 0)
		return 0;
	return xhci_microframes_to_exponent(udev, ep,
			ep->desc.bInterval, 0, 15);
}