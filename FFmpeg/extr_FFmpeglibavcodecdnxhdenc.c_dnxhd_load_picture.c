#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* linesize; int /*<<< orphan*/  top_field_first; scalar_t__ interlaced_frame; } ;
struct TYPE_12__ {int linesize; int uvlinesize; TYPE_1__* avctx; } ;
struct TYPE_13__ {int interlaced; int cur_field; TYPE_4__ m; TYPE_3__** thread; } ;
struct TYPE_10__ {int linesize; int uvlinesize; } ;
struct TYPE_11__ {int dct_y_offset; int dct_uv_offset; TYPE_2__ m; } ;
struct TYPE_9__ {int thread_count; } ;
typedef  TYPE_5__ DNXHDEncContext ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void dnxhd_load_picture(DNXHDEncContext *ctx, const AVFrame *frame)
{
    int i;

    for (i = 0; i < ctx->m.avctx->thread_count; i++) {
        ctx->thread[i]->m.linesize    = frame->linesize[0] << ctx->interlaced;
        ctx->thread[i]->m.uvlinesize  = frame->linesize[1] << ctx->interlaced;
        ctx->thread[i]->dct_y_offset  = ctx->m.linesize  *8;
        ctx->thread[i]->dct_uv_offset = ctx->m.uvlinesize*8;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    ctx->m.avctx->coded_frame->interlaced_frame = frame->interlaced_frame;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    ctx->cur_field = frame->interlaced_frame && !frame->top_field_first;
}