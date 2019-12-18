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
struct vino_framebuffer {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; } ;
struct vino_channel_settings {int /*<<< orphan*/  capture_lock; int /*<<< orphan*/  fb_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VINO_FRAMEBUFFER_UNUSED ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vino_capture_next (struct vino_channel_settings*,int /*<<< orphan*/ ) ; 
 struct vino_framebuffer* vino_queue_peek (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void vino_skip_frame(struct vino_channel_settings *vcs)
{
	struct vino_framebuffer *fb;
	unsigned long flags;
	unsigned int id;

	spin_lock_irqsave(&vcs->capture_lock, flags);
	fb = vino_queue_peek(&vcs->fb_queue, &id);
	if (!fb) {
		spin_unlock_irqrestore(&vcs->capture_lock, flags);
		dprintk("vino_skip_frame(): vino_queue_peek() failed!\n");
		return;
	}
	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	spin_lock_irqsave(&fb->state_lock, flags);
	fb->state = VINO_FRAMEBUFFER_UNUSED;
	spin_unlock_irqrestore(&fb->state_lock, flags);

	vino_capture_next(vcs, 0);
}