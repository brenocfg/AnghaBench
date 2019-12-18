#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_buffer {size_t index; } ;
struct file {struct cafe_camera* private_data; } ;
struct cafe_camera {size_t n_sbufs; int /*<<< orphan*/  s_mutex; TYPE_1__* sb_bufs; } ;
struct TYPE_2__ {struct v4l2_buffer v4lbuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cafe_vidioc_querybuf(struct file *filp, void *priv,
		struct v4l2_buffer *buf)
{
	struct cafe_camera *cam = filp->private_data;
	int ret = -EINVAL;

	mutex_lock(&cam->s_mutex);
	if (buf->index >= cam->n_sbufs)
		goto out;
	*buf = cam->sb_bufs[buf->index].v4lbuf;
	ret = 0;
  out:
	mutex_unlock(&cam->s_mutex);
	return ret;
}