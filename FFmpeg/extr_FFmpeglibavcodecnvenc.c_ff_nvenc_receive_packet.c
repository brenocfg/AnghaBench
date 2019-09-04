#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_out_surf ;
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {scalar_t__ encoder_flushing; int /*<<< orphan*/  unused_surface_queue; int /*<<< orphan*/  output_surface_ready_queue; int /*<<< orphan*/  nvencoder; int /*<<< orphan*/  d3d11_device; int /*<<< orphan*/  cu_context; } ;
typedef  int /*<<< orphan*/  NvencSurface ;
typedef  TYPE_1__ NvencContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int nvenc_pop_context (TYPE_2__*) ; 
 int nvenc_push_context (TYPE_2__*) ; 
 scalar_t__ output_ready (TYPE_2__*,scalar_t__) ; 
 int process_output_surface (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ff_nvenc_receive_packet(AVCodecContext *avctx, AVPacket *pkt)
{
    NvencSurface *tmp_out_surf;
    int res, res2;

    NvencContext *ctx = avctx->priv_data;

    if ((!ctx->cu_context && !ctx->d3d11_device) || !ctx->nvencoder)
        return AVERROR(EINVAL);

    if (output_ready(avctx, ctx->encoder_flushing)) {
        av_fifo_generic_read(ctx->output_surface_ready_queue, &tmp_out_surf, sizeof(tmp_out_surf), NULL);

        res = nvenc_push_context(avctx);
        if (res < 0)
            return res;

        res = process_output_surface(avctx, pkt, tmp_out_surf);

        res2 = nvenc_pop_context(avctx);
        if (res2 < 0)
            return res2;

        if (res)
            return res;

        av_fifo_generic_write(ctx->unused_surface_queue, &tmp_out_surf, sizeof(tmp_out_surf), NULL);
    } else if (ctx->encoder_flushing) {
        return AVERROR_EOF;
    } else {
        return AVERROR(EAGAIN);
    }

    return 0;
}