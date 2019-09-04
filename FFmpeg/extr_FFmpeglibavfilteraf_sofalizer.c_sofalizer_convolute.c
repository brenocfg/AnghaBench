#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int* write; int** delay; float** ir; int* n_clippings; float** ringbuffer; float** temp_src; TYPE_5__* out; TYPE_5__* in; } ;
typedef  TYPE_3__ ThreadData ;
struct TYPE_13__ {TYPE_4__* priv; } ;
struct TYPE_12__ {scalar_t__ format; int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_8__ {int ir_samples; int n_samples; } ;
struct TYPE_11__ {int n_conv; int buffer_length; int lfe_channel; float gain_lfe; TYPE_2__* fdsp; TYPE_1__ sofa; } ;
struct TYPE_9__ {scalar_t__ (* scalarproduct_float ) (float const*,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ SOFAlizerContext ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  FFALIGN (int const,int) ; 
 int FFMIN (int const,int const) ; 
 int fabsf (float) ; 
 int /*<<< orphan*/  memmove (float*,float const* const,int const) ; 
 scalar_t__ stub1 (float const*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sofalizer_convolute(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    SOFAlizerContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in, *out = td->out;
    int offset = jobnr;
    int *write = &td->write[jobnr];
    const int *const delay = td->delay[jobnr];
    const float *const ir = td->ir[jobnr];
    int *n_clippings = &td->n_clippings[jobnr];
    float *ringbuffer = td->ringbuffer[jobnr];
    float *temp_src = td->temp_src[jobnr];
    const int ir_samples = s->sofa.ir_samples; /* length of one IR */
    const int n_samples = s->sofa.n_samples;
    const int planar = in->format == AV_SAMPLE_FMT_FLTP;
    const int mult = 1 + !planar;
    const float *src = (const float *)in->extended_data[0]; /* get pointer to audio input buffer */
    float *dst = (float *)out->extended_data[jobnr * planar]; /* get pointer to audio output buffer */
    const int in_channels = s->n_conv; /* number of input channels */
    /* ring buffer length is: longest IR plus max. delay -> next power of 2 */
    const int buffer_length = s->buffer_length;
    /* -1 for AND instead of MODULO (applied to powers of 2): */
    const uint32_t modulo = (uint32_t)buffer_length - 1;
    float *buffer[16]; /* holds ringbuffer for each input channel */
    int wr = *write;
    int read;
    int i, l;

    if (!planar)
        dst += offset;

    for (l = 0; l < in_channels; l++) {
        /* get starting address of ringbuffer for each input channel */
        buffer[l] = ringbuffer + l * buffer_length;
    }

    for (i = 0; i < in->nb_samples; i++) {
        const float *temp_ir = ir; /* using same set of IRs for each sample */

        dst[0] = 0;
        if (planar) {
            for (l = 0; l < in_channels; l++) {
                const float *srcp = (const float *)in->extended_data[l];

                /* write current input sample to ringbuffer (for each channel) */
                buffer[l][wr] = srcp[i];
            }
        } else {
            for (l = 0; l < in_channels; l++) {
                /* write current input sample to ringbuffer (for each channel) */
                buffer[l][wr] = src[l];
            }
        }

        /* loop goes through all channels to be convolved */
        for (l = 0; l < in_channels; l++) {
            const float *const bptr = buffer[l];

            if (l == s->lfe_channel) {
                /* LFE is an input channel but requires no convolution */
                /* apply gain to LFE signal and add to output buffer */
                dst[0] += *(buffer[s->lfe_channel] + wr) * s->gain_lfe;
                temp_ir += n_samples;
                continue;
            }

            /* current read position in ringbuffer: input sample write position
             * - delay for l-th ch. + diff. betw. IR length and buffer length
             * (mod buffer length) */
            read = (wr - delay[l] - (ir_samples - 1) + buffer_length) & modulo;

            if (read + ir_samples < buffer_length) {
                memmove(temp_src, bptr + read, ir_samples * sizeof(*temp_src));
            } else {
                int len = FFMIN(n_samples - (read % ir_samples), buffer_length - read);

                memmove(temp_src, bptr + read, len * sizeof(*temp_src));
                memmove(temp_src + len, bptr, (n_samples - len) * sizeof(*temp_src));
            }

            /* multiply signal and IR, and add up the results */
            dst[0] += s->fdsp->scalarproduct_float(temp_ir, temp_src, FFALIGN(ir_samples, 32));
            temp_ir += n_samples;
        }

        /* clippings counter */
        if (fabsf(dst[0]) > 1)
            n_clippings[0]++;

        /* move output buffer pointer by +2 to get to next sample of processed channel: */
        dst += mult;
        src += in_channels;
        wr   = (wr + 1) & modulo; /* update ringbuffer write position */
    }

    *write = wr; /* remember write position in ringbuffer for next call */

    return 0;
}