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
struct v4l2_queryctrl {int id; } ;
struct cx18_av_state {int default_volume; } ;

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
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int cx18_av_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qc)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);

	switch (qc->id) {
	case V4L2_CID_BRIGHTNESS:
		return v4l2_ctrl_query_fill(qc, 0, 255, 1, 128);
	case V4L2_CID_CONTRAST:
	case V4L2_CID_SATURATION:
		return v4l2_ctrl_query_fill(qc, 0, 127, 1, 64);
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(qc, -128, 127, 1, 0);
	default:
		break;
	}

	switch (qc->id) {
	case V4L2_CID_AUDIO_VOLUME:
		return v4l2_ctrl_query_fill(qc, 0, 65535,
			65535 / 100, state->default_volume);
	case V4L2_CID_AUDIO_MUTE:
		return v4l2_ctrl_query_fill(qc, 0, 1, 1, 0);
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
		return v4l2_ctrl_query_fill(qc, 0, 65535, 65535 / 100, 32768);
	default:
		return -EINVAL;
	}
	return -EINVAL;
}