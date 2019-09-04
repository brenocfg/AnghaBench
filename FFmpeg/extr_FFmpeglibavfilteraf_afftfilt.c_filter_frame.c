#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int window_size; int win_scale; int start; int end; double pts; float const* window_func_lut; int overlap; scalar_t__ hop_size; int /*<<< orphan*/  fifo; TYPE_1__* buffer; TYPE_2__** fft_temp; int /*<<< orphan*/  ifft; int /*<<< orphan*/ * imag; int /*<<< orphan*/ * real; TYPE_2__** fft_data; int /*<<< orphan*/  fft; } ;
struct TYPE_21__ {TYPE_6__* priv; TYPE_4__** outputs; } ;
struct TYPE_20__ {int channels; double sample_rate; TYPE_5__* dst; } ;
struct TYPE_19__ {double pts; int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_18__ {float re; double im; } ;
struct TYPE_17__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ FFTComplex ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;
typedef  TYPE_6__ AFFTFiltContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 double AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t VAR_BIN ; 
 size_t VAR_CHANNEL ; 
 size_t VAR_CHANNELS ; 
 size_t VAR_IMAG ; 
 size_t VAR_NBBINS ; 
 size_t VAR_PTS ; 
 size_t VAR_REAL ; 
 size_t VAR_SAMPLE_RATE ; 
 int VAR_VARS_NB ; 
 int /*<<< orphan*/  av_audio_fifo_drain (int /*<<< orphan*/ ,scalar_t__) ; 
 int av_audio_fifo_peek (int /*<<< orphan*/ ,void**,int const) ; 
 int const av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int av_audio_fifo_write (int /*<<< orphan*/ ,void**,int) ; 
 float av_expr_eval (int /*<<< orphan*/ ,double*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_audio_buffer (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  memmove (float*,float*,int const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AFFTFiltContext *s = ctx->priv;
    const int window_size = s->window_size;
    const float f = 1. / s->win_scale;
    double values[VAR_VARS_NB];
    AVFrame *out, *in = NULL;
    int ch, n, ret, i, j, k;
    int start = s->start, end = s->end;

    if (s->pts == AV_NOPTS_VALUE)
        s->pts = frame->pts;

    ret = av_audio_fifo_write(s->fifo, (void **)frame->extended_data, frame->nb_samples);
    av_frame_free(&frame);
    if (ret < 0)
        return ret;

    while (av_audio_fifo_size(s->fifo) >= window_size) {
        if (!in) {
            in = ff_get_audio_buffer(outlink, window_size);
            if (!in)
                return AVERROR(ENOMEM);
        }

        ret = av_audio_fifo_peek(s->fifo, (void **)in->extended_data, window_size);
        if (ret < 0)
            break;

        for (ch = 0; ch < inlink->channels; ch++) {
            const float *src = (float *)in->extended_data[ch];
            FFTComplex *fft_data = s->fft_data[ch];

            for (n = 0; n < in->nb_samples; n++) {
                fft_data[n].re = src[n] * s->window_func_lut[n];
                fft_data[n].im = 0;
            }

            for (; n < window_size; n++) {
                fft_data[n].re = 0;
                fft_data[n].im = 0;
            }
        }

        values[VAR_PTS]         = s->pts;
        values[VAR_SAMPLE_RATE] = inlink->sample_rate;
        values[VAR_NBBINS]      = window_size / 2;
        values[VAR_CHANNELS]    = inlink->channels;

        for (ch = 0; ch < inlink->channels; ch++) {
            FFTComplex *fft_data = s->fft_data[ch];

            av_fft_permute(s->fft, fft_data);
            av_fft_calc(s->fft, fft_data);
        }

        for (ch = 0; ch < inlink->channels; ch++) {
            FFTComplex *fft_data = s->fft_data[ch];
            FFTComplex *fft_temp = s->fft_temp[ch];
            float *buf = (float *)s->buffer->extended_data[ch];
            int x;
            values[VAR_CHANNEL] = ch;

            for (n = 0; n <= window_size / 2; n++) {
                float fr, fi;

                values[VAR_BIN] = n;
                values[VAR_REAL] = fft_data[n].re;
                values[VAR_IMAG] = fft_data[n].im;

                fr = av_expr_eval(s->real[ch], values, s);
                fi = av_expr_eval(s->imag[ch], values, s);

                fft_temp[n].re = fr;
                fft_temp[n].im = fi;
            }

            for (n = window_size / 2 + 1, x = window_size / 2 - 1; n < window_size; n++, x--) {
                fft_temp[n].re =  fft_temp[x].re;
                fft_temp[n].im = -fft_temp[x].im;
            }

            av_fft_permute(s->ifft, fft_temp);
            av_fft_calc(s->ifft, fft_temp);

            start = s->start;
            end = s->end;
            k = end;
            for (i = 0, j = start; j < k && i < window_size; i++, j++) {
                buf[j] += s->fft_temp[ch][i].re * f;
            }

            for (; i < window_size; i++, j++) {
                buf[j] = s->fft_temp[ch][i].re * f;
            }

            start += s->hop_size;
            end = j;
        }

        s->start = start;
        s->end = end;

        if (start >= window_size) {
            float *dst, *buf;

            start -= window_size;
            end   -= window_size;

            s->start = start;
            s->end = end;

            out = ff_get_audio_buffer(outlink, window_size);
            if (!out) {
                ret = AVERROR(ENOMEM);
                break;
            }

            out->pts = s->pts;
            s->pts += window_size;

            for (ch = 0; ch < inlink->channels; ch++) {
                dst = (float *)out->extended_data[ch];
                buf = (float *)s->buffer->extended_data[ch];

                for (n = 0; n < window_size; n++) {
                    dst[n] = buf[n] * (1 - s->overlap);
                }
                memmove(buf, buf + window_size, window_size * 4);
            }

            ret = ff_filter_frame(outlink, out);
            if (ret < 0)
                break;
        }

        av_audio_fifo_drain(s->fifo, s->hop_size);
    }

    av_frame_free(&in);
    return ret < 0 ? ret : 0;
}