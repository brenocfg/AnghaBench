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
struct v4l2_ext_control {int id; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENCODER_MAX_BITRATE ; 
 int ENCODER_MIN_BITRATE ; 
#define  V4L2_CID_MPEG_AUDIO_MUTE 135 
#define  V4L2_CID_MPEG_STREAM_TYPE 134 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 133 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 130 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 129 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 128 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_PS ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int V4L2_MPEG_VIDEO_ASPECT_221x100 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 

__attribute__((used)) static int saa7164_try_ctrl(struct v4l2_ext_control *ctrl, int ac3)
{
	int ret = -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		if ((ctrl->value >= ENCODER_MIN_BITRATE) &&
			(ctrl->value <= ENCODER_MAX_BITRATE))
			ret = 0;
		break;
	case V4L2_CID_MPEG_STREAM_TYPE:
		if ((ctrl->value == V4L2_MPEG_STREAM_TYPE_MPEG2_PS) ||
			(ctrl->value == V4L2_MPEG_STREAM_TYPE_MPEG2_TS))
			ret = 0;
		break;
	case V4L2_CID_MPEG_AUDIO_MUTE:
		if ((ctrl->value >= 0) &&
			(ctrl->value <= 1))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		if ((ctrl->value >= V4L2_MPEG_VIDEO_ASPECT_1x1) &&
			(ctrl->value <= V4L2_MPEG_VIDEO_ASPECT_221x100))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		if ((ctrl->value >= 0) &&
			(ctrl->value <= 255))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		if ((ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR) ||
			(ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		if ((ctrl->value >= 1) &&
			(ctrl->value <= 3))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		if ((ctrl->value >= ENCODER_MIN_BITRATE) &&
			(ctrl->value <= ENCODER_MAX_BITRATE))
			ret = 0;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}