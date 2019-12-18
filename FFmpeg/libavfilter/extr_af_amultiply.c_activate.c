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
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {int nb_samples; scalar_t__* extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int /*<<< orphan*/  format; } ;
struct TYPE_19__ {int nb_inputs; TYPE_5__** inputs; int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
struct TYPE_18__ {scalar_t__* extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_17__ {int channels; int planes; TYPE_8__** frames; TYPE_1__* fdsp; int /*<<< orphan*/  samples_align; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* vector_dmul ) (double*,double const*,double const*,int) ;int /*<<< orphan*/  (* vector_fmul ) (float*,float const*,float const*,int) ;} ;
typedef  TYPE_2__ AudioMultiplyContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int /*<<< orphan*/ ) ; 
 int FFMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK_ALL (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_8__**) ; 
 scalar_t__ av_get_packed_sample_fmt (int /*<<< orphan*/ ) ; 
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* ff_get_audio_buffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_inlink_acknowledge_status (TYPE_5__*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_inlink_check_available_samples (TYPE_5__*,int) ; 
 int ff_inlink_consume_samples (TYPE_5__*,int,int,TYPE_8__**) ; 
 scalar_t__ ff_inlink_queued_samples (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (TYPE_5__*) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_outlink_set_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (float*,float const*,float const*,int) ; 
 int /*<<< orphan*/  stub2 (double*,double const*,double const*,int) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AudioMultiplyContext *s = ctx->priv;
    int i, ret, status;
    int nb_samples;
    int64_t pts;

    FF_FILTER_FORWARD_STATUS_BACK_ALL(ctx->outputs[0], ctx);

    nb_samples = FFMIN(ff_inlink_queued_samples(ctx->inputs[0]),
                       ff_inlink_queued_samples(ctx->inputs[1]));
    for (i = 0; i < ctx->nb_inputs && nb_samples > 0; i++) {
        if (s->frames[i])
            continue;

        if (ff_inlink_check_available_samples(ctx->inputs[i], nb_samples) > 0) {
            ret = ff_inlink_consume_samples(ctx->inputs[i], nb_samples, nb_samples, &s->frames[i]);
            if (ret < 0)
                return ret;
        }
    }

    if (s->frames[0] && s->frames[1]) {
        AVFrame *out;
        int plane_samples;

        if (av_sample_fmt_is_planar(ctx->inputs[0]->format))
            plane_samples = FFALIGN(s->frames[0]->nb_samples, s->samples_align);
        else
            plane_samples = FFALIGN(s->frames[0]->nb_samples * s->channels, s->samples_align);

        out = ff_get_audio_buffer(ctx->outputs[0], s->frames[0]->nb_samples);
        if (!out)
            return AVERROR(ENOMEM);

        out->pts = s->frames[0]->pts;

        if (av_get_packed_sample_fmt(ctx->inputs[0]->format) == AV_SAMPLE_FMT_FLT) {
            for (i = 0; i < s->planes; i++) {
                s->fdsp->vector_fmul((float *)out->extended_data[i],
                                     (const float *)s->frames[0]->extended_data[i],
                                     (const float *)s->frames[1]->extended_data[i],
                                     plane_samples);
            }
        } else {
            for (i = 0; i < s->planes; i++) {
                s->fdsp->vector_dmul((double *)out->extended_data[i],
                                     (const double *)s->frames[0]->extended_data[i],
                                     (const double *)s->frames[1]->extended_data[i],
                                     plane_samples);
            }
        }
        emms_c();

        av_frame_free(&s->frames[0]);
        av_frame_free(&s->frames[1]);

        ret = ff_filter_frame(ctx->outputs[0], out);
        if (ret < 0)
            return ret;
    }

    if (!nb_samples) {
        for (i = 0; i < 2; i++) {
            if (ff_inlink_acknowledge_status(ctx->inputs[i], &status, &pts)) {
                ff_outlink_set_status(ctx->outputs[0], status, pts);
                return 0;
            }
        }
    }

    if (ff_outlink_frame_wanted(ctx->outputs[0])) {
        for (i = 0; i < 2; i++) {
            if (ff_inlink_queued_samples(ctx->inputs[i]) > 0)
                continue;
            ff_inlink_request_frame(ctx->inputs[i]);
            return 0;
        }
    }
    return 0;
}