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
struct file {int dummy; } ;
struct cx25821_fh {scalar_t__ type; struct cx25821_dev* dev; } ;
struct cx25821_dev {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_VIDEO7 ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  get_queue (struct cx25821_fh*) ; 
 int /*<<< orphan*/  get_resource (struct cx25821_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_get (struct cx25821_dev*,struct cx25821_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int videobuf_streamon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct cx25821_fh *fh = priv;
	struct cx25821_dev *dev = fh->dev;

	if (unlikely(fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)) {
		return -EINVAL;
	}

	if (unlikely(i != fh->type)) {
		return -EINVAL;
	}

	if (unlikely(!res_get(dev, fh, get_resource(fh, RESOURCE_VIDEO7)))) {
		return -EBUSY;
	}

	return videobuf_streamon(get_queue(fh));
}