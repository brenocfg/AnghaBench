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
struct v4l2_streamparm {scalar_t__ type; } ;
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_webcam; } ;
struct em28xx {int /*<<< orphan*/  v4l2_dev; TYPE_1__ board; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  s_parm ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int vidioc_s_parm(struct file *file, void *priv,
			 struct v4l2_streamparm *p)
{
	struct em28xx_fh   *fh  = priv;
	struct em28xx      *dev = fh->dev;

	if (!dev->board.is_webcam)
		return -EINVAL;

	if (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	return v4l2_device_call_until_err(&dev->v4l2_dev, 0, video, s_parm, p);
}