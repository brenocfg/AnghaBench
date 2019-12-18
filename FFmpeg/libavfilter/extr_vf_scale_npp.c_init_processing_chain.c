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
struct TYPE_21__ {int stage_needed; int in_fmt; int out_fmt; TYPE_11__* frames_ctx; TYPE_4__* planes_in; TYPE_3__* planes_out; } ;
struct TYPE_20__ {TYPE_1__** outputs; TYPE_2__** inputs; TYPE_5__* priv; } ;
struct TYPE_19__ {int sw_format; int /*<<< orphan*/  device_ref; } ;
struct TYPE_18__ {scalar_t__ format; scalar_t__ interp_algo; int passthrough; TYPE_8__* stages; } ;
struct TYPE_17__ {int width; int height; } ;
struct TYPE_16__ {int width; int height; } ;
struct TYPE_15__ {TYPE_11__* hw_frames_ctx; } ;
struct TYPE_14__ {void* hw_frames_ctx; } ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  TYPE_5__ NPPScaleContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int FF_ARRAY_ELEMS (TYPE_8__*) ; 
 scalar_t__ NPPI_INTER_CUBIC ; 
 scalar_t__ NPPI_INTER_LANCZOS ; 
 scalar_t__ NPPI_INTER_SUPER ; 
 size_t STAGE_DEINTERLEAVE ; 
 size_t STAGE_INTERLEAVE ; 
 size_t STAGE_RESIZE ; 
 void* av_buffer_ref (TYPE_11__*) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  format_is_supported (int) ; 
 int get_deinterleaved_format (int) ; 
 int init_stage (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_processing_chain(AVFilterContext *ctx, int in_width, int in_height,
                                 int out_width, int out_height)
{
    NPPScaleContext *s = ctx->priv;

    AVHWFramesContext *in_frames_ctx;

    enum AVPixelFormat in_format;
    enum AVPixelFormat out_format;
    enum AVPixelFormat in_deinterleaved_format;
    enum AVPixelFormat out_deinterleaved_format;

    int i, ret, last_stage = -1;

    /* check that we have a hw context */
    if (!ctx->inputs[0]->hw_frames_ctx) {
        av_log(ctx, AV_LOG_ERROR, "No hw context provided on input\n");
        return AVERROR(EINVAL);
    }
    in_frames_ctx = (AVHWFramesContext*)ctx->inputs[0]->hw_frames_ctx->data;
    in_format     = in_frames_ctx->sw_format;
    out_format    = (s->format == AV_PIX_FMT_NONE) ? in_format : s->format;

    if (!format_is_supported(in_format)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported input format: %s\n",
               av_get_pix_fmt_name(in_format));
        return AVERROR(ENOSYS);
    }
    if (!format_is_supported(out_format)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported output format: %s\n",
               av_get_pix_fmt_name(out_format));
        return AVERROR(ENOSYS);
    }

    in_deinterleaved_format  = get_deinterleaved_format(in_format);
    out_deinterleaved_format = get_deinterleaved_format(out_format);
    if (in_deinterleaved_format  == AV_PIX_FMT_NONE ||
        out_deinterleaved_format == AV_PIX_FMT_NONE)
        return AVERROR_BUG;

    /* figure out which stages need to be done */
    if (in_width != out_width || in_height != out_height ||
        in_deinterleaved_format != out_deinterleaved_format) {
        s->stages[STAGE_RESIZE].stage_needed = 1;

        if (s->interp_algo == NPPI_INTER_SUPER &&
            (out_width > in_width && out_height > in_height)) {
            s->interp_algo = NPPI_INTER_LANCZOS;
            av_log(ctx, AV_LOG_WARNING, "super-sampling not supported for output dimensions, using lanczos instead.\n");
        }
        if (s->interp_algo == NPPI_INTER_SUPER &&
            !(out_width < in_width && out_height < in_height)) {
            s->interp_algo = NPPI_INTER_CUBIC;
            av_log(ctx, AV_LOG_WARNING, "super-sampling not supported for output dimensions, using cubic instead.\n");
        }
    }

    if (!s->stages[STAGE_RESIZE].stage_needed && in_format == out_format)
        s->passthrough = 1;

    if (!s->passthrough) {
        if (in_format != in_deinterleaved_format)
            s->stages[STAGE_DEINTERLEAVE].stage_needed = 1;
        if (out_format != out_deinterleaved_format)
            s->stages[STAGE_INTERLEAVE].stage_needed = 1;
    }

    s->stages[STAGE_DEINTERLEAVE].in_fmt              = in_format;
    s->stages[STAGE_DEINTERLEAVE].out_fmt             = in_deinterleaved_format;
    s->stages[STAGE_DEINTERLEAVE].planes_in[0].width  = in_width;
    s->stages[STAGE_DEINTERLEAVE].planes_in[0].height = in_height;

    s->stages[STAGE_RESIZE].in_fmt               = in_deinterleaved_format;
    s->stages[STAGE_RESIZE].out_fmt              = out_deinterleaved_format;
    s->stages[STAGE_RESIZE].planes_in[0].width   = in_width;
    s->stages[STAGE_RESIZE].planes_in[0].height  = in_height;
    s->stages[STAGE_RESIZE].planes_out[0].width  = out_width;
    s->stages[STAGE_RESIZE].planes_out[0].height = out_height;

    s->stages[STAGE_INTERLEAVE].in_fmt              = out_deinterleaved_format;
    s->stages[STAGE_INTERLEAVE].out_fmt             = out_format;
    s->stages[STAGE_INTERLEAVE].planes_in[0].width  = out_width;
    s->stages[STAGE_INTERLEAVE].planes_in[0].height = out_height;

    /* init the hardware contexts */
    for (i = 0; i < FF_ARRAY_ELEMS(s->stages); i++) {
        if (!s->stages[i].stage_needed)
            continue;

        ret = init_stage(&s->stages[i], in_frames_ctx->device_ref);
        if (ret < 0)
            return ret;

        last_stage = i;
    }

    if (last_stage >= 0)
        ctx->outputs[0]->hw_frames_ctx = av_buffer_ref(s->stages[last_stage].frames_ctx);
    else
        ctx->outputs[0]->hw_frames_ctx = av_buffer_ref(ctx->inputs[0]->hw_frames_ctx);

    if (!ctx->outputs[0]->hw_frames_ctx)
        return AVERROR(ENOMEM);

    return 0;
}