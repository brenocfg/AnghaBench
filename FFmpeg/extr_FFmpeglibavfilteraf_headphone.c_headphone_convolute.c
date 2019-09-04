#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int* write; int** delay; float** ir; int* n_clippings; float** ringbuffer; float** temp_src; TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {int channels; int nb_samples; scalar_t__* data; } ;
struct TYPE_9__ {int ir_len; int air_len; int buffer_length; int lfe_channel; float gain_lfe; TYPE_1__* fdsp; } ;
struct TYPE_7__ {scalar_t__ (* scalarproduct_float ) (float const*,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ HeadphoneContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFALIGN (int const,int) ; 
 int FFMIN (int const,int const) ; 
 int fabsf (float) ; 
 int /*<<< orphan*/  memcpy (float*,float const* const,int const) ; 
 scalar_t__ stub1 (float const*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int headphone_convolute(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    HeadphoneContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in, *out = td->out;
    int offset = jobnr;
    int *write = &td->write[jobnr];
    const int *const delay = td->delay[jobnr];
    const float *const ir = td->ir[jobnr];
    int *n_clippings = &td->n_clippings[jobnr];
    float *ringbuffer = td->ringbuffer[jobnr];
    float *temp_src = td->temp_src[jobnr];
    const int ir_len = s->ir_len;
    const int air_len = s->air_len;
    const float *src = (const float *)in->data[0];
    float *dst = (float *)out->data[0];
    const int in_channels = in->channels;
    const int buffer_length = s->buffer_length;
    const uint32_t modulo = (uint32_t)buffer_length - 1;
    float *buffer[16];
    int wr = *write;
    int read;
    int i, l;

    dst += offset;
    for (l = 0; l < in_channels; l++) {
        buffer[l] = ringbuffer + l * buffer_length;
    }

    for (i = 0; i < in->nb_samples; i++) {
        const float *temp_ir = ir;

        *dst = 0;
        for (l = 0; l < in_channels; l++) {
            *(buffer[l] + wr) = src[l];
        }

        for (l = 0; l < in_channels; l++) {
            const float *const bptr = buffer[l];

            if (l == s->lfe_channel) {
                *dst += *(buffer[s->lfe_channel] + wr) * s->gain_lfe;
                temp_ir += air_len;
                continue;
            }

            read = (wr - *(delay + l) - (ir_len - 1) + buffer_length) & modulo;

            if (read + ir_len < buffer_length) {
                memcpy(temp_src, bptr + read, ir_len * sizeof(*temp_src));
            } else {
                int len = FFMIN(air_len - (read % ir_len), buffer_length - read);

                memcpy(temp_src, bptr + read, len * sizeof(*temp_src));
                memcpy(temp_src + len, bptr, (air_len - len) * sizeof(*temp_src));
            }

            dst[0] += s->fdsp->scalarproduct_float(temp_ir, temp_src, FFALIGN(ir_len, 32));
            temp_ir += air_len;
        }

        if (fabsf(dst[0]) > 1)
            n_clippings[0]++;

        dst += 2;
        src += in_channels;
        wr   = (wr + 1) & modulo;
    }

    *write = wr;

    return 0;
}