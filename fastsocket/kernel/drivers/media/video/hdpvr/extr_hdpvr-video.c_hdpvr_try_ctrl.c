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
typedef  int uint ;
struct v4l2_ext_control {int id; int value; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 133 
#define  V4L2_CID_MPEG_STREAM_TYPE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 130 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 129 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 128 
 int V4L2_MPEG_AUDIO_ENCODING_AAC ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC ; 

__attribute__((used)) static int hdpvr_try_ctrl(struct v4l2_ext_control *ctrl, int ac3)
{
	int ret = -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		if (ctrl->value == V4L2_MPEG_AUDIO_ENCODING_AAC ||
		    (ac3 && ctrl->value == V4L2_MPEG_AUDIO_ENCODING_AC3))
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		if (ctrl->value == V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC)
			ret = 0;
		break;
/* 	case V4L2_CID_MPEG_VIDEO_B_FRAMES: */
/* 		if (ctrl->value == 0 || ctrl->value == 128) */
/* 			ret = 0; */
/* 		break; */
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		if (ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ||
		    ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR)
			ret = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
	{
		uint bitrate = ctrl->value / 100000;
		if (bitrate >= 10 && bitrate <= 135)
			ret = 0;
		break;
	}
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
	{
		uint peak_bitrate = ctrl->value / 100000;
		if (peak_bitrate >= 10 && peak_bitrate <= 202)
			ret = 0;
		break;
	}
	case V4L2_CID_MPEG_STREAM_TYPE:
		if (ctrl->value == V4L2_MPEG_STREAM_TYPE_MPEG2_TS)
			ret = 0;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}