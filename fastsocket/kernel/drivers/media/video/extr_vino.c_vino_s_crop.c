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
struct vino_channel_settings {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_crop {int type; TYPE_1__ c; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OVERLAY 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_2__* vino_drvdata ; 
 int /*<<< orphan*/  vino_set_clipping (struct vino_channel_settings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vino_s_crop(struct file *file, void *__fh,
			    struct v4l2_crop *c)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	unsigned long flags;

	switch (c->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		spin_lock_irqsave(&vino_drvdata->input_lock, flags);

		vino_set_clipping(vcs, c->c.left, c->c.top,
				  c->c.width, c->c.height);

		spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
	default:
		return -EINVAL;
	}

	return 0;
}