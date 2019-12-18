#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_23__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_22__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_21__ {TYPE_2__* hwframes; int /*<<< orphan*/  hwframes_ref; } ;
struct TYPE_20__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_19__ {void* data; } ;
typedef  TYPE_3__ HWDownloadContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int av_hwframe_transfer_data (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwdownload_filter_frame(AVFilterLink *link, AVFrame *input)
{
    AVFilterContext *avctx = link->dst;
    AVFilterLink  *outlink = avctx->outputs[0];
    HWDownloadContext *ctx = avctx->priv;
    AVFrame *output = NULL;
    int err;

    if (!ctx->hwframes_ref || !input->hw_frames_ctx) {
        av_log(ctx, AV_LOG_ERROR, "Input frames must have hardware context.\n");
        err = AVERROR(EINVAL);
        goto fail;
    }
    if ((void*)ctx->hwframes != input->hw_frames_ctx->data) {
        av_log(ctx, AV_LOG_ERROR, "Input frame is not the in the configured "
               "hwframe context.\n");
        err = AVERROR(EINVAL);
        goto fail;
    }

    output = ff_get_video_buffer(outlink, ctx->hwframes->width,
                                 ctx->hwframes->height);
    if (!output) {
        err = AVERROR(ENOMEM);
        goto fail;
    }

    err = av_hwframe_transfer_data(output, input, 0);
    if (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Failed to download frame: %d.\n", err);
        goto fail;
    }

    output->width  = outlink->w;
    output->height = outlink->h;

    err = av_frame_copy_props(output, input);
    if (err < 0)
        goto fail;

    av_frame_free(&input);

    return ff_filter_frame(avctx->outputs[0], output);

fail:
    av_frame_free(&input);
    av_frame_free(&output);
    return err;
}