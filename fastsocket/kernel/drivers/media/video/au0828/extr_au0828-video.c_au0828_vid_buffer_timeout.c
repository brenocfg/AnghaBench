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
struct au0828_dmaqueue {int dummy; } ;
struct TYPE_3__ {struct au0828_buffer* buf; } ;
struct au0828_dev {int vid_timeout_running; int /*<<< orphan*/  slock; int /*<<< orphan*/  vid_timeout; TYPE_1__ isoc_ctl; struct au0828_dmaqueue vidq; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct au0828_buffer {TYPE_2__ vb; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  buffer_filled (struct au0828_dev*,struct au0828_dmaqueue*,struct au0828_buffer*) ; 
 int /*<<< orphan*/  get_next_buf (struct au0828_dmaqueue*,struct au0828_buffer**) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char* videobuf_to_vmalloc (TYPE_2__*) ; 

void au0828_vid_buffer_timeout(unsigned long data)
{
	struct au0828_dev *dev = (struct au0828_dev *) data;
	struct au0828_dmaqueue *dma_q = &dev->vidq;
	struct au0828_buffer *buf;
	unsigned char *vid_data;
	unsigned long flags = 0;

	spin_lock_irqsave(&dev->slock, flags);

	buf = dev->isoc_ctl.buf;
	if (buf != NULL) {
		vid_data = videobuf_to_vmalloc(&buf->vb);
		memset(vid_data, 0x00, buf->vb.size); /* Blank green frame */
		buffer_filled(dev, dma_q, buf);
	}
	get_next_buf(dma_q, &buf);

	if (dev->vid_timeout_running == 1)
		mod_timer(&dev->vid_timeout, jiffies + (HZ / 10));

	spin_unlock_irqrestore(&dev->slock, flags);
}