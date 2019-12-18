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
struct vino_framebuffer {int state; scalar_t__ data_format; int /*<<< orphan*/  state_lock; } ;
struct vino_channel_settings {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vino_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ VINO_DATA_FMT_RGB32 ; 
#define  VINO_FRAMEBUFFER_IN_USE 129 
#define  VINO_FRAMEBUFFER_READY 128 
 int VINO_FRAMEBUFFER_UNUSED ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vino_clear_interrupt (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_convert_to_rgba (struct vino_framebuffer*) ; 
 int /*<<< orphan*/  vino_dma_stop (struct vino_channel_settings*) ; 
 TYPE_1__* vino_drvdata ; 
 scalar_t__ vino_pixel_conversion ; 
 int /*<<< orphan*/  vino_sync_buffer (struct vino_framebuffer*) ; 

__attribute__((used)) static int vino_check_buffer(struct vino_channel_settings *vcs,
			     struct vino_framebuffer *fb)
{
	int err = 0;
	unsigned long flags;

	dprintk("vino_check_buffer():\n");

	spin_lock_irqsave(&fb->state_lock, flags);
	switch (fb->state) {
	case VINO_FRAMEBUFFER_IN_USE:
		err = -EIO;
		break;
	case VINO_FRAMEBUFFER_READY:
		vino_sync_buffer(fb);
		fb->state = VINO_FRAMEBUFFER_UNUSED;
		break;
	default:
		err = -EINVAL;
	}
	spin_unlock_irqrestore(&fb->state_lock, flags);

	if (!err) {
		if (vino_pixel_conversion
		    && (fb->data_format == VINO_DATA_FMT_RGB32)) {
			vino_convert_to_rgba(fb);
		}
	} else if (err && (err != -EINVAL)) {
		dprintk("vino_check_buffer(): buffer not ready\n");

		spin_lock_irqsave(&vino_drvdata->vino_lock, flags);
		vino_dma_stop(vcs);
		vino_clear_interrupt(vcs);
		spin_unlock_irqrestore(&vino_drvdata->vino_lock, flags);
	}

	return err;
}