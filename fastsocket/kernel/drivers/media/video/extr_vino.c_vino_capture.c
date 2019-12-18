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
struct vino_framebuffer {scalar_t__ state; int /*<<< orphan*/  state_lock; } ;
struct vino_channel_settings {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vino_lock; int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VINO_FRAMEBUFFER_IN_USE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vino_dma_setup (struct vino_channel_settings*,struct vino_framebuffer*) ; 
 int /*<<< orphan*/  vino_dma_start (struct vino_channel_settings*) ; 
 TYPE_1__* vino_drvdata ; 

__attribute__((used)) static int vino_capture(struct vino_channel_settings *vcs,
			struct vino_framebuffer *fb)
{
	int err = 0;
	unsigned long flags, flags2;

	spin_lock_irqsave(&fb->state_lock, flags);

	if (fb->state == VINO_FRAMEBUFFER_IN_USE)
		err = -EBUSY;
	fb->state = VINO_FRAMEBUFFER_IN_USE;

	spin_unlock_irqrestore(&fb->state_lock, flags);

	if (err)
		return err;

	spin_lock_irqsave(&vino_drvdata->vino_lock, flags);
	spin_lock_irqsave(&vino_drvdata->input_lock, flags2);

	vino_dma_setup(vcs, fb);
	vino_dma_start(vcs);

	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags2);
	spin_unlock_irqrestore(&vino_drvdata->vino_lock, flags);

	return err;
}