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
struct vino_framebuffer {int dummy; } ;
struct vino_channel_settings {int capturing; int /*<<< orphan*/  capture_lock; int /*<<< orphan*/  fb_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vino_capture (struct vino_channel_settings*,struct vino_framebuffer*) ; 
 int vino_queue_get_incoming (int /*<<< orphan*/ *,unsigned int*) ; 
 struct vino_framebuffer* vino_queue_peek (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int vino_capture_next(struct vino_channel_settings *vcs, int start)
{
	struct vino_framebuffer *fb;
	unsigned int incoming, id;
	int err = 0;
	unsigned long flags;

	dprintk("vino_capture_next():\n");

	spin_lock_irqsave(&vcs->capture_lock, flags);

	if (start) {
		/* start capture only if capture isn't in progress already */
		if (vcs->capturing) {
			spin_unlock_irqrestore(&vcs->capture_lock, flags);
			return 0;
		}

	} else {
		/* capture next frame:
		 * stop capture if capturing is not set */
		if (!vcs->capturing) {
			spin_unlock_irqrestore(&vcs->capture_lock, flags);
			return 0;
		}
	}

	err = vino_queue_get_incoming(&vcs->fb_queue, &incoming);
	if (err) {
		dprintk("vino_capture_next(): vino_queue_get_incoming() "
			"failed\n");
		err = -EINVAL;
		goto out;
	}
	if (incoming == 0) {
		dprintk("vino_capture_next(): no buffers available\n");
		goto out;
	}

	fb = vino_queue_peek(&vcs->fb_queue, &id);
	if (fb == NULL) {
		dprintk("vino_capture_next(): vino_queue_peek() failed\n");
		err = -EINVAL;
		goto out;
	}

	if (start) {
		vcs->capturing = 1;
	}

	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	err = vino_capture(vcs, fb);

	return err;

out:
	vcs->capturing = 0;
	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	return err;
}