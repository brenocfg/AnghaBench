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
struct TYPE_6__ {int pixelformat; scalar_t__ field; int width; int height; int bytesperline; int sizeimage; scalar_t__ priv; scalar_t__ colorspace; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int subsample; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mchip_mode; TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE_CONT_COMP ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE_CONT_OUT ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_MJPEG 129 
#define  V4L2_PIX_FMT_YUYV 128 
 TYPE_4__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *fh,
				    struct v4l2_format *f)
{
	if (f->fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV &&
	    f->fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG)
		return -EINVAL;

	if (f->fmt.pix.field != V4L2_FIELD_ANY &&
	    f->fmt.pix.field != V4L2_FIELD_NONE)
		return -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;
	mutex_lock(&meye.lock);

	if (f->fmt.pix.width <= 320) {
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
		meye.params.subsample = 1;
	} else {
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
		meye.params.subsample = 0;
	}

	switch (f->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_YUYV:
		meye.mchip_mode = MCHIP_HIC_MODE_CONT_OUT;
		break;
	case V4L2_PIX_FMT_MJPEG:
		meye.mchip_mode = MCHIP_HIC_MODE_CONT_COMP;
		break;
	}

	mutex_unlock(&meye.lock);
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = 0;
	f->fmt.pix.priv = 0;

	return 0;
}