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
struct adv7343_state {int /*<<< orphan*/  gain; int /*<<< orphan*/  hue; int /*<<< orphan*/  bright; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MAX ; 
 int /*<<< orphan*/  ADV7343_BRIGHTNESS_MIN ; 
 int /*<<< orphan*/  ADV7343_DAC2_OUTPUT_LEVEL ; 
 int /*<<< orphan*/  ADV7343_GAIN_MAX ; 
 int /*<<< orphan*/  ADV7343_GAIN_MIN ; 
 int /*<<< orphan*/  ADV7343_HUE_MAX ; 
 int /*<<< orphan*/  ADV7343_HUE_MIN ; 
 int /*<<< orphan*/  ADV7343_SD_BRIGHTNESS_WSS ; 
 int /*<<< orphan*/  ADV7343_SD_HUE_REG ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NEGATIVE_GAIN_MIN ; 
 int /*<<< orphan*/  POSITIVE_GAIN_MAX ; 
#define  V4L2_CID_BRIGHTNESS 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_HUE 128 
 int adv7343_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 struct adv7343_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int adv7343_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct adv7343_state *state = to_state(sd);
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		if (ctrl->value < ADV7343_BRIGHTNESS_MIN ||
					ctrl->value > ADV7343_BRIGHTNESS_MAX) {
			v4l2_dbg(1, debug, sd,
					"invalid brightness settings %d\n",
								ctrl->value);
			return -ERANGE;
		}

		state->bright = ctrl->value;
		err = adv7343_write(sd, ADV7343_SD_BRIGHTNESS_WSS,
					state->bright);
		break;

	case V4L2_CID_HUE:
		if (ctrl->value < ADV7343_HUE_MIN ||
					ctrl->value > ADV7343_HUE_MAX) {
			v4l2_dbg(1, debug, sd, "invalid hue settings %d\n",
								ctrl->value);
			return -ERANGE;
		}

		state->hue = ctrl->value;
		err = adv7343_write(sd, ADV7343_SD_HUE_REG, state->hue);
		break;

	case V4L2_CID_GAIN:
		if (ctrl->value < ADV7343_GAIN_MIN ||
					ctrl->value > ADV7343_GAIN_MAX) {
			v4l2_dbg(1, debug, sd, "invalid gain settings %d\n",
								ctrl->value);
			return -ERANGE;
		}

		if ((ctrl->value > POSITIVE_GAIN_MAX) &&
			(ctrl->value < NEGATIVE_GAIN_MIN)) {
			v4l2_dbg(1, debug, sd,
				"gain settings not within the specified range\n");
			return -ERANGE;
		}

		state->gain = ctrl->value;
		err = adv7343_write(sd, ADV7343_DAC2_OUTPUT_LEVEL, state->gain);
		break;

	default:
		return -EINVAL;
	}

	if (err < 0)
		v4l2_err(sd, "Failed to set the encoder controls\n");

	return err;
}