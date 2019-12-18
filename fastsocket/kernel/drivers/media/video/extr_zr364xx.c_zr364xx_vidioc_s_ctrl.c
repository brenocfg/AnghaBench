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
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct zr364xx_camera {int /*<<< orphan*/  lock; int /*<<< orphan*/  udev; TYPE_1__ mode; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  V4L2_CID_BRIGHTNESS 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_control_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zr364xx_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int zr364xx_vidioc_s_ctrl(struct file *file, void *priv,
				 struct v4l2_control *c)
{
	struct zr364xx_camera *cam;
	int temp;

	if (file == NULL)
		return -ENODEV;
	cam = video_drvdata(file);

	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		cam->mode.brightness = c->value;
		/* hardware brightness */
		mutex_lock(&cam->lock);
		send_control_msg(cam->udev, 1, 0x2001, 0, NULL, 0);
		temp = (0x60 << 8) + 127 - cam->mode.brightness;
		send_control_msg(cam->udev, 1, temp, 0, NULL, 0);
		mutex_unlock(&cam->lock);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}