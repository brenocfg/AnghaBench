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
struct v4l2_buffer {scalar_t__ type; scalar_t__ memory; size_t index; } ;
struct camera_data {size_t num_frames; TYPE_1__* buffers; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,size_t) ; 
 int EINVAL ; 
 scalar_t__ FRAME_EMPTY ; 
 scalar_t__ FRAME_READY ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 

__attribute__((used)) static int ioctl_qbuf(void *arg,struct camera_data *cam)
{
	struct v4l2_buffer *buf = arg;

	if(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->memory != V4L2_MEMORY_MMAP ||
	   buf->index > cam->num_frames)
		return -EINVAL;

	DBG("QBUF #%d\n", buf->index);

	if(cam->buffers[buf->index].status == FRAME_READY)
		cam->buffers[buf->index].status = FRAME_EMPTY;

	return 0;
}