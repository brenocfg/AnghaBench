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
struct v4l2_requestbuffers {scalar_t__ type; scalar_t__ memory; scalar_t__ mapped; unsigned int count; unsigned int index; int /*<<< orphan*/  state; struct go7007* go; } ;
struct go7007_file {unsigned int buf_count; int /*<<< orphan*/  lock; struct v4l2_requestbuffers* bufs; struct go7007* go; } ;
struct go7007_buffer {int dummy; } ;
struct go7007 {int in_use; int /*<<< orphan*/  hw_lock; scalar_t__ streaming; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_STATE_IDLE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  kfree (struct v4l2_requestbuffers*) ; 
 struct v4l2_requestbuffers* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_requestbuffers*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *req)
{
	struct go7007_file *gofh = priv;
	struct go7007 *go = gofh->go;
	int retval = -EBUSY;
	unsigned int count, i;

	if (go->streaming)
		return retval;

	if (req->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
			req->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;

	mutex_lock(&gofh->lock);
	for (i = 0; i < gofh->buf_count; ++i)
		if (gofh->bufs[i].mapped > 0)
			goto unlock_and_return;

	mutex_lock(&go->hw_lock);
	if (go->in_use > 0 && gofh->buf_count == 0) {
		mutex_unlock(&go->hw_lock);
		goto unlock_and_return;
	}

	if (gofh->buf_count > 0)
		kfree(gofh->bufs);

	retval = -ENOMEM;
	count = req->count;
	if (count > 0) {
		if (count < 2)
			count = 2;
		if (count > 32)
			count = 32;

		gofh->bufs = kmalloc(count * sizeof(struct go7007_buffer),
				     GFP_KERNEL);

		if (!gofh->bufs) {
			mutex_unlock(&go->hw_lock);
			goto unlock_and_return;
		}

		memset(gofh->bufs, 0, count * sizeof(struct go7007_buffer));

		for (i = 0; i < count; ++i) {
			gofh->bufs[i].go = go;
			gofh->bufs[i].index = i;
			gofh->bufs[i].state = BUF_STATE_IDLE;
			gofh->bufs[i].mapped = 0;
		}

		go->in_use = 1;
	} else {
		go->in_use = 0;
	}

	gofh->buf_count = count;
	mutex_unlock(&go->hw_lock);
	mutex_unlock(&gofh->lock);

	memset(req, 0, sizeof(*req));

	req->count = count;
	req->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req->memory = V4L2_MEMORY_MMAP;

	return 0;

unlock_and_return:
	mutex_unlock(&gofh->lock);
	return retval;
}