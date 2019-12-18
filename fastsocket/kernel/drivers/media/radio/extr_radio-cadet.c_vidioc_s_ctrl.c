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
struct v4l2_control {int id; int value; } ;
struct file {int dummy; } ;
struct cadet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  cadet_setvol (struct cadet*,int) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct cadet *dev = video_drvdata(file);

	switch (ctrl->id){
	case V4L2_CID_AUDIO_MUTE: /* TODO: Handle this correctly */
		if (ctrl->value)
			cadet_setvol(dev, 0);
		else
			cadet_setvol(dev, 0xffff);
		break;
	case V4L2_CID_AUDIO_VOLUME:
		cadet_setvol(dev, ctrl->value);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}