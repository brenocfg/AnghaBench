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
struct TYPE_3__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
typedef  size_t u32 ;
struct xhci_hcd {TYPE_2__** devs; } ;
struct usb_device {int /*<<< orphan*/  portnum; scalar_t__ parent; } ;
struct TYPE_4__ {struct usb_device* udev; } ;

/* Variables and functions */
 size_t TRB_TO_SLOT_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_wakeup_notification (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,size_t) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,size_t) ; 

__attribute__((used)) static void handle_device_notification(struct xhci_hcd *xhci,
		union xhci_trb *event)
{
	u32 slot_id;
	struct usb_device *udev;

	slot_id = TRB_TO_SLOT_ID(event->generic.field[3]);
	if (!xhci->devs[slot_id]) {
		xhci_warn(xhci, "Device Notification event for "
				"unused slot %u\n", slot_id);
		return;
	}

	xhci_dbg(xhci, "Device Wake Notification event for slot ID %u\n",
			slot_id);
	udev = xhci->devs[slot_id]->udev;
	if (udev && udev->parent)
		usb_wakeup_notification(udev->parent, udev->portnum);
}