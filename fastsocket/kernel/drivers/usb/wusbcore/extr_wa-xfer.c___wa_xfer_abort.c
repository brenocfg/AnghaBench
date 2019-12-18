#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int bLength; int /*<<< orphan*/  dwTransferID; int /*<<< orphan*/  wRPipe; int /*<<< orphan*/  bRequestType; } ;
struct wa_xfer_abort_buffer {int /*<<< orphan*/  urb; TYPE_6__ cmd; } ;
struct wa_xfer {TYPE_5__* wa; TYPE_2__* ep; } ;
struct TYPE_9__ {int /*<<< orphan*/  wRPipeIndex; } ;
struct wa_rpipe {TYPE_3__ descr; } ;
struct device {int dummy; } ;
struct TYPE_11__ {TYPE_4__* dto_epd; int /*<<< orphan*/  usb_dev; TYPE_1__* usb_iface; } ;
struct TYPE_10__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_8__ {struct wa_rpipe* hcpriv; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WA_XFER_ABORT ; 
 int /*<<< orphan*/  __wa_xfer_abort_cb ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct wa_xfer*,int) ; 
 int /*<<< orphan*/  kfree (struct wa_xfer_abort_buffer*) ; 
 struct wa_xfer_abort_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ,struct wa_xfer_abort_buffer*) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_xfer_id (struct wa_xfer*) ; 

__attribute__((used)) static void __wa_xfer_abort(struct wa_xfer *xfer)
{
	int result;
	struct device *dev = &xfer->wa->usb_iface->dev;
	struct wa_xfer_abort_buffer *b;
	struct wa_rpipe *rpipe = xfer->ep->hcpriv;

	b = kmalloc(sizeof(*b), GFP_ATOMIC);
	if (b == NULL)
		goto error_kmalloc;
	b->cmd.bLength =  sizeof(b->cmd);
	b->cmd.bRequestType = WA_XFER_ABORT;
	b->cmd.wRPipe = rpipe->descr.wRPipeIndex;
	b->cmd.dwTransferID = wa_xfer_id(xfer);

	usb_init_urb(&b->urb);
	usb_fill_bulk_urb(&b->urb, xfer->wa->usb_dev,
		usb_sndbulkpipe(xfer->wa->usb_dev,
				xfer->wa->dto_epd->bEndpointAddress),
		&b->cmd, sizeof(b->cmd), __wa_xfer_abort_cb, b);
	result = usb_submit_urb(&b->urb, GFP_ATOMIC);
	if (result < 0)
		goto error_submit;
	return;				/* callback frees! */


error_submit:
	if (printk_ratelimit())
		dev_err(dev, "xfer %p: Can't submit abort request: %d\n",
			xfer, result);
	kfree(b);
error_kmalloc:
	return;

}