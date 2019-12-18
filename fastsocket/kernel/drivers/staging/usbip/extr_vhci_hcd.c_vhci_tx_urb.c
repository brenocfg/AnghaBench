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
struct vhci_priv {int seqnum; int /*<<< orphan*/  list; struct urb* urb; struct vhci_device* vdev; } ;
struct vhci_device {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  priv_tx; int /*<<< orphan*/  ud; } ;
struct urb {void* hcpriv; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_MALLOC ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 struct vhci_device* get_vdev (TYPE_2__*) ; 
 struct vhci_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* the_controller ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uinfo (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhci_tx_urb(struct urb *urb)
{
	struct vhci_device *vdev = get_vdev(urb->dev);
	struct vhci_priv *priv;
	unsigned long flag;

	if (!vdev) {
		err("could not get virtual device");
		/* BUG(); */
		return;
	}

	priv = kzalloc(sizeof(struct vhci_priv), GFP_ATOMIC);

	spin_lock_irqsave(&vdev->priv_lock, flag);

	if (!priv) {
		dev_err(&urb->dev->dev, "malloc vhci_priv\n");
		spin_unlock_irqrestore(&vdev->priv_lock, flag);
		usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_MALLOC);
		return;
	}

	priv->seqnum = atomic_inc_return(&the_controller->seqnum);
	if (priv->seqnum == 0xffff)
		usbip_uinfo("seqnum max\n");

	priv->vdev = vdev;
	priv->urb = urb;

	urb->hcpriv = (void *) priv;


	list_add_tail(&priv->list, &vdev->priv_tx);

	wake_up(&vdev->waitq_tx);
	spin_unlock_irqrestore(&vdev->priv_lock, flag);
}