#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_15__ {int channels; TYPE_4__* dst; } ;
struct TYPE_14__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_13__ {int delay_buf_pos; int max_samples; int lfo_length; int channel_phase; double* lfo; int lfo_pos; double* delay_last; double feedback_gain; scalar_t__ interpolation; double in_gain; double delay_gain; scalar_t__* delay_buffer; } ;
typedef  TYPE_1__ FlangerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INTERPOLATION_LINEAR ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (int /*<<< orphan*/ ,int) ; 
 double modf (double,double*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    FlangerContext *s = ctx->priv;
    AVFrame *out_frame;
    int chan, i;

    if (av_frame_is_writable(frame)) {
        out_frame = frame;
    } else {
        out_frame = ff_get_audio_buffer(ctx->outputs[0], frame->nb_samples);
        if (!out_frame) {
            av_frame_free(&frame);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out_frame, frame);
    }

    for (i = 0; i < frame->nb_samples; i++) {

        s->delay_buf_pos = (s->delay_buf_pos + s->max_samples - 1) % s->max_samples;

        for (chan = 0; chan < inlink->channels; chan++) {
            double *src = (double *)frame->extended_data[chan];
            double *dst = (double *)out_frame->extended_data[chan];
            double delayed_0, delayed_1;
            double delayed;
            double in, out;
            int channel_phase = chan * s->lfo_length * s->channel_phase + .5;
            double delay = s->lfo[(s->lfo_pos + channel_phase) % s->lfo_length];
            int int_delay = (int)delay;
            double frac_delay = modf(delay, &delay);
            double *delay_buffer = (double *)s->delay_buffer[chan];

            in = src[i];
            delay_buffer[s->delay_buf_pos] = in + s->delay_last[chan] *
                                                           s->feedback_gain;
            delayed_0 = delay_buffer[(s->delay_buf_pos + int_delay++) % s->max_samples];
            delayed_1 = delay_buffer[(s->delay_buf_pos + int_delay++) % s->max_samples];

            if (s->interpolation == INTERPOLATION_LINEAR) {
                delayed = delayed_0 + (delayed_1 - delayed_0) * frac_delay;
            } else {
                double a, b;
                double delayed_2 = delay_buffer[(s->delay_buf_pos + int_delay++) % s->max_samples];
                delayed_2 -= delayed_0;
                delayed_1 -= delayed_0;
                a = delayed_2 * .5 - delayed_1;
                b = delayed_1 *  2 - delayed_2 *.5;
                delayed = delayed_0 + (a * frac_delay + b) * frac_delay;
            }

            s->delay_last[chan] = delayed;
            out = in * s->in_gain + delayed * s->delay_gain;
            dst[i] = out;
        }
        s->lfo_pos = (s->lfo_pos + 1) % s->lfo_length;
    }

    if (frame != out_frame)
        av_frame_free(&frame);

    return ff_filter_frame(ctx->outputs[0], out_frame);
}