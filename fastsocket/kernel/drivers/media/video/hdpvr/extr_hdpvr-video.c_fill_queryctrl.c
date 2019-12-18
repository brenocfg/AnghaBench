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
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; } ;
struct hdpvr_options {int /*<<< orphan*/  bitrate_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDPVR_CONSTANT ; 
#define  V4L2_CID_BRIGHTNESS 137 
#define  V4L2_CID_CONTRAST 136 
#define  V4L2_CID_HUE 135 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 134 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 133 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 131 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_INACTIVE ; 
 int V4L2_MPEG_AUDIO_ENCODING_AAC ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int fill_queryctrl(struct hdpvr_options *opt, struct v4l2_queryctrl *qc,
			  int ac3)
{
	int err;

	switch (qc->id) {
	case V4L2_CID_BRIGHTNESS:
		return v4l2_ctrl_query_fill(qc, 0x0, 0xff, 1, 0x86);
	case V4L2_CID_CONTRAST:
		return v4l2_ctrl_query_fill(qc, 0x0, 0xff, 1, 0x80);
	case V4L2_CID_SATURATION:
		return v4l2_ctrl_query_fill(qc, 0x0, 0xff, 1, 0x80);
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(qc, 0x0, 0xff, 1, 0x80);
	case V4L2_CID_SHARPNESS:
		return v4l2_ctrl_query_fill(qc, 0x0, 0xff, 1, 0x80);
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return v4l2_ctrl_query_fill(
			qc, V4L2_MPEG_AUDIO_ENCODING_AAC,
			ac3 ? V4L2_MPEG_AUDIO_ENCODING_AC3
			: V4L2_MPEG_AUDIO_ENCODING_AAC,
			1, V4L2_MPEG_AUDIO_ENCODING_AAC);
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return v4l2_ctrl_query_fill(
			qc, V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC, 1,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC);

/* 	case V4L2_CID_MPEG_VIDEO_? maybe keyframe interval: */
/* 		return v4l2_ctrl_query_fill(qc, 0, 128, 128, 0); */
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		return v4l2_ctrl_query_fill(
			qc, V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 1,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);

	case V4L2_CID_MPEG_VIDEO_BITRATE:
		return v4l2_ctrl_query_fill(qc, 1000000, 13500000, 100000,
					    6500000);
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		err = v4l2_ctrl_query_fill(qc, 1100000, 20200000, 100000,
					   9000000);
		if (!err && opt->bitrate_mode == HDPVR_CONSTANT)
			qc->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return err;
	default:
		return -EINVAL;
	}
}