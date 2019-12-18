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
struct v4l2_control {int id; int value; } ;
struct go7007 {int bitrate; int gop_size; int pali; int closed_gop; int seq_header_enable; int gop_header_enable; int dvd_mode; int /*<<< orphan*/  aspect_ratio; void* format; int /*<<< orphan*/  repeat_seqhead; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 void* GO7007_FORMAT_MJPEG ; 
 void* GO7007_FORMAT_MPEG1 ; 
 void* GO7007_FORMAT_MPEG2 ; 
 void* GO7007_FORMAT_MPEG4 ; 
 int /*<<< orphan*/  GO7007_RATIO_16_9 ; 
 int /*<<< orphan*/  GO7007_RATIO_1_1 ; 
 int /*<<< orphan*/  GO7007_RATIO_4_3 ; 
#define  V4L2_CID_MPEG_STREAM_TYPE 142 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 141 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 140 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 139 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 138 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 137 
#define  V4L2_MPEG_STREAM_TYPE_MPEG2_DVD 136 
#define  V4L2_MPEG_STREAM_TYPE_MPEG_ELEM 135 
#define  V4L2_MPEG_VIDEO_ASPECT_16x9 134 
#define  V4L2_MPEG_VIDEO_ASPECT_1x1 133 
#define  V4L2_MPEG_VIDEO_ASPECT_221x100 132 
#define  V4L2_MPEG_VIDEO_ASPECT_4x3 131 
#define  V4L2_MPEG_VIDEO_ENCODING_MPEG_1 130 
#define  V4L2_MPEG_VIDEO_ENCODING_MPEG_2 129 
#define  V4L2_MPEG_VIDEO_ENCODING_MPEG_4 128 

__attribute__((used)) static int mpeg_s_ctrl(struct v4l2_control *ctrl, struct go7007 *go)
{
	/* pretty sure we can't change any of these while streaming */
	if (go->streaming)
		return -EBUSY;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		switch (ctrl->value) {
		case V4L2_MPEG_STREAM_TYPE_MPEG2_DVD:
			go->format = GO7007_FORMAT_MPEG2;
			go->bitrate = 9800000;
			go->gop_size = 15;
			go->pali = 0x48;
			go->closed_gop = 1;
			go->repeat_seqhead = 0;
			go->seq_header_enable = 1;
			go->gop_header_enable = 1;
			go->dvd_mode = 1;
			break;
		case V4L2_MPEG_STREAM_TYPE_MPEG_ELEM:
			/* todo: */
			break;
		default:
			return -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		switch (ctrl->value) {
		case V4L2_MPEG_VIDEO_ENCODING_MPEG_1:
			go->format = GO7007_FORMAT_MPEG1;
			go->pali = 0;
			break;
		case V4L2_MPEG_VIDEO_ENCODING_MPEG_2:
			go->format = GO7007_FORMAT_MPEG2;
			/*if (mpeg->pali >> 24 == 2)
				go->pali = mpeg->pali & 0xff;
			else*/
				go->pali = 0x48;
			break;
		case V4L2_MPEG_VIDEO_ENCODING_MPEG_4:
			go->format = GO7007_FORMAT_MPEG4;
			/*if (mpeg->pali >> 24 == 4)
				go->pali = mpeg->pali & 0xff;
			else*/
				go->pali = 0xf5;
			break;
		default:
			return -EINVAL;
		}
		go->gop_header_enable =
			/*mpeg->flags & GO7007_MPEG_OMIT_GOP_HEADER
			? 0 :*/ 1;
		/*if (mpeg->flags & GO7007_MPEG_REPEAT_SEQHEADER)
			go->repeat_seqhead = 1;
		else*/
			go->repeat_seqhead = 0;
		go->dvd_mode = 0;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		if (go->format == GO7007_FORMAT_MJPEG)
			return -EINVAL;
		switch (ctrl->value) {
		case V4L2_MPEG_VIDEO_ASPECT_1x1:
			go->aspect_ratio = GO7007_RATIO_1_1;
			break;
		case V4L2_MPEG_VIDEO_ASPECT_4x3:
			go->aspect_ratio = GO7007_RATIO_4_3;
			break;
		case V4L2_MPEG_VIDEO_ASPECT_16x9:
			go->aspect_ratio = GO7007_RATIO_16_9;
			break;
		case V4L2_MPEG_VIDEO_ASPECT_221x100:
		default:
			return -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		if (ctrl->value < 0 || ctrl->value > 34)
			return -EINVAL;
		go->gop_size = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		if (ctrl->value != 0 && ctrl->value != 1)
			return -EINVAL;
		go->closed_gop = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		/* Upper bound is kind of arbitrary here */
		if (ctrl->value < 64000 || ctrl->value > 10000000)
			return -EINVAL;
		go->bitrate = ctrl->value;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}