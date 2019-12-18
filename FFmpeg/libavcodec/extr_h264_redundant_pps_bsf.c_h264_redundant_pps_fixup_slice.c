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
struct TYPE_6__ {int slice_qp_delta; } ;
struct TYPE_5__ {int current_pic_init_qp; int global_pic_init_qp; } ;
typedef  TYPE_1__ H264RedundantPPSContext ;
typedef  TYPE_2__ H264RawSliceHeader ;

/* Variables and functions */

__attribute__((used)) static int h264_redundant_pps_fixup_slice(H264RedundantPPSContext *ctx,
                                          H264RawSliceHeader *slice)
{
    int qp;

    qp = ctx->current_pic_init_qp + slice->slice_qp_delta;
    slice->slice_qp_delta = qp - ctx->global_pic_init_qp;

    return 0;
}