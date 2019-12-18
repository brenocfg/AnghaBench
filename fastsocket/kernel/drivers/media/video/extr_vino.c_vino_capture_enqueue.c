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
struct vino_channel_settings {int /*<<< orphan*/  capture_lock; int /*<<< orphan*/  fb_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_framebuffer* vino_queue_add (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static
struct vino_framebuffer *vino_capture_enqueue(struct
					      vino_channel_settings *vcs,
					      unsigned int index)
{
	struct vino_framebuffer *fb;
	unsigned long flags;

	dprintk("vino_capture_enqueue():\n");

	spin_lock_irqsave(&vcs->capture_lock, flags);

	fb = vino_queue_add(&vcs->fb_queue, index);
	if (fb == NULL) {
		dprintk("vino_capture_enqueue(): vino_queue_add() failed, "
			"queue full?\n");
		goto out;
	}
out:
	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	return fb;
}