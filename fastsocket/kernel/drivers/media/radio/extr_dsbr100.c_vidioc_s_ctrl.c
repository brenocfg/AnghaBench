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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct file {int dummy; } ;
struct dsbr100_device {TYPE_1__* usbdev; scalar_t__ removed; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dsbr100_start (struct dsbr100_device*) ; 
 int dsbr100_stop (struct dsbr100_device*) ; 
 struct dsbr100_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct dsbr100_device *radio = video_drvdata(file);
	int retval;

	/* safety check */
	if (radio->removed)
		return -EIO;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value) {
			retval = dsbr100_stop(radio);
			if (retval < 0) {
				dev_warn(&radio->usbdev->dev,
					 "Radio did not respond properly\n");
				return -EBUSY;
			}
		} else {
			retval = dsbr100_start(radio);
			if (retval < 0) {
				dev_warn(&radio->usbdev->dev,
					 "Radio did not respond properly\n");
				return -EBUSY;
			}
		}
		return 0;
	}
	return -EINVAL;
}