#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wahc {int /*<<< orphan*/  xfer_list_lock; int /*<<< orphan*/  xfer_list; TYPE_1__* usb_iface; } ;
struct wa_xfer {unsigned int segs; int /*<<< orphan*/  segs_submitted; struct wa_seg** seg; int /*<<< orphan*/  list_node; TYPE_2__* ep; struct wahc* wa; } ;
struct wa_seg {int /*<<< orphan*/  list_node; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  wRequests; } ;
struct wa_rpipe {int /*<<< orphan*/  seg_lock; int /*<<< orphan*/  seg_list; int /*<<< orphan*/  segs_available; TYPE_3__ descr; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct wa_rpipe* hcpriv; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WA_SEG_DELAYED ; 
 int __wa_seg_submit (struct wa_rpipe*,struct wa_xfer*,struct wa_seg*) ; 
 int /*<<< orphan*/  __wa_xfer_abort (struct wa_xfer*) ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct wa_xfer*,unsigned int,...) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __wa_xfer_submit(struct wa_xfer *xfer)
{
	int result;
	struct wahc *wa = xfer->wa;
	struct device *dev = &wa->usb_iface->dev;
	unsigned cnt;
	struct wa_seg *seg;
	unsigned long flags;
	struct wa_rpipe *rpipe = xfer->ep->hcpriv;
	size_t maxrequests = le16_to_cpu(rpipe->descr.wRequests);
	u8 available;
	u8 empty;

	spin_lock_irqsave(&wa->xfer_list_lock, flags);
	list_add_tail(&xfer->list_node, &wa->xfer_list);
	spin_unlock_irqrestore(&wa->xfer_list_lock, flags);

	BUG_ON(atomic_read(&rpipe->segs_available) > maxrequests);
	result = 0;
	spin_lock_irqsave(&rpipe->seg_lock, flags);
	for (cnt = 0; cnt < xfer->segs; cnt++) {
		available = atomic_read(&rpipe->segs_available);
		empty = list_empty(&rpipe->seg_list);
		seg = xfer->seg[cnt];
		dev_dbg(dev, "xfer %p#%u: available %u empty %u (%s)\n",
			xfer, cnt, available, empty,
			available == 0 || !empty ? "delayed" : "submitted");
		if (available == 0 || !empty) {
			dev_dbg(dev, "xfer %p#%u: delayed\n", xfer, cnt);
			seg->status = WA_SEG_DELAYED;
			list_add_tail(&seg->list_node, &rpipe->seg_list);
		} else {
			result = __wa_seg_submit(rpipe, xfer, seg);
			if (result < 0) {
				__wa_xfer_abort(xfer);
				goto error_seg_submit;
			}
		}
		xfer->segs_submitted++;
	}
error_seg_submit:
	spin_unlock_irqrestore(&rpipe->seg_lock, flags);
	return result;
}