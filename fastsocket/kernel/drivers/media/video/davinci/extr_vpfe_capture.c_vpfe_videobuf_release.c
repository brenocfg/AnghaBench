#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpfe_fh {struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; int /*<<< orphan*/  v4l2_dev; } ;
struct videobuf_queue {struct vpfe_fh* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  videobuf_dma_contig_free (struct videobuf_queue*,struct videobuf_buffer*) ; 

__attribute__((used)) static void vpfe_videobuf_release(struct videobuf_queue *vq,
				  struct videobuf_buffer *vb)
{
	struct vpfe_fh *fh = vq->priv_data;
	struct vpfe_device *vpfe_dev = fh->vpfe_dev;
	unsigned long flags;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_videobuf_release\n");

	/*
	 * We need to flush the buffer from the dma queue since
	 * they are de-allocated
	 */
	spin_lock_irqsave(&vpfe_dev->dma_queue_lock, flags);
	INIT_LIST_HEAD(&vpfe_dev->dma_queue);
	spin_unlock_irqrestore(&vpfe_dev->dma_queue_lock, flags);
	videobuf_dma_contig_free(vq, vb);
	vb->state = VIDEOBUF_NEEDS_INIT;
}