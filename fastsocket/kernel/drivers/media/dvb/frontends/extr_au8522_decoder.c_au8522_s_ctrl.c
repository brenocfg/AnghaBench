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
struct v4l2_control {int id; int value; } ;
struct au8522_state {int brightness; int contrast; int saturation; int hue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_TVDEC_BRIGHTNESS_REG00AH ; 
 int /*<<< orphan*/  AU8522_TVDEC_CONTRAST_REG00BH ; 
 int /*<<< orphan*/  AU8522_TVDEC_HUE_H_REG00EH ; 
 int /*<<< orphan*/  AU8522_TVDEC_HUE_L_REG00FH ; 
 int /*<<< orphan*/  AU8522_TVDEC_SATURATION_CB_REG00CH ; 
 int /*<<< orphan*/  AU8522_TVDEC_SATURATION_CR_REG00DH ; 
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
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct au8522_state *state = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		state->brightness = ctrl->value;
		au8522_writereg(state, AU8522_TVDEC_BRIGHTNESS_REG00AH,
				ctrl->value - 128);
		break;
	case V4L2_CID_CONTRAST:
		state->contrast = ctrl->value;
		au8522_writereg(state, AU8522_TVDEC_CONTRAST_REG00BH,
				ctrl->value);
		break;
	case V4L2_CID_SATURATION:
		state->saturation = ctrl->value;
		au8522_writereg(state, AU8522_TVDEC_SATURATION_CB_REG00CH,
				ctrl->value);
		au8522_writereg(state, AU8522_TVDEC_SATURATION_CR_REG00DH,
				ctrl->value);
		break;
	case V4L2_CID_HUE:
		state->hue = ctrl->value;
		au8522_writereg(state, AU8522_TVDEC_HUE_H_REG00EH,
				ctrl->value >> 8);
		au8522_writereg(state, AU8522_TVDEC_HUE_L_REG00FH,
				ctrl->value & 0xFF);
		break;
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_MUTE:
		/* Not yet implemented */
	default:
		return -EINVAL;
	}

	return 0;
}