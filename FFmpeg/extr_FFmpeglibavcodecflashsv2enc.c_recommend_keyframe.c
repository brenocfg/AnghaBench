#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double diff_blocks; double tot_blocks; double diff_lines; double tot_lines; double uncomp_size; double raw_size; double comp_size; TYPE_1__* avctx; } ;
struct TYPE_4__ {scalar_t__ gop_size; } ;
typedef  TYPE_2__ FlashSV2Context ;

/* Variables and functions */

__attribute__((used)) static void recommend_keyframe(FlashSV2Context * s, int *keyframe)
{
#ifndef FLASHSV2_DUMB
    double block_ratio, line_ratio, enc_ratio, comp_ratio, data_ratio;
    if (s->avctx->gop_size > 0) {
        block_ratio = s->diff_blocks / s->tot_blocks;
        line_ratio = s->diff_lines / s->tot_lines;
        enc_ratio = s->uncomp_size / s->raw_size;
        comp_ratio = s->comp_size / s->uncomp_size;
        data_ratio = s->comp_size / s->raw_size;

        if ((block_ratio >= 0.5 && line_ratio / block_ratio <= 0.5) || line_ratio >= 0.95) {
            *keyframe = 1;
            return;
        }
    }
#else
    return;
#endif
}