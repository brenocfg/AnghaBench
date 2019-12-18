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
struct file {struct cafe_camera* private_data; } ;
struct cafe_camera {scalar_t__ state; int /*<<< orphan*/  s_mutex; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S_STREAMING ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  cafe_ctlr_stop_dma (struct cafe_camera*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cafe_vidioc_streamoff(struct file *filp, void *priv,
		enum v4l2_buf_type type)
{
	struct cafe_camera *cam = filp->private_data;
	int ret = -EINVAL;

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		goto out;
	mutex_lock(&cam->s_mutex);
	if (cam->state != S_STREAMING)
		goto out_unlock;

	cafe_ctlr_stop_dma(cam);
	ret = 0;

  out_unlock:
	mutex_unlock(&cam->s_mutex);
  out:
	return ret;
}