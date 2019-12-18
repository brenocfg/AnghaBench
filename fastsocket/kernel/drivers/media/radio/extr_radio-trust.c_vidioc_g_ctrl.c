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
struct trust {int curmute; int curvol; int curbass; int curtreble; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 struct trust* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct trust *tr = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		ctrl->value = tr->curmute;
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		ctrl->value = tr->curvol * 2048;
		return 0;
	case V4L2_CID_AUDIO_BASS:
		ctrl->value = tr->curbass * 4370;
		return 0;
	case V4L2_CID_AUDIO_TREBLE:
		ctrl->value = tr->curtreble * 4370;
		return 0;
	}
	return -EINVAL;
}