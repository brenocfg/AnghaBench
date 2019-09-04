#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int mb_height; scalar_t__ picture_structure; TYPE_4__* cur_pic_ptr; scalar_t__ droppable; } ;
struct TYPE_17__ {int mb_y; TYPE_3__* h264; scalar_t__ deblocking_filter; } ;
struct TYPE_16__ {int /*<<< orphan*/  tf; } ;
struct TYPE_15__ {TYPE_2__* slice_ctx; } ;
struct TYPE_13__ {scalar_t__ error_occurred; } ;
struct TYPE_14__ {TYPE_1__ er; } ;
typedef  TYPE_5__ H264SliceContext ;
typedef  TYPE_6__ H264Context ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int FIELD_PICTURE (TYPE_6__ const*) ; 
 int FRAME_MBAFF (TYPE_6__ const*) ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 int /*<<< orphan*/  ff_h264_draw_horiz_band (TYPE_6__ const*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void decode_finish_row(const H264Context *h, H264SliceContext *sl)
{
    int top            = 16 * (sl->mb_y      >> FIELD_PICTURE(h));
    int pic_height     = 16 *  h->mb_height >> FIELD_PICTURE(h);
    int height         =  16      << FRAME_MBAFF(h);
    int deblock_border = (16 + 4) << FRAME_MBAFF(h);

    if (sl->deblocking_filter) {
        if ((top + height) >= pic_height)
            height += deblock_border;
        top -= deblock_border;
    }

    if (top >= pic_height || (top + height) < 0)
        return;

    height = FFMIN(height, pic_height - top);
    if (top < 0) {
        height = top + height;
        top    = 0;
    }

    ff_h264_draw_horiz_band(h, sl, top, height);

    if (h->droppable || sl->h264->slice_ctx[0].er.error_occurred)
        return;

    ff_thread_report_progress(&h->cur_pic_ptr->tf, top + height - 1,
                              h->picture_structure == PICT_BOTTOM_FIELD);
}