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
struct videobuf_queue {struct au0828_fh* priv_data; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct TYPE_3__ {struct au0828_buffer* buf; } ;
struct au0828_dev {int /*<<< orphan*/  slock; TYPE_1__ isoc_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct au0828_buffer {TYPE_2__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  videobuf_vmalloc_free (TYPE_2__*) ; 

__attribute__((used)) static void free_buffer(struct videobuf_queue *vq, struct au0828_buffer *buf)
{
	struct au0828_fh     *fh  = vq->priv_data;
	struct au0828_dev    *dev = fh->dev;
	unsigned long flags = 0;
	if (in_interrupt())
		BUG();

	/* We used to wait for the buffer to finish here, but this didn't work
	   because, as we were keeping the state as VIDEOBUF_QUEUED,
	   videobuf_queue_cancel marked it as finished for us.
	   (Also, it could wedge forever if the hardware was misconfigured.)

	   This should be safe; by the time we get here, the buffer isn't
	   queued anymore. If we ever start marking the buffers as
	   VIDEOBUF_ACTIVE, it won't be, though.
	*/
	spin_lock_irqsave(&dev->slock, flags);
	if (dev->isoc_ctl.buf == buf)
		dev->isoc_ctl.buf = NULL;
	spin_unlock_irqrestore(&dev->slock, flags);

	videobuf_vmalloc_free(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}