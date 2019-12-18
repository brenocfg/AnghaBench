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
struct terratec {int /*<<< orphan*/  curvol; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  tt_mute (struct terratec*) ; 
 int /*<<< orphan*/  tt_setvol (struct terratec*,int /*<<< orphan*/ ) ; 
 struct terratec* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
					struct v4l2_control *ctrl)
{
	struct terratec *tt = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value)
			tt_mute(tt);
		else
			tt_setvol(tt,tt->curvol);
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		tt_setvol(tt,ctrl->value);
		return 0;
	}
	return -EINVAL;
}