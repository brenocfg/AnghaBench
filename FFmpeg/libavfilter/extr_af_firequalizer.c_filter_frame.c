#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_13__ {int channels; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_rate; TYPE_4__* dst; } ;
struct TYPE_12__ {int nb_samples; scalar_t__ pts; scalar_t__* extended_data; } ;
struct TYPE_11__ {int rdft_len; scalar_t__ next_pts; int fir_len; int /*<<< orphan*/  frame_nsamples_max; int /*<<< orphan*/  min_phase; scalar_t__ zero_phase; scalar_t__ conv_idx; scalar_t__ conv_buf; scalar_t__ multi; scalar_t__ kernel_buf; scalar_t__ fft_ctx; } ;
typedef  TYPE_1__ FIREqualizerContext ;
typedef  int /*<<< orphan*/  FFTComplex ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_make_q (int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fast_convolute (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,float*,int) ; 
 int /*<<< orphan*/  fast_convolute2 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,float*,float*,int) ; 
 int /*<<< orphan*/  fast_convolute_nonlinear (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,float*,int) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    FIREqualizerContext *s = ctx->priv;
    int ch;

    if (!s->min_phase) {
        for (ch = 0; ch + 1 < inlink->channels && s->fft_ctx; ch += 2) {
            fast_convolute2(s, s->kernel_buf, (FFTComplex *)(s->conv_buf + 2 * ch * s->rdft_len),
                            s->conv_idx + ch, (float *) frame->extended_data[ch],
                            (float *) frame->extended_data[ch+1], frame->nb_samples);
        }

        for ( ; ch < inlink->channels; ch++) {
            fast_convolute(s, s->kernel_buf + (s->multi ? ch * s->rdft_len : 0),
                        s->conv_buf + 2 * ch * s->rdft_len, s->conv_idx + ch,
                        (float *) frame->extended_data[ch], frame->nb_samples);
        }
    } else {
        for (ch = 0; ch < inlink->channels; ch++) {
            fast_convolute_nonlinear(s, s->kernel_buf + (s->multi ? ch * s->rdft_len : 0),
                                     s->conv_buf + 2 * ch * s->rdft_len, s->conv_idx + ch,
                                     (float *) frame->extended_data[ch], frame->nb_samples);
        }
    }

    s->next_pts = AV_NOPTS_VALUE;
    if (frame->pts != AV_NOPTS_VALUE) {
        s->next_pts = frame->pts + av_rescale_q(frame->nb_samples, av_make_q(1, inlink->sample_rate), inlink->time_base);
        if (s->zero_phase && !s->min_phase)
            frame->pts -= av_rescale_q(s->fir_len/2, av_make_q(1, inlink->sample_rate), inlink->time_base);
    }
    s->frame_nsamples_max = FFMAX(s->frame_nsamples_max, frame->nb_samples);
    return ff_filter_frame(ctx->outputs[0], frame);
}