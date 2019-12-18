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
struct TYPE_4__ {unsigned int offset; } ;
struct v4l2_buffer {scalar_t__ type; unsigned int index; unsigned int length; TYPE_2__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  flags; } ;
struct go7007_file {unsigned int buf_count; int /*<<< orphan*/  lock; TYPE_1__* bufs; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int state; scalar_t__ mapped; } ;

/* Variables and functions */
#define  BUF_STATE_DONE 129 
#define  BUF_STATE_QUEUED 128 
 int EINVAL ; 
 unsigned int GO7007_BUF_SIZE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  memset (struct v4l2_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *priv,
			   struct v4l2_buffer *buf)
{
	struct go7007_file *gofh = priv;
	int retval = -EINVAL;
	unsigned int index;

	if (buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return retval;

	index = buf->index;

	mutex_lock(&gofh->lock);
	if (index >= gofh->buf_count)
		goto unlock_and_return;

	memset(buf, 0, sizeof(*buf));
	buf->index = index;
	buf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	switch (gofh->bufs[index].state) {
	case BUF_STATE_QUEUED:
		buf->flags = V4L2_BUF_FLAG_QUEUED;
		break;
	case BUF_STATE_DONE:
		buf->flags = V4L2_BUF_FLAG_DONE;
		break;
	default:
		buf->flags = 0;
	}

	if (gofh->bufs[index].mapped)
		buf->flags |= V4L2_BUF_FLAG_MAPPED;
	buf->memory = V4L2_MEMORY_MMAP;
	buf->m.offset = index * GO7007_BUF_SIZE;
	buf->length = GO7007_BUF_SIZE;
	mutex_unlock(&gofh->lock);

	return 0;

unlock_and_return:
	mutex_unlock(&gofh->lock);
	return retval;
}