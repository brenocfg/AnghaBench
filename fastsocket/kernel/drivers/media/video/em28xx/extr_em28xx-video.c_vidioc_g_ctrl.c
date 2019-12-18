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
struct v4l2_control {int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct TYPE_2__ {scalar_t__ ac97; } ;
struct em28xx {int /*<<< orphan*/  v4l2_dev; TYPE_1__ audio_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EM28XX_NO_AC97 ; 
 int ac97_get_ctrl (struct em28xx*,struct v4l2_control*) ; 
 int check_dev (struct em28xx*) ; 
 scalar_t__ check_subdev_ctrl (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  g_ctrl ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct em28xx_fh      *fh  = priv;
	struct em28xx         *dev = fh->dev;
	int                   rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;
	rc = 0;

	/* Set an AC97 control */
	if (dev->audio_mode.ac97 != EM28XX_NO_AC97)
		rc = ac97_get_ctrl(dev, ctrl);
	else
		rc = 1;

	/* It were not an AC97 control. Sends it to the v4l2 dev interface */
	if (rc == 1) {
		if (check_subdev_ctrl(dev, ctrl->id))
			return -EINVAL;

		v4l2_device_call_all(&dev->v4l2_dev, 0, core, g_ctrl, ctrl);
		rc = 0;
	}

	return rc;
}