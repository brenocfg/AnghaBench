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
struct trust {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  tr_setbass (struct trust*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_setmute (struct trust*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_settreble (struct trust*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_setvol (struct trust*,int /*<<< orphan*/ ) ; 
 struct trust* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct trust *tr = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		tr_setmute(tr, ctrl->value);
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		tr_setvol(tr, ctrl->value);
		return 0;
	case V4L2_CID_AUDIO_BASS:
		tr_setbass(tr, ctrl->value);
		return 0;
	case V4L2_CID_AUDIO_TREBLE:
		tr_settreble(tr, ctrl->value);
		return 0;
	}
	return -EINVAL;
}