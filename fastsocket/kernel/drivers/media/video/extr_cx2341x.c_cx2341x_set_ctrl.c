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
struct cx2341x_mpeg_params {int audio_sampling_freq; int capabilities; int audio_encoding; int audio_l2_bitrate; int audio_ac3_bitrate; int audio_mode; int audio_mode_extension; int audio_emphasis; int audio_crc; int audio_mute; int video_aspect; int video_gop_size; int video_b_frames; int video_gop_closure; int video_bitrate_mode; int video_bitrate; int video_bitrate_peak; int video_temporal_decimation; int video_mute; int video_mute_yuv; int stream_type; int stream_vbi_fmt; int video_spatial_filter_mode; int video_spatial_filter; int video_luma_spatial_filter_type; int video_chroma_spatial_filter_type; int video_temporal_filter_mode; int video_temporal_filter; int video_median_filter_type; int video_luma_median_filter_top; int video_luma_median_filter_bottom; int video_chroma_median_filter_top; int video_chroma_median_filter_bottom; int stream_insert_nav_packets; int /*<<< orphan*/  video_encoding; } ;

/* Variables and functions */
 int CX2341X_CAP_HAS_AC3 ; 
 int EBUSY ; 
 int EINVAL ; 
 int ERANGE ; 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 160 
#define  V4L2_CID_MPEG_AUDIO_CRC 159 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 158 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 157 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 156 
#define  V4L2_CID_MPEG_AUDIO_MODE 155 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 154 
#define  V4L2_CID_MPEG_AUDIO_MUTE 153 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 152 
#define  V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 151 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM 150 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 149 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 148 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 147 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 146 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 145 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 144 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 143 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 142 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 141 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 140 
#define  V4L2_CID_MPEG_STREAM_TYPE 139 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 138 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 137 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 136 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 135 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 134 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 133 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 132 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 131 
#define  V4L2_CID_MPEG_VIDEO_MUTE 130 
#define  V4L2_CID_MPEG_VIDEO_MUTE_YUV 129 
#define  V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION 128 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG1_SS ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG1_VCD ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 

__attribute__((used)) static int cx2341x_set_ctrl(struct cx2341x_mpeg_params *params, int busy,
		struct v4l2_ext_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		if (busy)
			return -EBUSY;
		params->audio_sampling_freq = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		if (busy)
			return -EBUSY;
		if (params->capabilities & CX2341X_CAP_HAS_AC3)
			if (ctrl->value != V4L2_MPEG_AUDIO_ENCODING_LAYER_2 &&
			    ctrl->value != V4L2_MPEG_AUDIO_ENCODING_AC3)
				return -ERANGE;
		params->audio_encoding = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		if (busy)
			return -EBUSY;
		params->audio_l2_bitrate = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		if (busy)
			return -EBUSY;
		if (!(params->capabilities & CX2341X_CAP_HAS_AC3))
			return -EINVAL;
		params->audio_ac3_bitrate = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_MODE:
		params->audio_mode = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		params->audio_mode_extension = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_EMPHASIS:
		params->audio_emphasis = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_CRC:
		params->audio_crc = ctrl->value;
		break;
	case V4L2_CID_MPEG_AUDIO_MUTE:
		params->audio_mute = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		params->video_aspect = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES: {
		int b = ctrl->value + 1;
		int gop = params->video_gop_size;
		params->video_b_frames = ctrl->value;
		params->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		while (params->video_gop_size > 34)
			params->video_gop_size -= b;
		break;
	}
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE: {
		int b = params->video_b_frames + 1;
		int gop = ctrl->value;
		params->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		while (params->video_gop_size > 34)
			params->video_gop_size -= b;
		ctrl->value = params->video_gop_size;
		break;
	}
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		params->video_gop_closure = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		if (busy)
			return -EBUSY;
		/* MPEG-1 only allows CBR */
		if (params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1 &&
		    ctrl->value != V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			return -EINVAL;
		params->video_bitrate_mode = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		if (busy)
			return -EBUSY;
		params->video_bitrate = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		if (busy)
			return -EBUSY;
		params->video_bitrate_peak = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		params->video_temporal_decimation = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_MUTE:
		params->video_mute = (ctrl->value != 0);
		break;
	case V4L2_CID_MPEG_VIDEO_MUTE_YUV:
		params->video_mute_yuv = ctrl->value;
		break;
	case V4L2_CID_MPEG_STREAM_TYPE:
		if (busy)
			return -EBUSY;
		params->stream_type = ctrl->value;
		params->video_encoding =
		    (params->stream_type == V4L2_MPEG_STREAM_TYPE_MPEG1_SS ||
		     params->stream_type == V4L2_MPEG_STREAM_TYPE_MPEG1_VCD) ?
			V4L2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		if (params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 implies CBR */
			params->video_bitrate_mode =
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
		break;
	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		params->stream_vbi_fmt = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		params->video_spatial_filter_mode = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		params->video_spatial_filter = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		params->video_luma_spatial_filter_type = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		params->video_chroma_spatial_filter_type = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		params->video_temporal_filter_mode = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		params->video_temporal_filter = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		params->video_median_filter_type = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		params->video_luma_median_filter_top = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		params->video_luma_median_filter_bottom = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		params->video_chroma_median_filter_top = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		params->video_chroma_median_filter_bottom = ctrl->value;
		break;
	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		params->stream_insert_nav_packets = ctrl->value;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}