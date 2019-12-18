#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vhci_unlink {int /*<<< orphan*/  unlink_seqnum; } ;
struct vhci_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_2__ ret_unlink; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_3__ u; TYPE_1__ base; } ;
struct urb {int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct vhci_unlink* dequeue_pending_unlink (struct vhci_device*,struct usbip_header*) ; 
 int /*<<< orphan*/  kfree (struct vhci_unlink*) ; 
 struct urb* pickup_urb_and_free_priv (struct vhci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* the_controller ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rx (char*,struct urb*) ; 
 int /*<<< orphan*/  usbip_dump_header (struct usbip_header*) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhci_to_hcd (TYPE_4__*) ; 

__attribute__((used)) static void vhci_recv_ret_unlink(struct vhci_device *vdev,
						struct usbip_header *pdu)
{
	struct vhci_unlink *unlink;
	struct urb *urb;

	usbip_dump_header(pdu);

	unlink = dequeue_pending_unlink(vdev, pdu);
	if (!unlink) {
		usbip_uinfo("cannot find the pending unlink %u\n",
							pdu->base.seqnum);
		return;
	}

	urb = pickup_urb_and_free_priv(vdev, unlink->unlink_seqnum);
	if (!urb) {
		/*
		 * I get the result of a unlink request. But, it seems that I
		 * already received the result of its submit result and gave
		 * back the URB.
		 */
		usbip_uinfo("the urb (seqnum %d) was already given backed\n",
							pdu->base.seqnum);
	} else {
		usbip_dbg_vhci_rx("now giveback urb %p\n", urb);

		/* If unlink is succeed, status is -ECONNRESET */
		urb->status = pdu->u.ret_unlink.status;
		usbip_uinfo("%d\n", urb->status);

		spin_lock(&the_controller->lock);
		usb_hcd_unlink_urb_from_ep(vhci_to_hcd(the_controller), urb);
		spin_unlock(&the_controller->lock);

		usb_hcd_giveback_urb(vhci_to_hcd(the_controller), urb,
								urb->status);
	}

	kfree(unlink);

	return;
}