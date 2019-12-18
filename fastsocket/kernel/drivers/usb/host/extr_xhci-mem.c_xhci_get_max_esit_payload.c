#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xhci_hcd {int dummy; } ;
struct TYPE_7__ {int wMaxPacketSize; } ;
struct usb_host_endpoint {TYPE_3__ desc; TYPE_2__* ss_ep_comp; } ;
struct usb_device {scalar_t__ speed; } ;
struct TYPE_5__ {int wBytesPerInterval; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int GET_MAX_PACKET (int) ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int le16_to_cpu (int) ; 
 scalar_t__ usb_endpoint_xfer_bulk (TYPE_3__*) ; 
 scalar_t__ usb_endpoint_xfer_control (TYPE_3__*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static u32 xhci_get_max_esit_payload(struct xhci_hcd *xhci,
		struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	int max_burst;
	int max_packet;

	/* Only applies for interrupt or isochronous endpoints */
	if (usb_endpoint_xfer_control(&ep->desc) ||
			usb_endpoint_xfer_bulk(&ep->desc))
		return 0;

	if (udev->speed == USB_SPEED_SUPER) {
		if (ep->ss_ep_comp)
			return le16_to_cpu(ep->ss_ep_comp->desc.wBytesPerInterval);
		xhci_warn(xhci, "WARN no SS endpoint companion descriptor.\n");
		/* Assume no bursts, no multiple opportunities to send. */
		return ep->desc.wMaxPacketSize;
	}

	max_packet = GET_MAX_PACKET(le16_to_cpu(ep->desc.wMaxPacketSize));
	max_burst = (le16_to_cpu(ep->desc.wMaxPacketSize) & 0x1800) >> 11;
	/* A 0 in max burst means 1 transfer per ESIT */
	return max_packet * (max_burst + 1);
}