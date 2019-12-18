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
struct TYPE_14__ {int /*<<< orphan*/ ** outputs; TYPE_3__* priv; } ;
struct TYPE_13__ {int pts; scalar_t__* extended_data; } ;
struct TYPE_12__ {float factor; int channels; int start; int end; int win_size; int pts; TYPE_2__* buffer; int /*<<< orphan*/  phase; int /*<<< orphan*/  magnitude; scalar_t__ hop_size; TYPE_1__** fft_data; } ;
struct TYPE_11__ {scalar_t__* extended_data; } ;
struct TYPE_10__ {float re; } ;
typedef  TYPE_3__ SpectrumSynthContext ;
typedef  TYPE_4__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* ff_get_audio_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (float*,float*,int) ; 
 int /*<<< orphan*/  synth_window (TYPE_5__*,int) ; 

__attribute__((used)) static int try_push_frame(AVFilterContext *ctx, int x)
{
    SpectrumSynthContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    const float factor = s->factor;
    int ch, n, i, ret;
    int start, end;
    AVFrame *out;

    synth_window(ctx, x);

    for (ch = 0; ch < s->channels; ch++) {
        float *buf = (float *)s->buffer->extended_data[ch];
        int j, k;

        start = s->start;
        end = s->end;
        k = end;
        for (i = 0, j = start; j < k && i < s->win_size; i++, j++) {
            buf[j] += s->fft_data[ch][i].re;
        }

        for (; i < s->win_size; i++, j++) {
            buf[j] = s->fft_data[ch][i].re;
        }

        start += s->hop_size;
        end = j;

        if (start >= s->win_size) {
            start -= s->win_size;
            end -= s->win_size;

            if (ch == s->channels - 1) {
                float *dst;
                int c;

                out = ff_get_audio_buffer(outlink, s->win_size);
                if (!out) {
                    av_frame_free(&s->magnitude);
                    av_frame_free(&s->phase);
                    return AVERROR(ENOMEM);
                }

                out->pts = s->pts;
                s->pts += s->win_size;
                for (c = 0; c < s->channels; c++) {
                    dst = (float *)out->extended_data[c];
                    buf = (float *)s->buffer->extended_data[c];

                    for (n = 0; n < s->win_size; n++) {
                        dst[n] = buf[n] * factor;
                    }
                    memmove(buf, buf + s->win_size, s->win_size * 4);
                }

                ret = ff_filter_frame(outlink, out);
                if (ret < 0)
                    return ret;
            }
        }
    }

    s->start = start;
    s->end = end;

    return 0;
}