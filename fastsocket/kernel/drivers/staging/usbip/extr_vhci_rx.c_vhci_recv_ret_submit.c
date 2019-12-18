#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbip_device {int dummy; } ;
struct vhci_device {struct usbip_device ud; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_1__ base; } ;
struct urb {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  seqnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_RET_SUBMIT ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_TCP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct urb* pickup_urb_and_free_priv (struct vhci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* the_controller ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 scalar_t__ usbip_dbg_flag_vhci_rx ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rx (char*,...) ; 
 int /*<<< orphan*/  usbip_dump_urb (struct urb*) ; 
 int /*<<< orphan*/  usbip_event_add (struct usbip_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pack_pdu (struct usbip_header*,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbip_recv_iso (struct usbip_device*,struct urb*) ; 
 scalar_t__ usbip_recv_xbuff (struct usbip_device*,struct urb*) ; 
 int /*<<< orphan*/  usbip_uerr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhci_to_hcd (TYPE_2__*) ; 

__attribute__((used)) static void vhci_recv_ret_submit(struct vhci_device *vdev,
						struct usbip_header *pdu)
{
	struct usbip_device *ud = &vdev->ud;
	struct urb *urb;


	urb = pickup_urb_and_free_priv(vdev, pdu->base.seqnum);


	if (!urb) {
		usbip_uerr("cannot find a urb of seqnum %u\n",
							pdu->base.seqnum);
		usbip_uinfo("max seqnum %d\n",
					atomic_read(&the_controller->seqnum));
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		return;
	}


	/* unpack the pdu to a urb */
	usbip_pack_pdu(pdu, urb, USBIP_RET_SUBMIT, 0);


	/* recv transfer buffer */
	if (usbip_recv_xbuff(ud, urb) < 0)
		return;


	/* recv iso_packet_descriptor */
	if (usbip_recv_iso(ud, urb) < 0)
		return;


	if (usbip_dbg_flag_vhci_rx)
		usbip_dump_urb(urb);


	usbip_dbg_vhci_rx("now giveback urb %p\n", urb);

	spin_lock(&the_controller->lock);
	usb_hcd_unlink_urb_from_ep(vhci_to_hcd(the_controller), urb);
	spin_unlock(&the_controller->lock);

	usb_hcd_giveback_urb(vhci_to_hcd(the_controller), urb, urb->status);


	usbip_dbg_vhci_rx("Leave\n");

	return;
}