#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  format; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  time_base; TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__ pts; int /*<<< orphan*/  format; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  extended_data; } ;
struct TYPE_15__ {scalar_t__ next_pts; scalar_t__ next_in_pts; int got_output; scalar_t__ resampling; scalar_t__ avr; } ;
typedef  TYPE_1__ ResampleContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 void* av_rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avresample_available (scalar_t__) ; 
 int avresample_convert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int avresample_get_delay (scalar_t__) ; 
 int avresample_get_out_samples (scalar_t__,int) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext  *ctx = inlink->dst;
    ResampleContext    *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int ret;

    if (s->avr) {
        AVFrame *out;
        int delay, nb_samples;

        /* maximum possible samples lavr can output */
        delay      = avresample_get_delay(s->avr);
        nb_samples = avresample_get_out_samples(s->avr, in->nb_samples);

        out = ff_get_audio_buffer(outlink, nb_samples);
        if (!out) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ret = avresample_convert(s->avr, out->extended_data, out->linesize[0],
                                 nb_samples, in->extended_data, in->linesize[0],
                                 in->nb_samples);
        if (ret <= 0) {
            av_frame_free(&out);
            if (ret < 0)
                goto fail;
        }

        av_assert0(!avresample_available(s->avr));

        if (s->resampling && s->next_pts == AV_NOPTS_VALUE) {
            if (in->pts == AV_NOPTS_VALUE) {
                av_log(ctx, AV_LOG_WARNING, "First timestamp is missing, "
                       "assuming 0.\n");
                s->next_pts = 0;
            } else
                s->next_pts = av_rescale_q(in->pts, inlink->time_base,
                                           outlink->time_base);
        }

        if (ret > 0) {
            out->nb_samples = ret;

            ret = av_frame_copy_props(out, in);
            if (ret < 0) {
                av_frame_free(&out);
                goto fail;
            }

            if (s->resampling) {
                out->sample_rate = outlink->sample_rate;
                /* Only convert in->pts if there is a discontinuous jump.
                   This ensures that out->pts tracks the number of samples actually
                   output by the resampler in the absence of such a jump.
                   Otherwise, the rounding in av_rescale_q() and av_rescale()
                   causes off-by-1 errors. */
                if (in->pts != AV_NOPTS_VALUE && in->pts != s->next_in_pts) {
                    out->pts = av_rescale_q(in->pts, inlink->time_base,
                                                outlink->time_base) -
                                   av_rescale(delay, outlink->sample_rate,
                                              inlink->sample_rate);
                } else
                    out->pts = s->next_pts;

                s->next_pts = out->pts + out->nb_samples;
                s->next_in_pts = in->pts + in->nb_samples;
            } else
                out->pts = in->pts;

            ret = ff_filter_frame(outlink, out);
            s->got_output = 1;
        }

fail:
        av_frame_free(&in);
    } else {
        in->format = outlink->format;
        ret = ff_filter_frame(outlink, in);
        s->got_output = 1;
    }

    return ret;
}