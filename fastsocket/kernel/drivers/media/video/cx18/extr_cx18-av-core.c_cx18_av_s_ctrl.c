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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_ERR_DEV (struct v4l2_subdev*,char*,int) ; 
 int EINVAL ; 
 int ERANGE ; 
#define  V4L2_CID_AUDIO_BALANCE 136 
#define  V4L2_CID_AUDIO_BASS 135 
#define  V4L2_CID_AUDIO_MUTE 134 
#define  V4L2_CID_AUDIO_TREBLE 133 
#define  V4L2_CID_AUDIO_VOLUME 132 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int cx18_av_audio_s_ctrl (struct cx18*,struct v4l2_control*) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		if (ctrl->value < 0 || ctrl->value > 255) {
			CX18_ERR_DEV(sd, "invalid brightness setting %d\n",
				     ctrl->value);
			return -ERANGE;
		}

		cx18_av_write(cx, 0x414, ctrl->value - 128);
		break;

	case V4L2_CID_CONTRAST:
		if (ctrl->value < 0 || ctrl->value > 127) {
			CX18_ERR_DEV(sd, "invalid contrast setting %d\n",
				     ctrl->value);
			return -ERANGE;
		}

		cx18_av_write(cx, 0x415, ctrl->value << 1);
		break;

	case V4L2_CID_SATURATION:
		if (ctrl->value < 0 || ctrl->value > 127) {
			CX18_ERR_DEV(sd, "invalid saturation setting %d\n",
				     ctrl->value);
			return -ERANGE;
		}

		cx18_av_write(cx, 0x420, ctrl->value << 1);
		cx18_av_write(cx, 0x421, ctrl->value << 1);
		break;

	case V4L2_CID_HUE:
		if (ctrl->value < -128 || ctrl->value > 127) {
			CX18_ERR_DEV(sd, "invalid hue setting %d\n",
				     ctrl->value);
			return -ERANGE;
		}

		cx18_av_write(cx, 0x422, ctrl->value);
		break;

	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_MUTE:
		return cx18_av_audio_s_ctrl(cx, ctrl);

	default:
		return -EINVAL;
	}
	return 0;
}