#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
typedef  int MatroskaVideoStereoModeType ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_1__ AVStereo3D ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_STEREO3D ; 
 int /*<<< orphan*/  AV_STEREO3D_2D ; 
 int /*<<< orphan*/  AV_STEREO3D_CHECKERBOARD ; 
 int /*<<< orphan*/  AV_STEREO3D_COLUMNS ; 
 int /*<<< orphan*/  AV_STEREO3D_FLAG_INVERT ; 
 int /*<<< orphan*/  AV_STEREO3D_FRAMESEQUENCE ; 
 int /*<<< orphan*/  AV_STEREO3D_LINES ; 
 int /*<<< orphan*/  AV_STEREO3D_SIDEBYSIDE ; 
 int /*<<< orphan*/  AV_STEREO3D_TOPBOTTOM ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_LR 140 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_RL 139 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_BOTTOM_TOP 138 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_LR 137 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_RL 136 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_LR 135 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_RL 134 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_LEFT_RIGHT 133 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_MONO 132 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_RIGHT_LEFT 131 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_LR 130 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_RL 129 
#define  MATROSKA_VIDEO_STEREOMODE_TYPE_TOP_BOTTOM 128 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* av_stereo3d_alloc () ; 
 int av_stream_add_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int ff_mkv_stereo3d_conv(AVStream *st, MatroskaVideoStereoModeType stereo_mode)
{
    AVStereo3D *stereo;
    int ret;

    stereo = av_stereo3d_alloc();
    if (!stereo)
        return AVERROR(ENOMEM);

    // note: the missing breaks are intentional
    switch (stereo_mode) {
    case MATROSKA_VIDEO_STEREOMODE_TYPE_MONO:
        stereo->type = AV_STEREO3D_2D;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_RIGHT_LEFT:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_LEFT_RIGHT:
        stereo->type = AV_STEREO3D_SIDEBYSIDE;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTTOM_TOP:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_TOP_BOTTOM:
        stereo->type = AV_STEREO3D_TOPBOTTOM;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_RL:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_LR:
        stereo->type = AV_STEREO3D_CHECKERBOARD;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_RL:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_LR:
        stereo->type = AV_STEREO3D_LINES;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_RL:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_LR:
        stereo->type = AV_STEREO3D_COLUMNS;
        break;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_RL:
        stereo->flags |= AV_STEREO3D_FLAG_INVERT;
    case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_LR:
        stereo->type = AV_STEREO3D_FRAMESEQUENCE;
        break;
    }

    ret = av_stream_add_side_data(st, AV_PKT_DATA_STEREO3D, (uint8_t *)stereo,
                                  sizeof(*stereo));
    if (ret < 0) {
        av_freep(&stereo);
        return ret;
    }

    return 0;
}