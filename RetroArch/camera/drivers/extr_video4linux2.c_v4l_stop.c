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
struct TYPE_2__ {int ready; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ video4linux_t ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 int xioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void v4l_stop(void *data)
{
   video4linux_t *v4l = (video4linux_t*)data;
   enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

   if (xioctl(v4l->fd, VIDIOC_STREAMOFF, &type) == -1)
      RARCH_ERR("[V4L2]: Error - VIDIOC_STREAMOFF.\n");

   v4l->ready = false;
}