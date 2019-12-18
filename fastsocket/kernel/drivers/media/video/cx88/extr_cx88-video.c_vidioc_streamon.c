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
struct cx8800_fh {scalar_t__ type; struct cx8800_dev* dev; } ;
struct cx8800_dev {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  get_queue (struct cx8800_fh*) ; 
 int /*<<< orphan*/  get_ressource (struct cx8800_fh*) ; 
 int /*<<< orphan*/  res_get (struct cx8800_dev*,struct cx8800_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int videobuf_streamon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct cx8800_fh  *fh   = priv;
	struct cx8800_dev *dev  = fh->dev;

	/* We should remember that this driver also supports teletext,  */
	/* so we have to test if the v4l2_buf_type is VBI capture data. */
	if (unlikely((fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
		     (fh->type != V4L2_BUF_TYPE_VBI_CAPTURE)))
		return -EINVAL;

	if (unlikely(i != fh->type))
		return -EINVAL;

	if (unlikely(!res_get(dev,fh,get_ressource(fh))))
		return -EBUSY;
	return videobuf_streamon(get_queue(fh));
}