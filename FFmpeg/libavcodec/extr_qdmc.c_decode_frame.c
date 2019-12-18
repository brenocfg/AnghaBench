#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_14__ {float re; float im; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* fft_calc ) (TYPE_2__*,TYPE_3__*) ;int /*<<< orphan*/  (* fft_permute ) (TYPE_2__*,TYPE_3__*) ;} ;
struct TYPE_12__ {int fft_offset; int frame_size; float* buffer_ptr; float* buffer; size_t nb_channels; size_t buffer_offset; int subframe_size; float** fft_buffer; TYPE_3__** cmplx; TYPE_2__ fft_ctx; } ;
typedef  TYPE_1__ QDMCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  INT16_MAX ; 
 int /*<<< orphan*/  INT16_MIN ; 
 int /*<<< orphan*/  add_noise (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  add_waves (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_clipf (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int read_noise_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int read_wave_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_label (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int decode_frame(QDMCContext *s, GetBitContext *gb, int16_t *out)
{
    int ret, ch, i, n;

    if (skip_label(s, gb))
        return AVERROR_INVALIDDATA;

    s->fft_offset = s->frame_size - s->fft_offset;
    s->buffer_ptr = &s->buffer[s->nb_channels * s->buffer_offset];

    ret = read_noise_data(s, gb);
    if (ret < 0)
        return ret;

    ret = read_wave_data(s, gb);
    if (ret < 0)
        return ret;

    for (n = 0; n < 32; n++) {
        float *r;

        for (ch = 0; ch < s->nb_channels; ch++)
            add_noise(s, ch, n);

        add_waves(s, n);

        for (ch = 0; ch < s->nb_channels; ch++) {
            for (i = 0; i < s->subframe_size; i++) {
                s->cmplx[ch][i].re = s->fft_buffer[ch + 2][s->fft_offset + n * s->subframe_size + i];
                s->cmplx[ch][i].im = s->fft_buffer[ch + 0][s->fft_offset + n * s->subframe_size + i];
                s->cmplx[ch][s->subframe_size + i].re = 0;
                s->cmplx[ch][s->subframe_size + i].im = 0;
            }
        }

        for (ch = 0; ch < s->nb_channels; ch++) {
            s->fft_ctx.fft_permute(&s->fft_ctx, s->cmplx[ch]);
            s->fft_ctx.fft_calc(&s->fft_ctx, s->cmplx[ch]);
        }

        r = &s->buffer_ptr[s->nb_channels * n * s->subframe_size];
        for (i = 0; i < 2 * s->subframe_size; i++) {
            for (ch = 0; ch < s->nb_channels; ch++) {
                *r++ += s->cmplx[ch][i].re;
            }
        }

        r = &s->buffer_ptr[n * s->subframe_size * s->nb_channels];
        for (i = 0; i < s->nb_channels * s->subframe_size; i++) {
            out[i] = av_clipf(r[i], INT16_MIN, INT16_MAX);
        }
        out += s->subframe_size * s->nb_channels;

        for (ch = 0; ch < s->nb_channels; ch++) {
            memset(s->fft_buffer[ch+0] + s->fft_offset + n * s->subframe_size, 0, 4 * s->subframe_size);
            memset(s->fft_buffer[ch+2] + s->fft_offset + n * s->subframe_size, 0, 4 * s->subframe_size);
        }
        memset(s->buffer + s->nb_channels * (n * s->subframe_size + s->frame_size + s->buffer_offset), 0, 4 * s->subframe_size * s->nb_channels);
    }

    s->buffer_offset += s->frame_size;
    if (s->buffer_offset >= 32768 - s->frame_size) {
        memcpy(s->buffer, &s->buffer[s->nb_channels * s->buffer_offset], 4 * s->frame_size * s->nb_channels);
        s->buffer_offset = 0;
    }

    return 0;
}