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
struct v4l2_queryctrl {int id; } ;
struct saa7164_encoder_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENCODER_DEF_BITRATE ; 
 int ENCODER_MAX_BITRATE ; 
 int ENCODER_MIN_BITRATE ; 
#define  V4L2_CID_AUDIO_VOLUME 141 
#define  V4L2_CID_BRIGHTNESS 140 
#define  V4L2_CID_CONTRAST 139 
#define  V4L2_CID_HUE 138 
#define  V4L2_CID_MPEG_AUDIO_MUTE 137 
#define  V4L2_CID_MPEG_STREAM_TYPE 136 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 135 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 134 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 133 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 132 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 131 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_PS ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_TS ; 
 int V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int V4L2_MPEG_VIDEO_ASPECT_221x100 ; 
 int V4L2_MPEG_VIDEO_ASPECT_4x3 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int fill_queryctrl(struct saa7164_encoder_params *params,
	struct v4l2_queryctrl *c)
{
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		return v4l2_ctrl_query_fill(c, 0x0, 0xff, 1, 127);
	case V4L2_CID_CONTRAST:
		return v4l2_ctrl_query_fill(c, 0x0, 0xff, 1, 66);
	case V4L2_CID_SATURATION:
		return v4l2_ctrl_query_fill(c, 0x0, 0xff, 1, 62);
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(c, 0x0, 0xff, 1, 128);
	case V4L2_CID_SHARPNESS:
		return v4l2_ctrl_query_fill(c, 0x0, 0x0f, 1, 8);
	case V4L2_CID_MPEG_AUDIO_MUTE:
		return v4l2_ctrl_query_fill(c, 0x0, 0x01, 1, 0);
	case V4L2_CID_AUDIO_VOLUME:
		return v4l2_ctrl_query_fill(c, -83, 24, 1, 20);
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		return v4l2_ctrl_query_fill(c,
			ENCODER_MIN_BITRATE, ENCODER_MAX_BITRATE,
			100000, ENCODER_DEF_BITRATE);
	case V4L2_CID_MPEG_STREAM_TYPE:
		return v4l2_ctrl_query_fill(c,
			V4L2_MPEG_STREAM_TYPE_MPEG2_PS,
			V4L2_MPEG_STREAM_TYPE_MPEG2_TS,
			1, V4L2_MPEG_STREAM_TYPE_MPEG2_PS);
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return v4l2_ctrl_query_fill(c,
			V4L2_MPEG_VIDEO_ASPECT_1x1,
			V4L2_MPEG_VIDEO_ASPECT_221x100,
			1, V4L2_MPEG_VIDEO_ASPECT_4x3);
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		return v4l2_ctrl_query_fill(c, 1, 255, 1, 15);
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		return v4l2_ctrl_query_fill(c,
			V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
			1, V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		return v4l2_ctrl_query_fill(c,
			1, 3, 1, 1);
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		return v4l2_ctrl_query_fill(c,
			ENCODER_MIN_BITRATE, ENCODER_MAX_BITRATE,
			100000, ENCODER_DEF_BITRATE);
	default:
		return -EINVAL;
	}
}