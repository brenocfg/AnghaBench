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
struct TYPE_5__ {scalar_t__ max_b_frames; TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__* initial_pts; int async_depth; int /*<<< orphan*/  output_surface_queue; int /*<<< orphan*/  output_surface_ready_queue; } ;
typedef  int /*<<< orphan*/  NvencSurface ;
typedef  TYPE_1__ NvencContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int output_ready(AVCodecContext *avctx, int flush)
{
    NvencContext *ctx = avctx->priv_data;
    int nb_ready, nb_pending;

    /* when B-frames are enabled, we wait for two initial timestamps to
     * calculate the first dts */
    if (!flush && avctx->max_b_frames > 0 &&
        (ctx->initial_pts[0] == AV_NOPTS_VALUE || ctx->initial_pts[1] == AV_NOPTS_VALUE))
        return 0;

    nb_ready   = av_fifo_size(ctx->output_surface_ready_queue)   / sizeof(NvencSurface*);
    nb_pending = av_fifo_size(ctx->output_surface_queue)         / sizeof(NvencSurface*);
    if (flush)
        return nb_ready > 0;
    return (nb_ready > 0) && (nb_ready + nb_pending >= ctx->async_depth);
}