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
struct v4l2_buffer {scalar_t__ memory; size_t index; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  grabq; TYPE_1__* grab_buffer; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEYE_BUF_UNUSED ; 
 scalar_t__ MEYE_BUF_USING ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 size_t gbuffers ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_qbuf(struct file *file, void *fh, struct v4l2_buffer *buf)
{
	if (buf->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;

	if (buf->index >= gbuffers)
		return -EINVAL;

	if (meye.grab_buffer[buf->index].state != MEYE_BUF_UNUSED)
		return -EINVAL;

	mutex_lock(&meye.lock);
	buf->flags |= V4L2_BUF_FLAG_QUEUED;
	buf->flags &= ~V4L2_BUF_FLAG_DONE;
	meye.grab_buffer[buf->index].state = MEYE_BUF_USING;
	kfifo_put(meye.grabq, (unsigned char *)&buf->index, sizeof(int));
	mutex_unlock(&meye.lock);

	return 0;
}