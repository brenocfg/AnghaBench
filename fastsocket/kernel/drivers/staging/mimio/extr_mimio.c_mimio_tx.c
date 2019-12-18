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
struct TYPE_6__ {TYPE_3__* urb; } ;
struct mimio {int txflags; TYPE_2__ out; int /*<<< orphan*/  waitq; TYPE_1__* idev; int /*<<< orphan*/  txlock; int /*<<< orphan*/  udev; } ;
struct TYPE_7__ {int transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int MIMIO_TXDONE ; 
 int MIMIO_TXWAIT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  isvalidtxsize (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_3__*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int mimio_tx(struct mimio *mimio, const char *buf, int nbytes)
{
	int rslt;
	int timeout;
	unsigned long flags;
	DECLARE_WAITQUEUE(wait, current);

	if (!(isvalidtxsize(nbytes))) {
		dev_err(&mimio->idev->dev, "invalid arg: nbytes: %d.\n",
			nbytes);
		return -EINVAL;
	}

	/*
	 * Init the out urb and copy the data to send.
	 */
	mimio->out.urb->dev = mimio->udev;
	mimio->out.urb->transfer_buffer_length = nbytes;
	memcpy(mimio->out.urb->transfer_buffer, buf, nbytes);

	/*
	 * Send the data.
	 */
	spin_lock_irqsave(&mimio->txlock, flags);
	mimio->txflags = MIMIO_TXWAIT;
	rslt = usb_submit_urb(mimio->out.urb, GFP_ATOMIC);
	spin_unlock_irqrestore(&mimio->txlock, flags);
	dev_dbg(&mimio->idev->dev, "rslt: %d.\n", rslt);

	if (rslt) {
		dev_err(&mimio->idev->dev, "usb_submit_urb failure: %d.\n",
			rslt);
		return rslt;
	}

	/*
	 * Wait for completion to be signalled (the mimio_irq_out
	 * completion routine will or MIMIO_TXDONE in with txflags).
	 */
	timeout = HZ;
	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&mimio->waitq, &wait);

	while (timeout && ((mimio->txflags & MIMIO_TXDONE) == 0)) {
		timeout = schedule_timeout(timeout);
		rmb();
	}

	if ((mimio->txflags & MIMIO_TXDONE) == 0)
		dev_dbg(&mimio->idev->dev, "tx timed out.\n");

	/*
	 * Now that completion has been signalled,
	 * unlink the urb so that it can be recycled.
	 */
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&mimio->waitq, &wait);
	usb_unlink_urb(mimio->out.urb);

	return rslt;
}