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
struct v4l2_tuner {scalar_t__ index; int audmode; } ;
struct si470x_device {TYPE_1__* videodev; int /*<<< orphan*/ * registers; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t POWERCFG ; 
 int /*<<< orphan*/  POWERCFG_MONO ; 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int si470x_disconnect_check (struct si470x_device*) ; 
 int si470x_set_register (struct si470x_device*,size_t) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_s_tuner(struct file *file, void *priv,
		struct v4l2_tuner *tuner)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = -EINVAL;

	/* safety checks */
	retval = si470x_disconnect_check(radio);
	if (retval)
		goto done;

	if (tuner->index != 0)
		goto done;

	/* mono/stereo selector */
	switch (tuner->audmode) {
	case V4L2_TUNER_MODE_MONO:
		radio->registers[POWERCFG] |= POWERCFG_MONO;  /* force mono */
		break;
	case V4L2_TUNER_MODE_STEREO:
		radio->registers[POWERCFG] &= ~POWERCFG_MONO; /* try stereo */
		break;
	default:
		goto done;
	}

	retval = si470x_set_register(radio, POWERCFG);

done:
	if (retval < 0)
		dev_warn(&radio->videodev->dev,
			"set tuner failed with %d\n", retval);
	return retval;
}