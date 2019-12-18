#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VASurfaceID ;
typedef  scalar_t__ VAStatus ;
typedef  int /*<<< orphan*/  VAProcPipelineParameterBuffer ;
typedef  int /*<<< orphan*/  VABufferID ;
struct TYPE_9__ {int /*<<< orphan*/  va_context; TYPE_1__* hwctx; } ;
typedef  TYPE_2__ VAAPIVPPContext ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {scalar_t__* data; } ;
struct TYPE_8__ {int driver_quirks; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS ; 
 scalar_t__ CONFIG_VAAPI_1 ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  VAProcPipelineParameterBufferType ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ vaBeginPicture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vaCreateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vaDestroyBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vaEndPicture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaErrorStr (scalar_t__) ; 
 scalar_t__ vaRenderPicture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int ff_vaapi_vpp_render_picture(AVFilterContext *avctx,
                                VAProcPipelineParameterBuffer *params,
                                AVFrame *output_frame)
{
    VAAPIVPPContext *ctx = avctx->priv;
    VASurfaceID output_surface;
    VABufferID params_id;
    VAStatus vas;
    int err;

    output_surface = (VASurfaceID)(uintptr_t)output_frame->data[3];

    vas = vaBeginPicture(ctx->hwctx->display,
                         ctx->va_context, output_surface);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to attach new picture: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail;
    }

    vas = vaCreateBuffer(ctx->hwctx->display, ctx->va_context,
                         VAProcPipelineParameterBufferType,
                         sizeof(*params), 1, params, &params_id);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create parameter buffer: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail_after_begin;
    }
    av_log(avctx, AV_LOG_DEBUG, "Pipeline parameter buffer is %#x.\n",
           params_id);

    vas = vaRenderPicture(ctx->hwctx->display, ctx->va_context,
                          &params_id, 1);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to render parameter buffer: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail_after_begin;
    }

    vas = vaEndPicture(ctx->hwctx->display, ctx->va_context);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to start picture processing: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail_after_render;
    }

    if (CONFIG_VAAPI_1 || ctx->hwctx->driver_quirks &
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS) {
        vas = vaDestroyBuffer(ctx->hwctx->display, params_id);
        if (vas != VA_STATUS_SUCCESS) {
            av_log(avctx, AV_LOG_ERROR, "Failed to free parameter buffer: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            // And ignore.
        }
    }

    return 0;

    // We want to make sure that if vaBeginPicture has been called, we also
    // call vaRenderPicture and vaEndPicture.  These calls may well fail or
    // do something else nasty, but once we're in this failure case there
    // isn't much else we can do.
fail_after_begin:
    vaRenderPicture(ctx->hwctx->display, ctx->va_context, &params_id, 1);
fail_after_render:
    vaEndPicture(ctx->hwctx->display, ctx->va_context);
fail:
    return err;
}