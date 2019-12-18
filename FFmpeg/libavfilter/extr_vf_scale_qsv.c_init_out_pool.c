#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {int CropW; int CropH; } ;
typedef  TYPE_4__ mfxFrameInfo ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_25__ {TYPE_2__** inputs; TYPE_8__** outputs; TYPE_5__* priv; } ;
struct TYPE_24__ {TYPE_14__* hw_frames_ctx; } ;
struct TYPE_23__ {int sw_format; int initial_pool_size; void* height; void* width; int /*<<< orphan*/  format; TYPE_6__* hwctx; int /*<<< orphan*/  device_ref; } ;
struct TYPE_22__ {int nb_surfaces; TYPE_3__* surfaces; int /*<<< orphan*/  frame_type; } ;
struct TYPE_21__ {scalar_t__ format; } ;
struct TYPE_19__ {TYPE_4__ Info; } ;
struct TYPE_18__ {TYPE_1__* hw_frames_ctx; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_16__ {scalar_t__ data; } ;
typedef  TYPE_5__ QSVScaleContext ;
typedef  TYPE_6__ AVQSVFramesContext ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_8__ AVFilterLink ;
typedef  TYPE_9__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int,int) ; 
 TYPE_14__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_14__*) ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_init_hw_frames (TYPE_9__*,TYPE_8__*,int) ; 

__attribute__((used)) static int init_out_pool(AVFilterContext *ctx,
                         int out_width, int out_height)
{
    QSVScaleContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    AVHWFramesContext *in_frames_ctx;
    AVHWFramesContext *out_frames_ctx;
    AVQSVFramesContext *in_frames_hwctx;
    AVQSVFramesContext *out_frames_hwctx;
    enum AVPixelFormat in_format;
    enum AVPixelFormat out_format;
    int i, ret;

    /* check that we have a hw context */
    if (!ctx->inputs[0]->hw_frames_ctx) {
        av_log(ctx, AV_LOG_ERROR, "No hw context provided on input\n");
        return AVERROR(EINVAL);
    }
    in_frames_ctx   = (AVHWFramesContext*)ctx->inputs[0]->hw_frames_ctx->data;
    in_frames_hwctx = in_frames_ctx->hwctx;

    in_format     = in_frames_ctx->sw_format;
    out_format    = (s->format == AV_PIX_FMT_NONE) ? in_format : s->format;

    outlink->hw_frames_ctx = av_hwframe_ctx_alloc(in_frames_ctx->device_ref);
    if (!outlink->hw_frames_ctx)
        return AVERROR(ENOMEM);
    out_frames_ctx   = (AVHWFramesContext*)outlink->hw_frames_ctx->data;
    out_frames_hwctx = out_frames_ctx->hwctx;

    out_frames_ctx->format            = AV_PIX_FMT_QSV;
    out_frames_ctx->width             = FFALIGN(out_width,  16);
    out_frames_ctx->height            = FFALIGN(out_height, 16);
    out_frames_ctx->sw_format         = out_format;
    out_frames_ctx->initial_pool_size = 4;

    out_frames_hwctx->frame_type = in_frames_hwctx->frame_type;

    ret = ff_filter_init_hw_frames(ctx, outlink, 32);
    if (ret < 0)
        return ret;

    ret = av_hwframe_ctx_init(outlink->hw_frames_ctx);
    if (ret < 0)
        return ret;

    for (i = 0; i < out_frames_hwctx->nb_surfaces; i++) {
        mfxFrameInfo *info = &out_frames_hwctx->surfaces[i].Info;
        info->CropW = out_width;
        info->CropH = out_height;
    }

    return 0;
}