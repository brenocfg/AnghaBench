#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_2__* pps; } ;
struct TYPE_9__ {int /*<<< orphan*/  h264_loop_filter_strength; } ;
struct TYPE_12__ {int pixel_shift; TYPE_3__ ps; TYPE_1__ h264dsp; } ;
struct TYPE_10__ {scalar_t__ chroma_qp_diff; } ;
typedef  int /*<<< orphan*/  H264SliceContext ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_MBAFF (TYPE_4__ const*) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  ff_h264_filter_mb (TYPE_4__ const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  h264_filter_mb_fast_internal (TYPE_4__ const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

void ff_h264_filter_mb_fast(const H264Context *h, H264SliceContext *sl,
                            int mb_x, int mb_y, uint8_t *img_y,
                            uint8_t *img_cb, uint8_t *img_cr,
                            unsigned int linesize, unsigned int uvlinesize)
{
    av_assert2(!FRAME_MBAFF(h));
    if(!h->h264dsp.h264_loop_filter_strength || h->ps.pps->chroma_qp_diff) {
        ff_h264_filter_mb(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize);
        return;
    }

#if CONFIG_SMALL
    h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, h->pixel_shift);
#else
    if(h->pixel_shift){
        h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, 1);
    }else{
        h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, 0);
    }
#endif
}