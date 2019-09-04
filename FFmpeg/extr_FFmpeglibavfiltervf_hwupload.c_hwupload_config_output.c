#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ extra_hw_frames; TYPE_1__* priv; TYPE_3__** inputs; } ;
struct TYPE_13__ {scalar_t__ format; TYPE_7__* hw_frames_ctx; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* src; } ;
struct TYPE_12__ {scalar_t__ format; scalar_t__ sw_format; scalar_t__ initial_pool_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {TYPE_7__* hwframes_ref; TYPE_2__* hwframes; int /*<<< orphan*/  hwdevice_ref; } ;
typedef  TYPE_1__ HWUploadContext ;
typedef  TYPE_2__ AVHWFramesContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_buffer_ref (TYPE_7__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_7__**) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (scalar_t__) ; 
 TYPE_7__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_7__*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int hwupload_config_output(AVFilterLink *outlink)
{
    AVFilterContext *avctx = outlink->src;
    AVFilterLink   *inlink = avctx->inputs[0];
    HWUploadContext   *ctx = avctx->priv;
    int err;

    av_buffer_unref(&ctx->hwframes_ref);

    if (inlink->format == outlink->format) {
        // The input is already a hardware format, so we just want to
        // pass through the input frames in their own hardware context.
        if (!inlink->hw_frames_ctx) {
            av_log(ctx, AV_LOG_ERROR, "No input hwframe context.\n");
            return AVERROR(EINVAL);
        }

        outlink->hw_frames_ctx = av_buffer_ref(inlink->hw_frames_ctx);
        if (!outlink->hw_frames_ctx)
            return AVERROR(ENOMEM);

        return 0;
    }

    ctx->hwframes_ref = av_hwframe_ctx_alloc(ctx->hwdevice_ref);
    if (!ctx->hwframes_ref)
        return AVERROR(ENOMEM);

    ctx->hwframes = (AVHWFramesContext*)ctx->hwframes_ref->data;

    av_log(ctx, AV_LOG_DEBUG, "Surface format is %s.\n",
           av_get_pix_fmt_name(inlink->format));

    ctx->hwframes->format    = outlink->format;
    ctx->hwframes->sw_format = inlink->format;
    ctx->hwframes->width     = inlink->w;
    ctx->hwframes->height    = inlink->h;

    if (avctx->extra_hw_frames >= 0)
        ctx->hwframes->initial_pool_size = 2 + avctx->extra_hw_frames;

    err = av_hwframe_ctx_init(ctx->hwframes_ref);
    if (err < 0)
        goto fail;

    outlink->hw_frames_ctx = av_buffer_ref(ctx->hwframes_ref);
    if (!outlink->hw_frames_ctx) {
        err = AVERROR(ENOMEM);
        goto fail;
    }

    return 0;

fail:
    av_buffer_unref(&ctx->hwframes_ref);
    return err;
}