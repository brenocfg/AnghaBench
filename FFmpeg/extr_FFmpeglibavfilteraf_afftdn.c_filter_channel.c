#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_19__ {float re; scalar_t__ im; } ;
struct TYPE_18__ {TYPE_3__* priv; } ;
struct TYPE_17__ {int channels; scalar_t__* extended_data; } ;
struct TYPE_16__ {int block_count; int window_length; float const* window; int fft_length2; int /*<<< orphan*/  fft_length; int /*<<< orphan*/  track_noise; TYPE_2__* dnch; } ;
struct TYPE_15__ {double* out_samples; double sfm_fail_total; double sfm_threshold; double sfm_alpha; TYPE_8__* fft_data; int /*<<< orphan*/  ifft; int /*<<< orphan*/  prior_band_excit; int /*<<< orphan*/  prior; int /*<<< orphan*/  fft; scalar_t__* sfm_fail_flags; } ;
typedef  TYPE_2__ DeNoiseChannel ;
typedef  TYPE_3__ AudioFFTDeNoiseContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  postprocess (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preprocess (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_frame (TYPE_3__*,TYPE_2__*,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_channel(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AudioFFTDeNoiseContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    const int start = (in->channels * jobnr) / nb_jobs;
    const int end = (in->channels * (jobnr+1)) / nb_jobs;

    for (int ch = start; ch < end; ch++) {
        DeNoiseChannel *dnch = &s->dnch[ch];
        const float *src = (const float *)in->extended_data[ch];
        double *dst = dnch->out_samples;

        if (s->track_noise) {
            int i = s->block_count & 0x1FF;

            if (dnch->sfm_fail_flags[i])
                dnch->sfm_fail_total--;
            dnch->sfm_fail_flags[i] = 0;
            dnch->sfm_threshold *= 1.0 - dnch->sfm_alpha;
            dnch->sfm_threshold += dnch->sfm_alpha * (0.5 + (1.0 / 640) * dnch->sfm_fail_total);
        }

        for (int m = 0; m < s->window_length; m++) {
            dnch->fft_data[m].re = s->window[m] * src[m] * (1LL << 24);
            dnch->fft_data[m].im = 0;
        }

        for (int m = s->window_length; m < s->fft_length2; m++) {
            dnch->fft_data[m].re = 0;
            dnch->fft_data[m].im = 0;
        }

        av_fft_permute(dnch->fft, dnch->fft_data);
        av_fft_calc(dnch->fft, dnch->fft_data);

        preprocess(dnch->fft_data, s->fft_length);
        process_frame(s, dnch, dnch->fft_data,
                      dnch->prior,
                      dnch->prior_band_excit,
                      s->track_noise);
        postprocess(dnch->fft_data, s->fft_length);

        av_fft_permute(dnch->ifft, dnch->fft_data);
        av_fft_calc(dnch->ifft, dnch->fft_data);

        for (int m = 0; m < s->window_length; m++)
            dst[m] += s->window[m] * dnch->fft_data[m].re / (1LL << 24);
    }

    return 0;
}