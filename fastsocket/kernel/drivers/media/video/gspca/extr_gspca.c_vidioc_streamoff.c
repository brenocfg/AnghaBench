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
struct gspca_dev {int /*<<< orphan*/  queue_lock; scalar_t__ fr_o; int /*<<< orphan*/  fr_i; int /*<<< orphan*/  fr_q; int /*<<< orphan*/  wq; int /*<<< orphan*/  usb_lock; scalar_t__ usb_err; struct file* capt_file; int /*<<< orphan*/  streaming; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_stream_off (struct gspca_dev*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv,
				enum v4l2_buf_type buf_type)
{
	struct gspca_dev *gspca_dev = priv;
	int ret;

	if (buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;

	if (!gspca_dev->streaming) {
		ret = 0;
		goto out;
	}

	/* check the capture file */
	if (gspca_dev->capt_file != file) {
		ret = -EBUSY;
		goto out;
	}

	/* stop streaming */
	if (mutex_lock_interruptible(&gspca_dev->usb_lock)) {
		ret = -ERESTARTSYS;
		goto out;
	}
	gspca_dev->usb_err = 0;
	gspca_stream_off(gspca_dev);
	mutex_unlock(&gspca_dev->usb_lock);
	/* In case another thread is waiting in dqbuf */
	wake_up_interruptible(&gspca_dev->wq);

	/* empty the transfer queues */
	atomic_set(&gspca_dev->fr_q, 0);
	atomic_set(&gspca_dev->fr_i, 0);
	gspca_dev->fr_o = 0;
	ret = 0;
out:
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}