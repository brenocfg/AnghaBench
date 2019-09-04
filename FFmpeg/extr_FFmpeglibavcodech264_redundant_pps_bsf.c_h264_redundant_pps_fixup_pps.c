#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int weighted_pred_flag; scalar_t__ pic_init_qp_minus26; } ;
struct TYPE_5__ {scalar_t__ global_pic_init_qp; scalar_t__ current_pic_init_qp; } ;
typedef  TYPE_1__ H264RedundantPPSContext ;
typedef  TYPE_2__ H264RawPPS ;

/* Variables and functions */

__attribute__((used)) static int h264_redundant_pps_fixup_pps(H264RedundantPPSContext *ctx,
                                        H264RawPPS *pps)
{
    // Record the current value of pic_init_qp in order to fix up
    // following slices, then overwrite with the global value.
    ctx->current_pic_init_qp = pps->pic_init_qp_minus26 + 26;
    pps->pic_init_qp_minus26 = ctx->global_pic_init_qp - 26;

    // Some PPSs have this set, so it must be set in all of them.
    // (Slices which do not use such a PPS on input will still have
    // *_weight_l*flag as zero and therefore write equivalently.)
    pps->weighted_pred_flag = 1;

    return 0;
}