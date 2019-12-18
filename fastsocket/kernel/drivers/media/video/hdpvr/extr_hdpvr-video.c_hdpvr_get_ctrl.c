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
struct hdpvr_options {int audio_codec; int bitrate; int peak_bitrate; int /*<<< orphan*/  bitrate_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDPVR_CONSTANT ; 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 133 
#define  V4L2_CID_MPEG_STREAM_TYPE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 130 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 129 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 128 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC ; 

__attribute__((used)) static int hdpvr_get_ctrl(struct hdpvr_options *opt,
			  struct v4l2_ext_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		ctrl->value = opt->audio_codec;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		ctrl->value = V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC;
		break;
/* 	case V4L2_CID_MPEG_VIDEO_B_FRAMES: */
/* 		ctrl->value = (opt->gop_mode & 0x2) ? 0 : 128; */
/* 		break; */
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctrl->value = opt->bitrate_mode == HDPVR_CONSTANT
			? V4L2_MPEG_VIDEO_BITRATE_MODE_CBR
			: V4L2_MPEG_VIDEO_BITRATE_MODE_VBR;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = opt->bitrate * 100000;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctrl->value = opt->peak_bitrate * 100000;
		break;
	case V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = V4L2_MPEG_STREAM_TYPE_MPEG2_TS;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}