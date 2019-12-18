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
struct v4l2_requestbuffers {scalar_t__ type; scalar_t__ memory; int /*<<< orphan*/  reserved; int /*<<< orphan*/  count; } ;
struct camera_data {int /*<<< orphan*/  num_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ioctl_reqbufs(void *arg,struct camera_data *cam)
{
	struct v4l2_requestbuffers *req = arg;

	if(req->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   req->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;

	DBG("REQBUFS requested:%d returning:%d\n", req->count, cam->num_frames);
	req->count = cam->num_frames;
	memset(&req->reserved, 0, sizeof(req->reserved));

	return 0;
}