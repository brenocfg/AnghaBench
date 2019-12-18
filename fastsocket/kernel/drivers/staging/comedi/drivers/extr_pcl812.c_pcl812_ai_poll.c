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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct TYPE_4__ {unsigned int* dmabytestomove; int next_dma_buf; unsigned int ai_poll_ptr; scalar_t__* dmabuf; int /*<<< orphan*/  ai_dma; } ;
struct TYPE_3__ {int buf_write_count; int buf_read_count; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 unsigned int get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transfer_from_dma_buf (struct comedi_device*,struct comedi_subdevice*,void*,unsigned int,unsigned int) ; 

__attribute__((used)) static int pcl812_ai_poll(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned long flags;
	unsigned int top1, top2, i;

	if (!devpriv->ai_dma)
		return 0;	/*  poll is valid only for DMA transfer */

	spin_lock_irqsave(&dev->spinlock, flags);

	for (i = 0; i < 10; i++) {
		top1 = get_dma_residue(devpriv->ai_dma);	/*  where is now DMA */
		top2 = get_dma_residue(devpriv->ai_dma);
		if (top1 == top2)
			break;
	}

	if (top1 != top2) {
		spin_unlock_irqrestore(&dev->spinlock, flags);
		return 0;
	}

	top1 = devpriv->dmabytestomove[1 - devpriv->next_dma_buf] - top1;	/*  where is now DMA in buffer */
	top1 >>= 1;		/*  sample position */
	top2 = top1 - devpriv->ai_poll_ptr;
	if (top2 < 1) {		/*  no new samples */
		spin_unlock_irqrestore(&dev->spinlock, flags);
		return 0;
	}

	transfer_from_dma_buf(dev, s,
			      (void *)devpriv->dmabuf[1 -
						      devpriv->next_dma_buf],
			      devpriv->ai_poll_ptr, top2);

	devpriv->ai_poll_ptr = top1;	/*  new buffer position */

	spin_unlock_irqrestore(&dev->spinlock, flags);

	return s->async->buf_write_count - s->async->buf_read_count;
}