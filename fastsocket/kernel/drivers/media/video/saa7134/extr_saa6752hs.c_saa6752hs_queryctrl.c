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
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; } ;
struct saa6752hs_mpeg_params {int vi_bitrate_mode; } ;
struct saa6752hs_state {int /*<<< orphan*/  has_ac3; struct saa6752hs_mpeg_params params; } ;

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
 int /*<<< orphan*/  V4L2_CTRL_FLAG_INACTIVE ; 
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
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 struct saa6752hs_state* to_state (struct v4l2_subdev*) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int saa6752hs_queryctrl(struct v4l2_subdev *sd, struct v4l2_queryctrl *qctrl)
{
	struct saa6752hs_state *h = to_state(sd);
	struct saa6752hs_mpeg_params *params = &h->params;
	int err;

	switch (qctrl->id) {
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
				h->has_ac3 ? V4L2_MPEG_AUDIO_ENCODING_AC3 :
					V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
				1, V4L2_MPEG_AUDIO_ENCODING_LAYER_2);

	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_L2_BITRATE_256K,
				V4L2_MPEG_AUDIO_L2_BITRATE_384K, 1,
				V4L2_MPEG_AUDIO_L2_BITRATE_256K);

	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		if (!h->has_ac3)
			return -EINVAL;
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_AC3_BITRATE_256K,
				V4L2_MPEG_AUDIO_AC3_BITRATE_384K, 1,
				V4L2_MPEG_AUDIO_AC3_BITRATE_256K);

	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000, 1,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);

	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_2,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_2, 1,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_2);

	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_ASPECT_4x3,
				V4L2_MPEG_VIDEO_ASPECT_16x9, 1,
				V4L2_MPEG_VIDEO_ASPECT_4x3);

	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		err = v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 8000000);
		if (err == 0 &&
		    params->vi_bitrate_mode ==
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return err;

	case V4L2_CID_MPEG_STREAM_TYPE:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_STREAM_TYPE_MPEG2_TS,
				V4L2_MPEG_STREAM_TYPE_MPEG2_TS, 1,
				V4L2_MPEG_STREAM_TYPE_MPEG2_TS);

	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 1,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		return v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 6000000);
	case V4L2_CID_MPEG_STREAM_PID_PMT:
		return v4l2_ctrl_query_fill(qctrl, 0, (1 << 14) - 1, 1, 16);
	case V4L2_CID_MPEG_STREAM_PID_AUDIO:
		return v4l2_ctrl_query_fill(qctrl, 0, (1 << 14) - 1, 1, 260);
	case V4L2_CID_MPEG_STREAM_PID_VIDEO:
		return v4l2_ctrl_query_fill(qctrl, 0, (1 << 14) - 1, 1, 256);
	case V4L2_CID_MPEG_STREAM_PID_PCR:
		return v4l2_ctrl_query_fill(qctrl, 0, (1 << 14) - 1, 1, 259);

	default:
		break;
	}
	return -EINVAL;
}