#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* priv; } ;
struct TYPE_11__ {int sample_rate; int channels; int min_samples; int max_samples; int partial_buf_size; TYPE_3__* dst; } ;
struct TYPE_10__ {int fir_len; int delay; int remaining; int rdft_len; int nsamples_max; int cepstrum_len; int analysis_rdft_len; int accuracy; scalar_t__ fixed; void* conv_idx; void* conv_buf; void* kernel_buf; void* kernel_tmp_buf; void* analysis_buf; scalar_t__ multi; void* dump_buf; void* analysis_rdft; scalar_t__ dumpfile; void* analysis_irdft; void* cepstrum_buf; void* cepstrum_irdft; void* cepstrum_rdft; scalar_t__ min_phase; int /*<<< orphan*/  fft_ctx; scalar_t__ fft2; void* irdft; void* rdft; scalar_t__ frame_nsamples_max; scalar_t__ next_pts; } ;
typedef  TYPE_1__ FIREqualizerContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DFT_R2C ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  IDFT_C2R ; 
 int RDFT_BITS_MAX ; 
 int RDFT_BITS_MIN ; 
 int /*<<< orphan*/  SELECT_GAIN (TYPE_1__*) ; 
 int /*<<< orphan*/  SELECT_GAIN_ENTRY (TYPE_1__*) ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_fft_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_malloc_array (int,int) ; 
 void* av_rdft_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_uninit (TYPE_1__*) ; 
 int generate_kernel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    FIREqualizerContext *s = ctx->priv;
    int rdft_bits;

    common_uninit(s);

    s->next_pts = 0;
    s->frame_nsamples_max = 0;

    s->fir_len = FFMAX(2 * (int)(inlink->sample_rate * s->delay) + 1, 3);
    s->remaining = s->fir_len - 1;

    for (rdft_bits = RDFT_BITS_MIN; rdft_bits <= RDFT_BITS_MAX; rdft_bits++) {
        s->rdft_len = 1 << rdft_bits;
        s->nsamples_max = s->rdft_len - s->fir_len + 1;
        if (s->nsamples_max * 2 >= s->fir_len)
            break;
    }

    if (rdft_bits > RDFT_BITS_MAX) {
        av_log(ctx, AV_LOG_ERROR, "too large delay, please decrease it.\n");
        return AVERROR(EINVAL);
    }

    if (!(s->rdft = av_rdft_init(rdft_bits, DFT_R2C)) || !(s->irdft = av_rdft_init(rdft_bits, IDFT_C2R)))
        return AVERROR(ENOMEM);

    if (s->fft2 && !s->multi && inlink->channels > 1 && !(s->fft_ctx = av_fft_init(rdft_bits, 0)))
        return AVERROR(ENOMEM);

    if (s->min_phase) {
        int cepstrum_bits = rdft_bits + 2;
        if (cepstrum_bits > RDFT_BITS_MAX) {
            av_log(ctx, AV_LOG_ERROR, "too large delay, please decrease it.\n");
            return AVERROR(EINVAL);
        }

        cepstrum_bits = FFMIN(RDFT_BITS_MAX, cepstrum_bits + 1);
        s->cepstrum_rdft = av_rdft_init(cepstrum_bits, DFT_R2C);
        s->cepstrum_irdft = av_rdft_init(cepstrum_bits, IDFT_C2R);
        if (!s->cepstrum_rdft || !s->cepstrum_irdft)
            return AVERROR(ENOMEM);

        s->cepstrum_len = 1 << cepstrum_bits;
        s->cepstrum_buf = av_malloc_array(s->cepstrum_len, sizeof(*s->cepstrum_buf));
        if (!s->cepstrum_buf)
            return AVERROR(ENOMEM);
    }

    for ( ; rdft_bits <= RDFT_BITS_MAX; rdft_bits++) {
        s->analysis_rdft_len = 1 << rdft_bits;
        if (inlink->sample_rate <= s->accuracy * s->analysis_rdft_len)
            break;
    }

    if (rdft_bits > RDFT_BITS_MAX) {
        av_log(ctx, AV_LOG_ERROR, "too small accuracy, please increase it.\n");
        return AVERROR(EINVAL);
    }

    if (!(s->analysis_irdft = av_rdft_init(rdft_bits, IDFT_C2R)))
        return AVERROR(ENOMEM);

    if (s->dumpfile) {
        s->analysis_rdft = av_rdft_init(rdft_bits, DFT_R2C);
        s->dump_buf = av_malloc_array(s->analysis_rdft_len, sizeof(*s->dump_buf));
    }

    s->analysis_buf = av_malloc_array(s->analysis_rdft_len, sizeof(*s->analysis_buf));
    s->kernel_tmp_buf = av_malloc_array(s->rdft_len * (s->multi ? inlink->channels : 1), sizeof(*s->kernel_tmp_buf));
    s->kernel_buf = av_malloc_array(s->rdft_len * (s->multi ? inlink->channels : 1), sizeof(*s->kernel_buf));
    s->conv_buf   = av_calloc(2 * s->rdft_len * inlink->channels, sizeof(*s->conv_buf));
    s->conv_idx   = av_calloc(inlink->channels, sizeof(*s->conv_idx));
    if (!s->analysis_buf || !s->kernel_tmp_buf || !s->kernel_buf || !s->conv_buf || !s->conv_idx)
        return AVERROR(ENOMEM);

    av_log(ctx, AV_LOG_DEBUG, "sample_rate = %d, channels = %d, analysis_rdft_len = %d, rdft_len = %d, fir_len = %d, nsamples_max = %d.\n",
           inlink->sample_rate, inlink->channels, s->analysis_rdft_len, s->rdft_len, s->fir_len, s->nsamples_max);

    if (s->fixed)
        inlink->min_samples = inlink->max_samples = inlink->partial_buf_size = s->nsamples_max;

    return generate_kernel(ctx, SELECT_GAIN(s), SELECT_GAIN_ENTRY(s));
}