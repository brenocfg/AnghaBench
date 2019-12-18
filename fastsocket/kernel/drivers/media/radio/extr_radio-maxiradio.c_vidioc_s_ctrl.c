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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct maxiradio {int /*<<< orphan*/  lock; int /*<<< orphan*/  freq; int /*<<< orphan*/  muted; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_freq (struct maxiradio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_power (struct maxiradio*,int /*<<< orphan*/ ) ; 
 struct maxiradio* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
		struct v4l2_control *ctrl)
{
	struct maxiradio *dev = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		mutex_lock(&dev->lock);
		dev->muted = ctrl->value;
		if (dev->muted)
			turn_power(dev, 0);
		else
			set_freq(dev, dev->freq);
		mutex_unlock(&dev->lock);
		return 0;
	}

	return -EINVAL;
}