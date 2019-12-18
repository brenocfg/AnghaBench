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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct go7007 {int /*<<< orphan*/  bitrate; int /*<<< orphan*/  closed_gop; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  aspect_ratio; int /*<<< orphan*/  format; int /*<<< orphan*/  dvd_mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GO7007_FORMAT_MPEG1 139 
#define  GO7007_FORMAT_MPEG2 138 
#define  GO7007_FORMAT_MPEG4 137 
#define  GO7007_RATIO_16_9 136 
#define  GO7007_RATIO_1_1 135 
#define  GO7007_RATIO_4_3 134 
#define  V4L2_CID_MPEG_STREAM_TYPE 133 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 130 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 129 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 128 
 int /*<<< orphan*/  V4L2_MPEG_STREAM_TYPE_MPEG2_DVD ; 
 int /*<<< orphan*/  V4L2_MPEG_STREAM_TYPE_MPEG_ELEM ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ASPECT_16x9 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ASPECT_4x3 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_4 ; 

__attribute__((used)) static int mpeg_g_ctrl(struct v4l2_control *ctrl, struct go7007 *go)
{
	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		if (go->dvd_mode)
			ctrl->value = V4L2_MPEG_STREAM_TYPE_MPEG2_DVD;
		else
			ctrl->value = V4L2_MPEG_STREAM_TYPE_MPEG_ELEM;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		switch (go->format) {
		case GO7007_FORMAT_MPEG1:
			ctrl->value = V4L2_MPEG_VIDEO_ENCODING_MPEG_1;
			break;
		case GO7007_FORMAT_MPEG2:
			ctrl->value = V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
			break;
		case GO7007_FORMAT_MPEG4:
			ctrl->value = V4L2_MPEG_VIDEO_ENCODING_MPEG_4;
			break;
		default:
			return -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		switch (go->aspect_ratio) {
		case GO7007_RATIO_1_1:
			ctrl->value = V4L2_MPEG_VIDEO_ASPECT_1x1;
			break;
		case GO7007_RATIO_4_3:
			ctrl->value = V4L2_MPEG_VIDEO_ASPECT_4x3;
			break;
		case GO7007_RATIO_16_9:
			ctrl->value = V4L2_MPEG_VIDEO_ASPECT_16x9;
			break;
		default:
			return -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctrl->value = go->gop_size;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		ctrl->value = go->closed_gop;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = go->bitrate;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}