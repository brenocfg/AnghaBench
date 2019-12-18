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

/* Variables and functions */
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

__attribute__((used)) static void mkv_stereo_mode_display_mul(int stereo_mode,
                                        int *h_width, int *h_height)
{
    switch (stereo_mode) {
        case MATROSKA_VIDEO_STEREOMODE_TYPE_MONO:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_RL:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_CHECKERBOARD_LR:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_RL:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTH_EYES_BLOCK_LR:
            break;
        case MATROSKA_VIDEO_STEREOMODE_TYPE_RIGHT_LEFT:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_LEFT_RIGHT:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_RL:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_COL_INTERLEAVED_LR:
            *h_width = 2;
            break;
        case MATROSKA_VIDEO_STEREOMODE_TYPE_BOTTOM_TOP:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_TOP_BOTTOM:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_RL:
        case MATROSKA_VIDEO_STEREOMODE_TYPE_ROW_INTERLEAVED_LR:
            *h_height = 2;
            break;
    }
}