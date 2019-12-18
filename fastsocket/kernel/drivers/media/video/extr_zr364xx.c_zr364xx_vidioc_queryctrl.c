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
struct zr364xx_camera {TYPE_1__ mode; } ;
struct v4l2_queryctrl {int id; int maximum; int step; int /*<<< orphan*/  flags; int /*<<< orphan*/  default_value; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  V4L2_CID_BRIGHTNESS 128 
 int /*<<< orphan*/  V4L2_CTRL_TYPE_INTEGER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct zr364xx_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int zr364xx_vidioc_queryctrl(struct file *file, void *priv,
				    struct v4l2_queryctrl *c)
{
	struct zr364xx_camera *cam;

	if (file == NULL)
		return -ENODEV;
	cam = video_drvdata(file);

	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Brightness");
		c->minimum = 0;
		c->maximum = 127;
		c->step = 1;
		c->default_value = cam->mode.brightness;
		c->flags = 0;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}