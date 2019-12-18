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
struct TYPE_3__ {scalar_t__ sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct gspca_dev {scalar_t__ nframes; scalar_t__ frsz; int curr_mode; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ streaming; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int try_fmt_vid_cap (struct gspca_dev*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
			    struct v4l2_format *fmt)
{
	struct gspca_dev *gspca_dev = priv;
	int ret;

	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;

	ret = try_fmt_vid_cap(gspca_dev, fmt);
	if (ret < 0)
		goto out;

	if (gspca_dev->nframes != 0
	    && fmt->fmt.pix.sizeimage > gspca_dev->frsz) {
		ret = -EINVAL;
		goto out;
	}

	if (ret == gspca_dev->curr_mode) {
		ret = 0;
		goto out;			/* same mode */
	}

	if (gspca_dev->streaming) {
		ret = -EBUSY;
		goto out;
	}
	gspca_dev->width = fmt->fmt.pix.width;
	gspca_dev->height = fmt->fmt.pix.height;
	gspca_dev->pixfmt = fmt->fmt.pix.pixelformat;
	gspca_dev->curr_mode = ret;

	ret = 0;
out:
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}