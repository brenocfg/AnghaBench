#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_21__ {int stage_needed; int in_fmt; int out_fmt; TYPE_11__* frames_ctx; TYPE_2__* planes_out; TYPE_1__* planes_in; } ;
struct TYPE_20__ {TYPE_4__** outputs; TYPE_3__** inputs; TYPE_5__* priv; } ;
struct TYPE_19__ {int sw_format; int /*<<< orphan*/  device_ref; } ;
struct TYPE_18__ {scalar_t__ dir; int passthrough; TYPE_8__* stages; } ;
struct TYPE_17__ {void* hw_frames_ctx; } ;
struct TYPE_16__ {TYPE_11__* hw_frames_ctx; } ;
struct TYPE_15__ {int width; int height; } ;
struct TYPE_14__ {int width; int height; } ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  TYPE_5__ NPPTransposeContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int FF_ARRAY_ELEMS (TYPE_8__*) ; 
 scalar_t__ NPP_TRANSPOSE_CCLOCK_FLIP ; 
 scalar_t__ NPP_TRANSPOSE_CLOCK_FLIP ; 
 size_t STAGE_ROTATE ; 
 size_t STAGE_TRANSPOSE ; 
 void* av_buffer_ref (TYPE_11__*) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  format_is_supported (int) ; 
 int init_stage (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_processing_chain(AVFilterContext *ctx, int in_width, int in_height,
                                 int out_width, int out_height)
{
    NPPTransposeContext *s = ctx->priv;
    AVHWFramesContext *in_frames_ctx;
    enum AVPixelFormat format;
    int i, ret, last_stage = -1;
    int rot_width = out_width, rot_height = out_height;

    /* check that we have a hw context */
    if (!ctx->inputs[0]->hw_frames_ctx) {
        av_log(ctx, AV_LOG_ERROR, "No hw context provided on input\n");
        return AVERROR(EINVAL);
    }

    in_frames_ctx = (AVHWFramesContext*)ctx->inputs[0]->hw_frames_ctx->data;
    format        = in_frames_ctx->sw_format;

    if (!format_is_supported(format)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported input format: %s\n",
               av_get_pix_fmt_name(format));
        return AVERROR(ENOSYS);
    }

    if (s->dir != NPP_TRANSPOSE_CCLOCK_FLIP) {
        s->stages[STAGE_ROTATE].stage_needed = 1;
    }

    if (s->dir == NPP_TRANSPOSE_CCLOCK_FLIP || s->dir == NPP_TRANSPOSE_CLOCK_FLIP) {
        s->stages[STAGE_TRANSPOSE].stage_needed = 1;

        /* Rotating by 180° in case of clock_flip, or not at all for cclock_flip, so width/height unchanged by rotation */
        rot_width = in_width;
        rot_height = in_height;
    }

    s->stages[STAGE_ROTATE].in_fmt               = format;
    s->stages[STAGE_ROTATE].out_fmt              = format;
    s->stages[STAGE_ROTATE].planes_in[0].width   = in_width;
    s->stages[STAGE_ROTATE].planes_in[0].height  = in_height;
    s->stages[STAGE_ROTATE].planes_out[0].width  = rot_width;
    s->stages[STAGE_ROTATE].planes_out[0].height = rot_height;
    s->stages[STAGE_TRANSPOSE].in_fmt               = format;
    s->stages[STAGE_TRANSPOSE].out_fmt              = format;
    s->stages[STAGE_TRANSPOSE].planes_in[0].width   = rot_width;
    s->stages[STAGE_TRANSPOSE].planes_in[0].height  = rot_height;
    s->stages[STAGE_TRANSPOSE].planes_out[0].width  = out_width;
    s->stages[STAGE_TRANSPOSE].planes_out[0].height = out_height;

    /* init the hardware contexts */
    for (i = 0; i < FF_ARRAY_ELEMS(s->stages); i++) {
        if (!s->stages[i].stage_needed)
            continue;
        ret = init_stage(&s->stages[i], in_frames_ctx->device_ref);
        if (ret < 0)
            return ret;
        last_stage = i;
    }

    if (last_stage >= 0) {
        ctx->outputs[0]->hw_frames_ctx = av_buffer_ref(s->stages[last_stage].frames_ctx);
    } else {
        ctx->outputs[0]->hw_frames_ctx = av_buffer_ref(ctx->inputs[0]->hw_frames_ctx);
        s->passthrough = 1;
    }

    if (!ctx->outputs[0]->hw_frames_ctx)
        return AVERROR(ENOMEM);

    return 0;
}