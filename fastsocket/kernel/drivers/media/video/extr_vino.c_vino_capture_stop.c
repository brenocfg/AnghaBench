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
struct vino_channel_settings {int /*<<< orphan*/  capture_lock; int /*<<< orphan*/  fb_queue; scalar_t__ capturing; } ;
struct TYPE_2__ {int /*<<< orphan*/  vino_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vino_clear_interrupt (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_dma_stop (struct vino_channel_settings*) ; 
 TYPE_1__* vino_drvdata ; 
 scalar_t__ vino_queue_get_incoming (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ vino_queue_get_outgoing (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  vino_queue_remove (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  vino_queue_transfer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vino_capture_stop(struct vino_channel_settings *vcs)
{
	unsigned int incoming = 0, outgoing = 0, id;
	unsigned long flags, flags2;

	dprintk("vino_capture_stop():\n");

	spin_lock_irqsave(&vcs->capture_lock, flags);

	/* unset capturing to stop queue processing */
	vcs->capturing = 0;

	spin_lock_irqsave(&vino_drvdata->vino_lock, flags2);

	vino_dma_stop(vcs);
	vino_clear_interrupt(vcs);

	spin_unlock_irqrestore(&vino_drvdata->vino_lock, flags2);

	/* remove all items from the queue */
	if (vino_queue_get_incoming(&vcs->fb_queue, &incoming)) {
		dprintk("vino_capture_stop(): "
			"vino_queue_get_incoming() failed\n");
		goto out;
	}
	while (incoming > 0) {
		vino_queue_transfer(&vcs->fb_queue);

		if (vino_queue_get_incoming(&vcs->fb_queue, &incoming)) {
			dprintk("vino_capture_stop(): "
				"vino_queue_get_incoming() failed\n");
			goto out;
		}
	}

	if (vino_queue_get_outgoing(&vcs->fb_queue, &outgoing)) {
		dprintk("vino_capture_stop(): "
			"vino_queue_get_outgoing() failed\n");
		goto out;
	}
	while (outgoing > 0) {
		vino_queue_remove(&vcs->fb_queue, &id);

		if (vino_queue_get_outgoing(&vcs->fb_queue, &outgoing)) {
			dprintk("vino_capture_stop(): "
				"vino_queue_get_outgoing() failed\n");
			goto out;
		}
	}

out:
	spin_unlock_irqrestore(&vcs->capture_lock, flags);
}