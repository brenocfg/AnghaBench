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
struct typhoon {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  typhoon_mute (struct typhoon*) ; 
 int /*<<< orphan*/  typhoon_setvol (struct typhoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_unmute (struct typhoon*) ; 
 struct typhoon* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl (struct file *file, void *priv,
					struct v4l2_control *ctrl)
{
	struct typhoon *dev = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value)
			typhoon_mute(dev);
		else
			typhoon_unmute(dev);
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		typhoon_setvol(dev, ctrl->value);
		return 0;
	}
	return -EINVAL;
}