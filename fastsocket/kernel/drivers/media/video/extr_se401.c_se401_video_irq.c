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
struct usb_se401 {scalar_t__ nullpackets; size_t scratch_next; int bayeroffset; int cheight; int cwidth; TYPE_2__* dev; int /*<<< orphan*/  wq; int /*<<< orphan*/  scratch_overflow; TYPE_1__* scratch; int /*<<< orphan*/  dropped; int /*<<< orphan*/  streaming; } ;
struct urb {int actual_length; TYPE_2__* dev; scalar_t__ status; scalar_t__ transfer_buffer; struct usb_se401* context; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int state; int offset; int length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  BUFFER_BUSY 130 
#define  BUFFER_READY 129 
#define  BUFFER_UNUSED 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SE401_MAX_NULLPACKETS ; 
 size_t SE401_NUMSCRATCH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void se401_video_irq(struct urb *urb)
{
	struct usb_se401 *se401 = urb->context;
	int length = urb->actual_length;

	/* ohoh... */
	if (!se401->streaming)
		return;

	if (!se401->dev) {
		dev_info(&urb->dev->dev, "device vapourished\n");
		return;
	}

	/* 0 sized packets happen if we are to fast, but sometimes the camera
	   keeps sending them forever...
	 */
	if (length && !urb->status) {
		se401->nullpackets = 0;
		switch (se401->scratch[se401->scratch_next].state) {
		case BUFFER_READY:
		case BUFFER_BUSY:
			se401->dropped++;
			break;
		case BUFFER_UNUSED:
			memcpy(se401->scratch[se401->scratch_next].data,
				(unsigned char *)urb->transfer_buffer, length);
			se401->scratch[se401->scratch_next].state
							= BUFFER_READY;
			se401->scratch[se401->scratch_next].offset
							= se401->bayeroffset;
			se401->scratch[se401->scratch_next].length = length;
			if (waitqueue_active(&se401->wq))
				wake_up_interruptible(&se401->wq);
			se401->scratch_overflow = 0;
			se401->scratch_next++;
			if (se401->scratch_next >= SE401_NUMSCRATCH)
				se401->scratch_next = 0;
			break;
		}
		se401->bayeroffset += length;
		if (se401->bayeroffset >= se401->cheight * se401->cwidth)
			se401->bayeroffset = 0;
	} else {
		se401->nullpackets++;
		if (se401->nullpackets > SE401_MAX_NULLPACKETS)
			if (waitqueue_active(&se401->wq))
				wake_up_interruptible(&se401->wq);
	}

	/* Resubmit urb for new data */
	urb->status = 0;
	urb->dev = se401->dev;
	if (usb_submit_urb(urb, GFP_KERNEL))
		dev_info(&urb->dev->dev, "urb burned down\n");
	return;
}