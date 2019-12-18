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
struct wahc {int /*<<< orphan*/  xfer_work; int /*<<< orphan*/  xfer_list_lock; int /*<<< orphan*/  xfer_delayed_list; TYPE_1__* usb_iface; } ;
struct wa_xfer {int /*<<< orphan*/  list_node; struct usb_host_endpoint* ep; int /*<<< orphan*/  gfp; struct urb* urb; int /*<<< orphan*/  wa; } ;
struct usb_host_endpoint {int dummy; } ;
struct urb {int transfer_flags; int pipe; int /*<<< orphan*/  transfer_buffer_length; struct wa_xfer* hcpriv; int /*<<< orphan*/  status; int /*<<< orphan*/ * transfer_buffer; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct wa_xfer*,struct urb*,int,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct urb*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 unsigned int in_atomic () ; 
 unsigned int irqs_disabled () ; 
 int /*<<< orphan*/  kfree (struct wa_xfer*) ; 
 struct wa_xfer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_get_urb (struct urb*) ; 
 int /*<<< orphan*/  wa_get (struct wahc*) ; 
 int /*<<< orphan*/  wa_urb_enqueue_b (struct wa_xfer*) ; 
 int /*<<< orphan*/  wa_xfer_init (struct wa_xfer*) ; 
 int /*<<< orphan*/  wusbd ; 

int wa_urb_enqueue(struct wahc *wa, struct usb_host_endpoint *ep,
		   struct urb *urb, gfp_t gfp)
{
	int result;
	struct device *dev = &wa->usb_iface->dev;
	struct wa_xfer *xfer;
	unsigned long my_flags;
	unsigned cant_sleep = irqs_disabled() | in_atomic();

	if (urb->transfer_buffer == NULL
	    && !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
	    && urb->transfer_buffer_length != 0) {
		dev_err(dev, "BUG? urb %p: NULL xfer buffer & NODMA\n", urb);
		dump_stack();
	}

	result = -ENOMEM;
	xfer = kzalloc(sizeof(*xfer), gfp);
	if (xfer == NULL)
		goto error_kmalloc;

	result = -ENOENT;
	if (urb->status != -EINPROGRESS)	/* cancelled */
		goto error_dequeued;		/* before starting? */
	wa_xfer_init(xfer);
	xfer->wa = wa_get(wa);
	xfer->urb = urb;
	xfer->gfp = gfp;
	xfer->ep = ep;
	urb->hcpriv = xfer;

	dev_dbg(dev, "xfer %p urb %p pipe 0x%02x [%d bytes] %s %s %s\n",
		xfer, urb, urb->pipe, urb->transfer_buffer_length,
		urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP ? "dma" : "nodma",
		urb->pipe & USB_DIR_IN ? "inbound" : "outbound",
		cant_sleep ? "deferred" : "inline");

	if (cant_sleep) {
		usb_get_urb(urb);
		spin_lock_irqsave(&wa->xfer_list_lock, my_flags);
		list_add_tail(&xfer->list_node, &wa->xfer_delayed_list);
		spin_unlock_irqrestore(&wa->xfer_list_lock, my_flags);
		queue_work(wusbd, &wa->xfer_work);
	} else {
		wa_urb_enqueue_b(xfer);
	}
	return 0;

error_dequeued:
	kfree(xfer);
error_kmalloc:
	return result;
}