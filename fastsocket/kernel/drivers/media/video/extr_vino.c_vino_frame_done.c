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
struct vino_framebuffer {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frame_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  frame_wait_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  frame_counter; } ;
struct vino_channel_settings {TYPE_2__ fb_queue; TYPE_1__ int_data; int /*<<< orphan*/  capture_lock; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 scalar_t__ VINO_FRAMEBUFFER_IN_USE ; 
 scalar_t__ VINO_FRAMEBUFFER_READY ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vino_capture_next (struct vino_channel_settings*,int /*<<< orphan*/ ) ; 
 struct vino_framebuffer* vino_queue_transfer (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vino_frame_done(struct vino_channel_settings *vcs)
{
	struct vino_framebuffer *fb;
	unsigned long flags;

	spin_lock_irqsave(&vcs->capture_lock, flags);
	fb = vino_queue_transfer(&vcs->fb_queue);
	if (!fb) {
		spin_unlock_irqrestore(&vcs->capture_lock, flags);
		dprintk("vino_frame_done(): vino_queue_transfer() failed!\n");
		return;
	}
	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	fb->frame_counter = vcs->int_data.frame_counter;
	memcpy(&fb->timestamp, &vcs->int_data.timestamp,
	       sizeof(struct timeval));

	spin_lock_irqsave(&fb->state_lock, flags);
	if (fb->state == VINO_FRAMEBUFFER_IN_USE)
		fb->state = VINO_FRAMEBUFFER_READY;
	spin_unlock_irqrestore(&fb->state_lock, flags);

	wake_up(&vcs->fb_queue.frame_wait_queue);

	vino_capture_next(vcs, 0);
}