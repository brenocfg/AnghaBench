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
typedef  int s32 ;
typedef  enum v4l2_ctrl_type { ____Placeholder_v4l2_ctrl_type } v4l2_ctrl_type ;

/* Variables and functions */
#define  V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 140 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM 139 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 138 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 137 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 136 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 135 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 134 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 133 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 132 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 131 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 130 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 129 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 128 
 int V4L2_CTRL_FLAG_READ_ONLY ; 
 int V4L2_CTRL_FLAG_SLIDER ; 
 int V4L2_CTRL_FLAG_UPDATE ; 
 int V4L2_CTRL_TYPE_BOOLEAN ; 
 int V4L2_CTRL_TYPE_INTEGER ; 
 int V4L2_CTRL_TYPE_MENU ; 
 char* cx2341x_get_name (int) ; 

__attribute__((used)) static void cx2341x_ctrl_fill(u32 id, const char **name, enum v4l2_ctrl_type *type,
		    s32 *min, s32 *max, s32 *step, s32 *def, u32 *flags)
{
	*name = cx2341x_get_name(id);
	*flags = 0;

	switch (id) {
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		*type = V4L2_CTRL_TYPE_MENU;
		*min = 0;
		*step = 0;
		break;
	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		*type = V4L2_CTRL_TYPE_BOOLEAN;
		*min = 0;
		*max = *step = 1;
		break;
	default:
		*type = V4L2_CTRL_TYPE_INTEGER;
		break;
	}
	switch (id) {
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		*flags |= V4L2_CTRL_FLAG_UPDATE;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		*flags |= V4L2_CTRL_FLAG_SLIDER;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		break;
	}
}