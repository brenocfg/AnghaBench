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
struct gspca_dev {scalar_t__ nframes; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  streaming; TYPE_2__* frame; struct file* capt_file; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ v4l2_buf; } ;

/* Variables and functions */
 int D_STREAM ; 
 int EBUSY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PDEBUG_MODE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V4L2_BUF_FLAG_QUEUED ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int gspca_debug ; 
 int gspca_init_transfer (struct gspca_dev*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv,
			   enum v4l2_buf_type buf_type)
{
	struct gspca_dev *gspca_dev = priv;
	int ret;

	if (buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;

	/* check the capture file */
	if (gspca_dev->capt_file != file) {
		ret = -EBUSY;
		goto out;
	}

	if (gspca_dev->nframes == 0
	    || !(gspca_dev->frame[0].v4l2_buf.flags & V4L2_BUF_FLAG_QUEUED)) {
		ret = -EINVAL;
		goto out;
	}
	if (!gspca_dev->streaming) {
		ret = gspca_init_transfer(gspca_dev);
		if (ret < 0)
			goto out;
	}
#ifdef GSPCA_DEBUG
	if (gspca_debug & D_STREAM) {
		PDEBUG_MODE("stream on OK",
			gspca_dev->pixfmt,
			gspca_dev->width,
			gspca_dev->height);
	}
#endif
	ret = 0;
out:
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}