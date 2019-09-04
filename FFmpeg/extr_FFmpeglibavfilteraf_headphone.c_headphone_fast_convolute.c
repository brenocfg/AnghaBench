#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int* write; int* n_clippings; float** ringbuffer; TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_14__ {TYPE_2__* priv; } ;
struct TYPE_13__ {int channels; int nb_samples; scalar_t__* data; } ;
struct TYPE_12__ {float re; float im; } ;
struct TYPE_11__ {int ir_len; int buffer_length; int n_fft; int lfe_channel; float const gain_lfe; int /*<<< orphan*/ ** fft; int /*<<< orphan*/ ** ifft; TYPE_3__** temp_afft; TYPE_3__** temp_fft; TYPE_3__** data_hrtf; } ;
typedef  TYPE_2__ HeadphoneContext ;
typedef  int /*<<< orphan*/  FFTContext ;
typedef  TYPE_3__ FFTComplex ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int FFMIN (int const,int) ; 
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int fabsf (float) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int headphone_fast_convolute(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    HeadphoneContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in, *out = td->out;
    int offset = jobnr;
    int *write = &td->write[jobnr];
    FFTComplex *hrtf = s->data_hrtf[jobnr];
    int *n_clippings = &td->n_clippings[jobnr];
    float *ringbuffer = td->ringbuffer[jobnr];
    const int ir_len = s->ir_len;
    const float *src = (const float *)in->data[0];
    float *dst = (float *)out->data[0];
    const int in_channels = in->channels;
    const int buffer_length = s->buffer_length;
    const uint32_t modulo = (uint32_t)buffer_length - 1;
    FFTComplex *fft_in = s->temp_fft[jobnr];
    FFTComplex *fft_acc = s->temp_afft[jobnr];
    FFTContext *ifft = s->ifft[jobnr];
    FFTContext *fft = s->fft[jobnr];
    const int n_fft = s->n_fft;
    const float fft_scale = 1.0f / s->n_fft;
    FFTComplex *hrtf_offset;
    int wr = *write;
    int n_read;
    int i, j;

    dst += offset;

    n_read = FFMIN(ir_len, in->nb_samples);
    for (j = 0; j < n_read; j++) {
        dst[2 * j]     = ringbuffer[wr];
        ringbuffer[wr] = 0.0;
        wr  = (wr + 1) & modulo;
    }

    for (j = n_read; j < in->nb_samples; j++) {
        dst[2 * j] = 0;
    }

    memset(fft_acc, 0, sizeof(FFTComplex) * n_fft);

    for (i = 0; i < in_channels; i++) {
        if (i == s->lfe_channel) {
            for (j = 0; j < in->nb_samples; j++) {
                dst[2 * j] += src[i + j * in_channels] * s->gain_lfe;
            }
            continue;
        }

        offset = i * n_fft;
        hrtf_offset = hrtf + offset;

        memset(fft_in, 0, sizeof(FFTComplex) * n_fft);

        for (j = 0; j < in->nb_samples; j++) {
            fft_in[j].re = src[j * in_channels + i];
        }

        av_fft_permute(fft, fft_in);
        av_fft_calc(fft, fft_in);
        for (j = 0; j < n_fft; j++) {
            const FFTComplex *hcomplex = hrtf_offset + j;
            const float re = fft_in[j].re;
            const float im = fft_in[j].im;

            fft_acc[j].re += re * hcomplex->re - im * hcomplex->im;
            fft_acc[j].im += re * hcomplex->im + im * hcomplex->re;
        }
    }

    av_fft_permute(ifft, fft_acc);
    av_fft_calc(ifft, fft_acc);

    for (j = 0; j < in->nb_samples; j++) {
        dst[2 * j] += fft_acc[j].re * fft_scale;
    }

    for (j = 0; j < ir_len - 1; j++) {
        int write_pos = (wr + j) & modulo;

        *(ringbuffer + write_pos) += fft_acc[in->nb_samples + j].re * fft_scale;
    }

    for (i = 0; i < out->nb_samples; i++) {
        if (fabsf(dst[0]) > 1) {
            n_clippings[0]++;
        }

        dst += 2;
    }

    *write = wr;

    return 0;
}