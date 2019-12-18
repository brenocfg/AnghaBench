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
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_VIDEO10 ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  get_queue (struct cx25821_fh*) ; 
 int get_resource (struct cx25821_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct cx25821_dev*,struct cx25821_fh*,int) ; 
 int videobuf_streamoff (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct cx25821_fh *fh = priv;
	struct cx25821_dev *dev = fh->dev;
	int err, res;

	if (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (i != fh->type)
		return -EINVAL;

	res = get_resource(fh, RESOURCE_VIDEO10);
	err = videobuf_streamoff(get_queue(fh));
	if (err < 0)
		return err;
	res_free(dev, fh, res);
	return 0;
}