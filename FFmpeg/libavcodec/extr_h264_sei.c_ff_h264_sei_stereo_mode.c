#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int arrangement_cancel_flag; int arrangement_type; int content_interpretation_type; } ;
typedef  TYPE_1__ H264SEIFramePacking ;

/* Variables and functions */
#define  H264_SEI_FPA_TYPE_2D 134 
#define  H264_SEI_FPA_TYPE_CHECKERBOARD 133 
#define  H264_SEI_FPA_TYPE_INTERLEAVE_COLUMN 132 
#define  H264_SEI_FPA_TYPE_INTERLEAVE_ROW 131 
#define  H264_SEI_FPA_TYPE_INTERLEAVE_TEMPORAL 130 
#define  H264_SEI_FPA_TYPE_SIDE_BY_SIDE 129 
#define  H264_SEI_FPA_TYPE_TOP_BOTTOM 128 

const char *ff_h264_sei_stereo_mode(const H264SEIFramePacking *h)
{
    if (h->arrangement_cancel_flag == 0) {
        switch (h->arrangement_type) {
            case H264_SEI_FPA_TYPE_CHECKERBOARD:
                if (h->content_interpretation_type == 2)
                    return "checkerboard_rl";
                else
                    return "checkerboard_lr";
            case H264_SEI_FPA_TYPE_INTERLEAVE_COLUMN:
                if (h->content_interpretation_type == 2)
                    return "col_interleaved_rl";
                else
                    return "col_interleaved_lr";
            case H264_SEI_FPA_TYPE_INTERLEAVE_ROW:
                if (h->content_interpretation_type == 2)
                    return "row_interleaved_rl";
                else
                    return "row_interleaved_lr";
            case H264_SEI_FPA_TYPE_SIDE_BY_SIDE:
                if (h->content_interpretation_type == 2)
                    return "right_left";
                else
                    return "left_right";
            case H264_SEI_FPA_TYPE_TOP_BOTTOM:
                if (h->content_interpretation_type == 2)
                    return "bottom_top";
                else
                    return "top_bottom";
            case H264_SEI_FPA_TYPE_INTERLEAVE_TEMPORAL:
                if (h->content_interpretation_type == 2)
                    return "block_rl";
                else
                    return "block_lr";
            case H264_SEI_FPA_TYPE_2D:
            default:
                return "mono";
        }
    } else if (h->arrangement_cancel_flag == 1) {
        return "mono";
    } else {
        return NULL;
    }
}