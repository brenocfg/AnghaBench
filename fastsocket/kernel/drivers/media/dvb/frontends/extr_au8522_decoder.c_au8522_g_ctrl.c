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
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct au8522_state {int /*<<< orphan*/  hue; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 136 
#define  V4L2_CID_AUDIO_BASS 135 
#define  V4L2_CID_AUDIO_MUTE 134 
#define  V4L2_CID_AUDIO_TREBLE 133 
#define  V4L2_CID_AUDIO_VOLUME 132 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct au8522_state *state = to_state(sd);

	/* Note that we are using values cached in the state structure instead
	   of reading the registers due to issues with i2c reads not working
	   properly/consistently yet on the HVR-950q */

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ctrl->value = state->brightness;
		break;
	case V4L2_CID_CONTRAST:
		ctrl->value = state->contrast;
		break;
	case V4L2_CID_SATURATION:
		ctrl->value = state->saturation;
		break;
	case V4L2_CID_HUE:
		ctrl->value = state->hue;
		break;
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_MUTE:
		/* Not yet supported */
	default:
		return -EINVAL;
	}

	return 0;
}