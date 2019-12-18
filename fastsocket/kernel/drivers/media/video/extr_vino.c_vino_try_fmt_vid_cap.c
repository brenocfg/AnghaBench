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
struct vino_channel_settings {size_t data_format; int decimation; int line_size; TYPE_2__ clipping; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; scalar_t__ priv; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  description; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 size_t VINO_DATA_FMT_GREY ; 
 size_t VINO_DATA_FMT_NONE ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  memcpy (struct vino_channel_settings*,struct vino_channel_settings*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_4__* vino_data_formats ; 
 TYPE_3__* vino_drvdata ; 
 size_t vino_find_data_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vino_set_scaling (struct vino_channel_settings*,int,int) ; 

__attribute__((used)) static int vino_try_fmt_vid_cap(struct file *file, void *__fh,
			     struct v4l2_format *f)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	struct vino_channel_settings tempvcs;
	unsigned long flags;
	struct v4l2_pix_format *pf = &f->fmt.pix;

	dprintk("requested: w = %d, h = %d\n",
			pf->width, pf->height);

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);
	memcpy(&tempvcs, vcs, sizeof(struct vino_channel_settings));
	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);

	tempvcs.data_format = vino_find_data_format(pf->pixelformat);
	if (tempvcs.data_format == VINO_DATA_FMT_NONE) {
		tempvcs.data_format = VINO_DATA_FMT_GREY;
		pf->pixelformat =
			vino_data_formats[tempvcs.data_format].
			pixelformat;
	}

	/* data format must be set before clipping/scaling */
	vino_set_scaling(&tempvcs, pf->width, pf->height);

	dprintk("data format = %s\n",
			vino_data_formats[tempvcs.data_format].description);

	pf->width = (tempvcs.clipping.right - tempvcs.clipping.left) /
		tempvcs.decimation;
	pf->height = (tempvcs.clipping.bottom - tempvcs.clipping.top) /
		tempvcs.decimation;

	pf->field = V4L2_FIELD_INTERLACED;
	pf->bytesperline = tempvcs.line_size;
	pf->sizeimage = tempvcs.line_size *
		(tempvcs.clipping.bottom - tempvcs.clipping.top) /
		tempvcs.decimation;
	pf->colorspace =
		vino_data_formats[tempvcs.data_format].colorspace;

	pf->priv = 0;
	return 0;
}