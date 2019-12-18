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
struct videobuf_queue {struct omap24xxcam_fh* priv_data; } ;
struct videobuf_buffer {int state; int /*<<< orphan*/  size; } ;
struct omap24xxcam_fh {struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int sgdma_in_queue; int /*<<< orphan*/  dev; int /*<<< orphan*/  core_enable_disable_lock; int /*<<< orphan*/  in_reset; int /*<<< orphan*/  sgdma; } ;
typedef  enum videobuf_state { ____Placeholder_videobuf_state } videobuf_state ;
struct TYPE_2__ {int /*<<< orphan*/  sglen; int /*<<< orphan*/  sglist; } ;

/* Variables and functions */
 int VIDEOBUF_ACTIVE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap24xxcam_core_enable (struct omap24xxcam_device*) ; 
 int omap24xxcam_sgdma_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct videobuf_buffer*) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_complete ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* videobuf_to_dma (struct videobuf_buffer*) ; 

__attribute__((used)) static void omap24xxcam_vbq_queue(struct videobuf_queue *vbq,
				  struct videobuf_buffer *vb)
{
	struct omap24xxcam_fh *fh = vbq->priv_data;
	struct omap24xxcam_device *cam = fh->cam;
	enum videobuf_state state = vb->state;
	unsigned long flags;
	int err;

	/*
	 * FIXME: We're marking the buffer active since we have no
	 * pretty way of marking it active exactly when the
	 * scatter-gather transfer starts.
	 */
	vb->state = VIDEOBUF_ACTIVE;

	err = omap24xxcam_sgdma_queue(&fh->cam->sgdma,
				      videobuf_to_dma(vb)->sglist,
				      videobuf_to_dma(vb)->sglen, vb->size,
				      omap24xxcam_vbq_complete, vb);

	if (!err) {
		spin_lock_irqsave(&cam->core_enable_disable_lock, flags);
		if (++cam->sgdma_in_queue == 1
		    && !atomic_read(&cam->in_reset))
			omap24xxcam_core_enable(cam);
		spin_unlock_irqrestore(&cam->core_enable_disable_lock, flags);
	} else {
		/*
		 * Oops. We're not supposed to get any errors here.
		 * The only way we could get an error is if we ran out
		 * of scatter-gather DMA slots, but we are supposed to
		 * have at least as many scatter-gather DMA slots as
		 * video buffers so that can't happen.
		 */
		dev_err(cam->dev, "failed to queue a video buffer for dma!\n");
		dev_err(cam->dev, "likely a bug in the driver!\n");
		vb->state = state;
	}
}