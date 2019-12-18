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
struct v4l2_buffer {size_t index; } ;
struct uvc_video_queue {size_t count; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __uvc_query_buffer (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int uvc_query_buffer(struct uvc_video_queue *queue,
		struct v4l2_buffer *v4l2_buf)
{
	int ret = 0;

	mutex_lock(&queue->mutex);
	if (v4l2_buf->index >= queue->count) {
		ret = -EINVAL;
		goto done;
	}

	__uvc_query_buffer(&queue->buffer[v4l2_buf->index], v4l2_buf);

done:
	mutex_unlock(&queue->mutex);
	return ret;
}