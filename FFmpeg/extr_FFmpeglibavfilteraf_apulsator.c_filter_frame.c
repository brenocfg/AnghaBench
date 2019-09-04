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
struct TYPE_18__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_17__ {TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_15__ {double level_out; double level_in; double amount; int /*<<< orphan*/  lfoR; int /*<<< orphan*/  lfoL; } ;
typedef  TYPE_1__ AudioPulsatorContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lfo_advance (int /*<<< orphan*/ *,int) ; 
 double lfo_get_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AudioPulsatorContext *s = ctx->priv;
    const double *src = (const double *)in->data[0];
    const int nb_samples = in->nb_samples;
    const double level_out = s->level_out;
    const double level_in = s->level_in;
    const double amount = s->amount;
    AVFrame *out;
    double *dst;
    int n;

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

    for (n = 0; n < nb_samples; n++) {
        double outL;
        double outR;
        double inL = src[0] * level_in;
        double inR = src[1] * level_in;
        double procL = inL;
        double procR = inR;

        procL *= lfo_get_value(&s->lfoL) * 0.5 + amount / 2;
        procR *= lfo_get_value(&s->lfoR) * 0.5 + amount / 2;

        outL = procL + inL * (1 - amount);
        outR = procR + inR * (1 - amount);

        outL *= level_out;
        outR *= level_out;

        dst[0] = outL;
        dst[1] = outR;

        lfo_advance(&s->lfoL, 1);
        lfo_advance(&s->lfoR, 1);

        dst += 2;
        src += 2;
    }

    if (in != out)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}