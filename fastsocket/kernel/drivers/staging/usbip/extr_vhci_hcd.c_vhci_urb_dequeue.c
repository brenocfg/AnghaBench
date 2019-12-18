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
struct vhci_unlink {int seqnum; int /*<<< orphan*/  list; int /*<<< orphan*/  unlink_seqnum; } ;
struct vhci_priv {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  list; struct vhci_device* vdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tcp_socket; } ;
struct vhci_device {int /*<<< orphan*/  status; TYPE_2__ ud; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  unlink_tx; struct vhci_priv* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  status; TYPE_2__ ud; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  unlink_tx; struct vhci_priv* hcpriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  seqnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vhci_priv*) ; 
 struct vhci_unlink* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* the_controller ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct vhci_device*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct vhci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct vhci_device*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uerr (char*) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,...) ; 
 int /*<<< orphan*/  vhci_to_hcd (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	unsigned long flags;
	struct vhci_priv *priv;
	struct vhci_device *vdev;

	usbip_uinfo("vhci_hcd: dequeue a urb %p\n", urb);


	spin_lock_irqsave(&the_controller->lock, flags);

	priv = urb->hcpriv;
	if (!priv) {
		/* URB was never linked! or will be soon given back by
		 * vhci_rx. */
		spin_unlock_irqrestore(&the_controller->lock, flags);
		return 0;
	}

	{
		int ret = 0;
		ret = usb_hcd_check_unlink_urb(hcd, urb, status);
		if (ret) {
			spin_unlock_irqrestore(&the_controller->lock, flags);
			return ret;
		}
	}

	 /* send unlink request here? */
	vdev = priv->vdev;

	if (!vdev->ud.tcp_socket) {
		/* tcp connection is closed */
		unsigned long flags2;

		spin_lock_irqsave(&vdev->priv_lock, flags2);

		usbip_uinfo("vhci_hcd: device %p seems to be disconnected\n",
									vdev);
		list_del(&priv->list);
		kfree(priv);
		urb->hcpriv = NULL;

		spin_unlock_irqrestore(&vdev->priv_lock, flags2);

		/*
		 * If tcp connection is alive, we have sent CMD_UNLINK.
		 * vhci_rx will receive RET_UNLINK and give back the URB.
		 * Otherwise, we give back it here.
		 */
		usbip_uinfo("vhci_hcd: vhci_urb_dequeue() gives back urb %p\n",
									urb);

		usb_hcd_unlink_urb_from_ep(hcd, urb);

		spin_unlock_irqrestore(&the_controller->lock, flags);
		usb_hcd_giveback_urb(vhci_to_hcd(the_controller), urb,
								urb->status);
		spin_lock_irqsave(&the_controller->lock, flags);

	} else {
		/* tcp connection is alive */
		unsigned long flags2;
		struct vhci_unlink *unlink;

		spin_lock_irqsave(&vdev->priv_lock, flags2);

		/* setup CMD_UNLINK pdu */
		unlink = kzalloc(sizeof(struct vhci_unlink), GFP_ATOMIC);
		if (!unlink) {
			usbip_uerr("malloc vhci_unlink\n");
			spin_unlock_irqrestore(&vdev->priv_lock, flags2);
			spin_unlock_irqrestore(&the_controller->lock, flags);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
			return -ENOMEM;
		}

		unlink->seqnum = atomic_inc_return(&the_controller->seqnum);
		if (unlink->seqnum == 0xffff)
			usbip_uinfo("seqnum max\n");

		unlink->unlink_seqnum = priv->seqnum;

		usbip_uinfo("vhci_hcd: device %p seems to be still connected\n",
									vdev);

		/* send cmd_unlink and try to cancel the pending URB in the
		 * peer */
		list_add_tail(&unlink->list, &vdev->unlink_tx);
		wake_up(&vdev->waitq_tx);

		spin_unlock_irqrestore(&vdev->priv_lock, flags2);
	}


	if (!vdev->ud.tcp_socket) {
		/* tcp connection is closed */
		usbip_uinfo("vhci_hcd: vhci_urb_dequeue() gives back urb %p\n",
									urb);

		usb_hcd_unlink_urb_from_ep(hcd, urb);

		spin_unlock_irqrestore(&the_controller->lock, flags);
		usb_hcd_giveback_urb(vhci_to_hcd(the_controller), urb,
								urb->status);
		spin_lock_irqsave(&the_controller->lock, flags);
	}

	spin_unlock_irqrestore(&the_controller->lock, flags);

	usbip_dbg_vhci_hc("leave\n");
	return 0;
}