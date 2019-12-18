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
struct saa6752hs_mpeg_params {int ts_pid_pmt; int ts_pid_audio; int ts_pid_video; int ts_pid_pcr; int au_encoding; int au_l2_bitrate; int au_ac3_bitrate; int vi_aspect; int vi_bitrate; int vi_bitrate_peak; int vi_bitrate_mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 141 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 140 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 139 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 138 
#define  V4L2_CID_MPEG_STREAM_PID_AUDIO 137 
#define  V4L2_CID_MPEG_STREAM_PID_PCR 136 
#define  V4L2_CID_MPEG_STREAM_PID_PMT 135 
#define  V4L2_CID_MPEG_STREAM_PID_VIDEO 134 
#define  V4L2_CID_MPEG_STREAM_TYPE 133 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 130 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 129 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 128 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 

__attribute__((used)) static int get_ctrl(int has_ac3, struct saa6752hs_mpeg_params *params,
		struct v4l2_ext_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = V4L2_MPEG_STREAM_TYPE_MPEG2_TS;
		break;
	case V4L2_CID_MPEG_STREAM_PID_PMT:
		ctrl->value = params->ts_pid_pmt;
		break;
	case V4L2_CID_MPEG_STREAM_PID_AUDIO:
		ctrl->value = params->ts_pid_audio;
		break;
	case V4L2_CID_MPEG_STREAM_PID_VIDEO:
		ctrl->value = params->ts_pid_video;
		break;
	case V4L2_CID_MPEG_STREAM_PID_PCR:
		ctrl->value = params->ts_pid_pcr;
		break;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		ctrl->value = params->au_encoding;
		break;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		ctrl->value = params->au_l2_bitrate;
		break;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		if (!has_ac3)
			return -EINVAL;
		ctrl->value = params->au_ac3_bitrate;
		break;
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		ctrl->value = V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		ctrl->value = V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		ctrl->value = params->vi_aspect;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = params->vi_bitrate * 1000;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctrl->value = params->vi_bitrate_peak * 1000;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctrl->value = params->vi_bitrate_mode;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}