#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int right; int left; int bottom; int top; } ;
struct vino_channel_settings {int decimation; size_t data_format; int line_size; TYPE_2__ clipping; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; scalar_t__ priv; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_4__* vino_data_formats ; 
 TYPE_3__* vino_drvdata ; 

__attribute__((used)) static int vino_g_fmt_vid_cap(struct file *file, void *__fh,
			   struct v4l2_format *f)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	unsigned long flags;
	struct v4l2_pix_format *pf = &f->fmt.pix;

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);

	pf->width = (vcs->clipping.right - vcs->clipping.left) /
		vcs->decimation;
	pf->height = (vcs->clipping.bottom - vcs->clipping.top) /
		vcs->decimation;
	pf->pixelformat =
		vino_data_formats[vcs->data_format].pixelformat;

	pf->field = V4L2_FIELD_INTERLACED;
	pf->bytesperline = vcs->line_size;
	pf->sizeimage = vcs->line_size *
		(vcs->clipping.bottom - vcs->clipping.top) /
		vcs->decimation;
	pf->colorspace =
		vino_data_formats[vcs->data_format].colorspace;

	pf->priv = 0;

	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);
	return 0;
}