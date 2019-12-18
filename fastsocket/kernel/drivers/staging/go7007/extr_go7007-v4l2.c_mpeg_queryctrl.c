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
typedef  int u32 ;
struct v4l2_queryctrl {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_CLASS 134 
#define  V4L2_CID_MPEG_STREAM_TYPE 133 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 130 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 129 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 128 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_DVD ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG_ELEM ; 
 int V4L2_MPEG_VIDEO_ASPECT_16x9 ; 
 int V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_4 ; 
 int /*<<< orphan*/  v4l2_ctrl_next (int const**,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

__attribute__((used)) static int mpeg_queryctrl(struct v4l2_queryctrl *ctrl)
{
	static const u32 mpeg_ctrls[] = {
		V4L2_CID_MPEG_CLASS,
		V4L2_CID_MPEG_STREAM_TYPE,
		V4L2_CID_MPEG_VIDEO_ENCODING,
		V4L2_CID_MPEG_VIDEO_ASPECT,
		V4L2_CID_MPEG_VIDEO_GOP_SIZE,
		V4L2_CID_MPEG_VIDEO_GOP_CLOSURE,
		V4L2_CID_MPEG_VIDEO_BITRATE,
		0
	};
	static const u32 *ctrl_classes[] = {
		mpeg_ctrls,
		NULL
	};

	ctrl->id = v4l2_ctrl_next(ctrl_classes, ctrl->id);

	switch (ctrl->id) {
	case V4L2_CID_MPEG_CLASS:
		return v4l2_ctrl_query_fill(ctrl, 0, 0, 0, 0);
	case V4L2_CID_MPEG_STREAM_TYPE:
		return v4l2_ctrl_query_fill(ctrl,
				V4L2_MPEG_STREAM_TYPE_MPEG2_DVD,
				V4L2_MPEG_STREAM_TYPE_MPEG_ELEM, 1,
				V4L2_MPEG_STREAM_TYPE_MPEG_ELEM);
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return v4l2_ctrl_query_fill(ctrl,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_1,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_4, 1,
				V4L2_MPEG_VIDEO_ENCODING_MPEG_2);
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return v4l2_ctrl_query_fill(ctrl,
				V4L2_MPEG_VIDEO_ASPECT_1x1,
				V4L2_MPEG_VIDEO_ASPECT_16x9, 1,
				V4L2_MPEG_VIDEO_ASPECT_1x1);
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		return v4l2_ctrl_query_fill(ctrl, 0, 34, 1, 15);
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		return v4l2_ctrl_query_fill(ctrl, 0, 1, 1, 0);
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		return v4l2_ctrl_query_fill(ctrl,
				64000,
				10000000, 1,
				1500000);
	default:
		return -EINVAL;
	}
	return 0;
}