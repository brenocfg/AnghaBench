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
struct v4l2_buffer {int /*<<< orphan*/  flags; } ;
struct uvc_buffer {int state; scalar_t__ vma_use_count; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
#define  UVC_BUF_STATE_ACTIVE 133 
#define  UVC_BUF_STATE_DONE 132 
#define  UVC_BUF_STATE_ERROR 131 
#define  UVC_BUF_STATE_IDLE 130 
#define  UVC_BUF_STATE_QUEUED 129 
#define  UVC_BUF_STATE_READY 128 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
 int /*<<< orphan*/  memcpy (struct v4l2_buffer*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __uvc_query_buffer(struct uvc_buffer *buf,
		struct v4l2_buffer *v4l2_buf)
{
	memcpy(v4l2_buf, &buf->buf, sizeof *v4l2_buf);

	if (buf->vma_use_count)
		v4l2_buf->flags |= V4L2_BUF_FLAG_MAPPED;

	switch (buf->state) {
	case UVC_BUF_STATE_ERROR:
	case UVC_BUF_STATE_DONE:
		v4l2_buf->flags |= V4L2_BUF_FLAG_DONE;
		break;
	case UVC_BUF_STATE_QUEUED:
	case UVC_BUF_STATE_ACTIVE:
	case UVC_BUF_STATE_READY:
		v4l2_buf->flags |= V4L2_BUF_FLAG_QUEUED;
		break;
	case UVC_BUF_STATE_IDLE:
	default:
		break;
	}
}