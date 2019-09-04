#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {double level_in; double level_out; double mix; double sdiff; int /*<<< orphan*/  lfo; scalar_t__ is_lfo; int /*<<< orphan*/ * sr; scalar_t__ samples; int /*<<< orphan*/  round; scalar_t__ smin; } ;
struct TYPE_19__ {TYPE_2__** outputs; TYPE_4__* priv; } ;
struct TYPE_18__ {int channels; TYPE_3__* dst; } ;
struct TYPE_17__ {int nb_samples; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ ACrusherContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_1__*) ; 
 double const bitreduction (TYPE_4__*,double) ; 
 int ff_filter_frame (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* ff_get_audio_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lfo_advance (int /*<<< orphan*/ *,int) ; 
 double lfo_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round (scalar_t__) ; 
 double const samplereduction (TYPE_4__*,int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    ACrusherContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    const double *src = (const double *)in->data[0];
    double *dst;
    const double level_in = s->level_in;
    const double level_out = s->level_out;
    const double mix = s->mix;
    int n, c;

    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_audio_buffer(inlink, in->nb_samples);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    dst = (double *)out->data[0];
    for (n = 0; n < in->nb_samples; n++) {
        if (s->is_lfo) {
            s->samples = s->smin + s->sdiff * (lfo_get(&s->lfo) + 0.5);
            s->round = round(s->samples);
        }

        for (c = 0; c < inlink->channels; c++) {
            double sample = src[c] * level_in;

            sample = mix * samplereduction(s, &s->sr[c], sample) + src[c] * (1. - mix) * level_in;
            dst[c] = bitreduction(s, sample) * level_out;
        }
        src += c;
        dst += c;

        if (s->is_lfo)
            lfo_advance(&s->lfo, 1);
    }

    if (in != out)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}