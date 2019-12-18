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
struct TYPE_4__ {size_t head; size_t tail; char* buf; } ;
struct iforce {int /*<<< orphan*/  xmit_lock; TYPE_2__* dev; int /*<<< orphan*/  xmit_flags; TYPE_3__* out; TYPE_1__ xmit; int /*<<< orphan*/  usbdev; } ;
struct TYPE_6__ {int transfer_buffer_length; scalar_t__ transfer_buffer; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CIRC_CNT_TO_END (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IFORCE_XMIT_RUNNING ; 
 int /*<<< orphan*/  XMIT_INC (size_t,int) ; 
 int /*<<< orphan*/  XMIT_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 

void iforce_usb_xmit(struct iforce *iforce)
{
	int n, c;
	unsigned long flags;

	spin_lock_irqsave(&iforce->xmit_lock, flags);

	if (iforce->xmit.head == iforce->xmit.tail) {
		clear_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags);
		spin_unlock_irqrestore(&iforce->xmit_lock, flags);
		return;
	}

	((char *)iforce->out->transfer_buffer)[0] = iforce->xmit.buf[iforce->xmit.tail];
	XMIT_INC(iforce->xmit.tail, 1);
	n = iforce->xmit.buf[iforce->xmit.tail];
	XMIT_INC(iforce->xmit.tail, 1);

	iforce->out->transfer_buffer_length = n + 1;
	iforce->out->dev = iforce->usbdev;

	/* Copy rest of data then */
	c = CIRC_CNT_TO_END(iforce->xmit.head, iforce->xmit.tail, XMIT_SIZE);
	if (n < c) c=n;

	memcpy(iforce->out->transfer_buffer + 1,
	       &iforce->xmit.buf[iforce->xmit.tail],
	       c);
	if (n != c) {
		memcpy(iforce->out->transfer_buffer + 1 + c,
		       &iforce->xmit.buf[0],
		       n-c);
	}
	XMIT_INC(iforce->xmit.tail, n);

	if ( (n=usb_submit_urb(iforce->out, GFP_ATOMIC)) ) {
		clear_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags);
		dev_warn(&iforce->dev->dev, "usb_submit_urb failed %d\n", n);
	}

	/* The IFORCE_XMIT_RUNNING bit is not cleared here. That's intended.
	 * As long as the urb completion handler is not called, the transmiting
	 * is considered to be running */
	spin_unlock_irqrestore(&iforce->xmit_lock, flags);
}