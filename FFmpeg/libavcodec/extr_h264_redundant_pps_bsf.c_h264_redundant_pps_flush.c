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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  extradata_pic_init_qp; int /*<<< orphan*/  current_pic_init_qp; } ;
typedef  TYPE_1__ H264RedundantPPSContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */

__attribute__((used)) static void h264_redundant_pps_flush(AVBSFContext *bsf)
{
    H264RedundantPPSContext *ctx = bsf->priv_data;
    ctx->current_pic_init_qp = ctx->extradata_pic_init_qp;
}