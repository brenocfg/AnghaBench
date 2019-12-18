#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int* write; int* n_clippings; float** ringbuffer; TYPE_5__* out; TYPE_5__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_16__ {TYPE_3__* priv; } ;
struct TYPE_15__ {scalar_t__ format; int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_14__ {float re; float im; } ;
struct TYPE_11__ {int ir_samples; } ;
struct TYPE_13__ {int n_conv; int buffer_length; int n_fft; int lfe_channel; float const gain_lfe; int /*<<< orphan*/ ** fft; int /*<<< orphan*/ ** ifft; TYPE_4__** temp_afft; TYPE_4__** temp_fft; TYPE_1__ sofa; TYPE_4__** data_hrtf; } ;
typedef  TYPE_3__ SOFAlizerContext ;
typedef  int /*<<< orphan*/  FFTContext ;
typedef  TYPE_4__ FFTComplex ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 scalar_t__ AV_SAMPLE_FMT_FLTP ; 
 int FFMIN (int const,int) ; 
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int fabsf (float) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sofalizer_fast_convolute(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    SOFAlizerContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in, *out = td->out;
    int offset = jobnr;
    int *write = &td->write[jobnr];
    FFTComplex *hrtf = s->data_hrtf[jobnr]; /* get pointers to current HRTF data */
    int *n_clippings = &td->n_clippings[jobnr];
    float *ringbuffer = td->ringbuffer[jobnr];
    const int ir_samples = s->sofa.ir_samples; /* length of one IR */
    const int planar = in->format == AV_SAMPLE_FMT_FLTP;
    const int mult = 1 + !planar;
    float *dst = (float *)out->extended_data[jobnr * planar]; /* get pointer to audio output buffer */
    const int in_channels = s->n_conv; /* number of input channels */
    /* ring buffer length is: longest IR plus max. delay -> next power of 2 */
    const int buffer_length = s->buffer_length;
    /* -1 for AND instead of MODULO (applied to powers of 2): */
    const uint32_t modulo = (uint32_t)buffer_length - 1;
    FFTComplex *fft_in = s->temp_fft[jobnr]; /* temporary array for FFT input/output data */
    FFTComplex *fft_acc = s->temp_afft[jobnr];
    FFTContext *ifft = s->ifft[jobnr];
    FFTContext *fft = s->fft[jobnr];
    const int n_conv = s->n_conv;
    const int n_fft = s->n_fft;
    const float fft_scale = 1.0f / s->n_fft;
    FFTComplex *hrtf_offset;
    int wr = *write;
    int n_read;
    int i, j;

    if (!planar)
        dst += offset;

    /* find minimum between number of samples and output buffer length:
     * (important, if one IR is longer than the output buffer) */
    n_read = FFMIN(ir_samples, in->nb_samples);
    for (j = 0; j < n_read; j++) {
        /* initialize output buf with saved signal from overflow buf */
        dst[mult * j]  = ringbuffer[wr];
        ringbuffer[wr] = 0.0f; /* re-set read samples to zero */
        /* update ringbuffer read/write position */
        wr  = (wr + 1) & modulo;
    }

    /* initialize rest of output buffer with 0 */
    for (j = n_read; j < in->nb_samples; j++) {
        dst[mult * j] = 0;
    }

    /* fill FFT accumulation with 0 */
    memset(fft_acc, 0, sizeof(FFTComplex) * n_fft);

    for (i = 0; i < n_conv; i++) {
        const float *src = (const float *)in->extended_data[i * planar]; /* get pointer to audio input buffer */

        if (i == s->lfe_channel) { /* LFE */
            if (in->format == AV_SAMPLE_FMT_FLT) {
                for (j = 0; j < in->nb_samples; j++) {
                    /* apply gain to LFE signal and add to output buffer */
                    dst[2 * j] += src[i + j * in_channels] * s->gain_lfe;
                }
            } else {
                for (j = 0; j < in->nb_samples; j++) {
                    /* apply gain to LFE signal and add to output buffer */
                    dst[j] += src[j] * s->gain_lfe;
                }
            }
            continue;
        }

        /* outer loop: go through all input channels to be convolved */
        offset = i * n_fft; /* no. samples already processed */
        hrtf_offset = hrtf + offset;

        /* fill FFT input with 0 (we want to zero-pad) */
        memset(fft_in, 0, sizeof(FFTComplex) * n_fft);

        if (in->format == AV_SAMPLE_FMT_FLT) {
            for (j = 0; j < in->nb_samples; j++) {
                /* prepare input for FFT */
                /* write all samples of current input channel to FFT input array */
                fft_in[j].re = src[j * in_channels + i];
            }
        } else {
            for (j = 0; j < in->nb_samples; j++) {
                /* prepare input for FFT */
                /* write all samples of current input channel to FFT input array */
                fft_in[j].re = src[j];
            }
        }

        /* transform input signal of current channel to frequency domain */
        av_fft_permute(fft, fft_in);
        av_fft_calc(fft, fft_in);
        for (j = 0; j < n_fft; j++) {
            const FFTComplex *hcomplex = hrtf_offset + j;
            const float re = fft_in[j].re;
            const float im = fft_in[j].im;

            /* complex multiplication of input signal and HRTFs */
            /* output channel (real): */
            fft_acc[j].re += re * hcomplex->re - im * hcomplex->im;
            /* output channel (imag): */
            fft_acc[j].im += re * hcomplex->im + im * hcomplex->re;
        }
    }

    /* transform output signal of current channel back to time domain */
    av_fft_permute(ifft, fft_acc);
    av_fft_calc(ifft, fft_acc);

    for (j = 0; j < in->nb_samples; j++) {
        /* write output signal of current channel to output buffer */
        dst[mult * j] += fft_acc[j].re * fft_scale;
    }

    for (j = 0; j < ir_samples - 1; j++) { /* overflow length is IR length - 1 */
        /* write the rest of output signal to overflow buffer */
        int write_pos = (wr + j) & modulo;

        *(ringbuffer + write_pos) += fft_acc[in->nb_samples + j].re * fft_scale;
    }

    /* go through all samples of current output buffer: count clippings */
    for (i = 0; i < out->nb_samples; i++) {
        /* clippings counter */
        if (fabsf(dst[i * mult]) > 1) { /* if current output sample > 1 */
            n_clippings[0]++;
        }
    }

    /* remember read/write position in ringbuffer for next call */
    *write = wr;

    return 0;
}