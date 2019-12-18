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
struct v4l2_ext_control {int value; int id; } ;
struct saa6752hs_mpeg_params {int ts_pid_pmt; int ts_pid_audio; int ts_pid_video; int ts_pid_pcr; int au_encoding; int au_l2_bitrate; int au_ac3_bitrate; int vi_aspect; int vi_bitrate; int vi_bitrate_peak; int vi_bitrate_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int MPEG_PID_MAX ; 
 int MPEG_VIDEO_TARGET_BITRATE_MAX ; 
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
 int V4L2_MPEG_AUDIO_AC3_BITRATE_256K ; 
 int V4L2_MPEG_AUDIO_AC3_BITRATE_384K ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_256K ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_384K ; 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_ASPECT_16x9 ; 
 int V4L2_MPEG_VIDEO_ASPECT_4x3 ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 

__attribute__((used)) static int handle_ctrl(int has_ac3, struct saa6752hs_mpeg_params *params,
		struct v4l2_ext_control *ctrl, int set)
{
	int old = 0, new;

	new = ctrl->value;
	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		old = V4L2_MPEG_STREAM_TYPE_MPEG2_TS;
		if (set && new != old)
			return -ERANGE;
		new = old;
		break;
	case V4L2_CID_MPEG_STREAM_PID_PMT:
		old = params->ts_pid_pmt;
		if (set && new > MPEG_PID_MAX)
			return -ERANGE;
		if (new > MPEG_PID_MAX)
			new = MPEG_PID_MAX;
		params->ts_pid_pmt = new;
		break;
	case V4L2_CID_MPEG_STREAM_PID_AUDIO:
		old = params->ts_pid_audio;
		if (set && new > MPEG_PID_MAX)
			return -ERANGE;
		if (new > MPEG_PID_MAX)
			new = MPEG_PID_MAX;
		params->ts_pid_audio = new;
		break;
	case V4L2_CID_MPEG_STREAM_PID_VIDEO:
		old = params->ts_pid_video;
		if (set && new > MPEG_PID_MAX)
			return -ERANGE;
		if (new > MPEG_PID_MAX)
			new = MPEG_PID_MAX;
		params->ts_pid_video = new;
		break;
	case V4L2_CID_MPEG_STREAM_PID_PCR:
		old = params->ts_pid_pcr;
		if (set && new > MPEG_PID_MAX)
			return -ERANGE;
		if (new > MPEG_PID_MAX)
			new = MPEG_PID_MAX;
		params->ts_pid_pcr = new;
		break;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		old = params->au_encoding;
		if (set && new != V4L2_MPEG_AUDIO_ENCODING_LAYER_2 &&
		    (!has_ac3 || new != V4L2_MPEG_AUDIO_ENCODING_AC3))
			return -ERANGE;
		params->au_encoding = new;
		break;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		old = params->au_l2_bitrate;
		if (set && new != V4L2_MPEG_AUDIO_L2_BITRATE_256K &&
			   new != V4L2_MPEG_AUDIO_L2_BITRATE_384K)
			return -ERANGE;
		if (new <= V4L2_MPEG_AUDIO_L2_BITRATE_256K)
			new = V4L2_MPEG_AUDIO_L2_BITRATE_256K;
		else
			new = V4L2_MPEG_AUDIO_L2_BITRATE_384K;
		params->au_l2_bitrate = new;
		break;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		if (!has_ac3)
			return -EINVAL;
		old = params->au_ac3_bitrate;
		if (set && new != V4L2_MPEG_AUDIO_AC3_BITRATE_256K &&
			   new != V4L2_MPEG_AUDIO_AC3_BITRATE_384K)
			return -ERANGE;
		if (new <= V4L2_MPEG_AUDIO_AC3_BITRATE_256K)
			new = V4L2_MPEG_AUDIO_AC3_BITRATE_256K;
		else
			new = V4L2_MPEG_AUDIO_AC3_BITRATE_384K;
		params->au_ac3_bitrate = new;
		break;
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		old = V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000;
		if (set && new != old)
			return -ERANGE;
		new = old;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		old = V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		if (set && new != old)
			return -ERANGE;
		new = old;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		old = params->vi_aspect;
		if (set && new != V4L2_MPEG_VIDEO_ASPECT_16x9 &&
			   new != V4L2_MPEG_VIDEO_ASPECT_4x3)
			return -ERANGE;
		if (new != V4L2_MPEG_VIDEO_ASPECT_16x9)
			new = V4L2_MPEG_VIDEO_ASPECT_4x3;
		params->vi_aspect = new;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		old = params->vi_bitrate * 1000;
		new = 1000 * (new / 1000);
		if (set && new > MPEG_VIDEO_TARGET_BITRATE_MAX * 1000)
			return -ERANGE;
		if (new > MPEG_VIDEO_TARGET_BITRATE_MAX * 1000)
			new = MPEG_VIDEO_TARGET_BITRATE_MAX * 1000;
		params->vi_bitrate = new / 1000;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		old = params->vi_bitrate_peak * 1000;
		new = 1000 * (new / 1000);
		if (set && new > MPEG_VIDEO_TARGET_BITRATE_MAX * 1000)
			return -ERANGE;
		if (new > MPEG_VIDEO_TARGET_BITRATE_MAX * 1000)
			new = MPEG_VIDEO_TARGET_BITRATE_MAX * 1000;
		params->vi_bitrate_peak = new / 1000;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		old = params->vi_bitrate_mode;
		params->vi_bitrate_mode = new;
		break;
	default:
		return -EINVAL;
	}
	ctrl->value = new;
	return 0;
}