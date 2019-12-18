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
struct videobuf_queue {scalar_t__ type; } ;
struct v4l2_m2m_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct v4l2_buffer {scalar_t__ memory; TYPE_1__ m; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ DST_QUEUE_OFF_BASE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 struct videobuf_queue* v4l2_m2m_get_vq (struct v4l2_m2m_ctx*,int /*<<< orphan*/ ) ; 
 int videobuf_querybuf (struct videobuf_queue*,struct v4l2_buffer*) ; 

int v4l2_m2m_querybuf(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
		      struct v4l2_buffer *buf)
{
	struct videobuf_queue *vq;
	int ret;

	vq = v4l2_m2m_get_vq(m2m_ctx, buf->type);
	ret = videobuf_querybuf(vq, buf);

	if (buf->memory == V4L2_MEMORY_MMAP
	    && vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		buf->m.offset += DST_QUEUE_OFF_BASE;
	}

	return ret;
}