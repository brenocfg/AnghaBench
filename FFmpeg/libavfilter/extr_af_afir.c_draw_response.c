#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int h; int w; int ir_channel; int nb_taps; TYPE_1__** in; } ;
struct TYPE_9__ {int channels; scalar_t__* extended_data; } ;
typedef  TYPE_2__ AudioFIRContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 float FLT_MAX ; 
 float FLT_MIN ; 
 int M_PI ; 
 float atan2 (double,double) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_free (float*) ; 
 float* av_malloc_array (int,int) ; 
 float const cos (int) ; 
 int /*<<< orphan*/  draw_line (TYPE_3__*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drawtext (TYPE_3__*,int,int,char*,int) ; 
 float fmaxf (float,float) ; 
 float fminf (float,float) ; 
 float hypot (double,double) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 float const sin (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 

__attribute__((used)) static void draw_response(AVFilterContext *ctx, AVFrame *out)
{
    AudioFIRContext *s = ctx->priv;
    float *mag, *phase, *delay, min = FLT_MAX, max = FLT_MIN;
    float min_delay = FLT_MAX, max_delay = FLT_MIN;
    int prev_ymag = -1, prev_yphase = -1, prev_ydelay = -1;
    char text[32];
    int channel, i, x;

    memset(out->data[0], 0, s->h * out->linesize[0]);

    phase = av_malloc_array(s->w, sizeof(*phase));
    mag = av_malloc_array(s->w, sizeof(*mag));
    delay = av_malloc_array(s->w, sizeof(*delay));
    if (!mag || !phase || !delay)
        goto end;

    channel = av_clip(s->ir_channel, 0, s->in[1]->channels - 1);
    for (i = 0; i < s->w; i++) {
        const float *src = (const float *)s->in[1]->extended_data[channel];
        double w = i * M_PI / (s->w - 1);
        double div, real_num = 0., imag_num = 0., real = 0., imag = 0.;

        for (x = 0; x < s->nb_taps; x++) {
            real += cos(-x * w) * src[x];
            imag += sin(-x * w) * src[x];
            real_num += cos(-x * w) * src[x] * x;
            imag_num += sin(-x * w) * src[x] * x;
        }

        mag[i] = hypot(real, imag);
        phase[i] = atan2(imag, real);
        div = real * real + imag * imag;
        delay[i] = (real_num * real + imag_num * imag) / div;
        min = fminf(min, mag[i]);
        max = fmaxf(max, mag[i]);
        min_delay = fminf(min_delay, delay[i]);
        max_delay = fmaxf(max_delay, delay[i]);
    }

    for (i = 0; i < s->w; i++) {
        int ymag = mag[i] / max * (s->h - 1);
        int ydelay = (delay[i] - min_delay) / (max_delay - min_delay) * (s->h - 1);
        int yphase = (0.5 * (1. + phase[i] / M_PI)) * (s->h - 1);

        ymag = s->h - 1 - av_clip(ymag, 0, s->h - 1);
        yphase = s->h - 1 - av_clip(yphase, 0, s->h - 1);
        ydelay = s->h - 1 - av_clip(ydelay, 0, s->h - 1);

        if (prev_ymag < 0)
            prev_ymag = ymag;
        if (prev_yphase < 0)
            prev_yphase = yphase;
        if (prev_ydelay < 0)
            prev_ydelay = ydelay;

        draw_line(out, i,   ymag, FFMAX(i - 1, 0),   prev_ymag, 0xFFFF00FF);
        draw_line(out, i, yphase, FFMAX(i - 1, 0), prev_yphase, 0xFF00FF00);
        draw_line(out, i, ydelay, FFMAX(i - 1, 0), prev_ydelay, 0xFF00FFFF);

        prev_ymag   = ymag;
        prev_yphase = yphase;
        prev_ydelay = ydelay;
    }

    if (s->w > 400 && s->h > 100) {
        drawtext(out, 2, 2, "Max Magnitude:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", max);
        drawtext(out, 15 * 8 + 2, 2, text, 0xDDDDDDDD);

        drawtext(out, 2, 12, "Min Magnitude:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", min);
        drawtext(out, 15 * 8 + 2, 12, text, 0xDDDDDDDD);

        drawtext(out, 2, 22, "Max Delay:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", max_delay);
        drawtext(out, 11 * 8 + 2, 22, text, 0xDDDDDDDD);

        drawtext(out, 2, 32, "Min Delay:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", min_delay);
        drawtext(out, 11 * 8 + 2, 32, text, 0xDDDDDDDD);
    }

end:
    av_free(delay);
    av_free(phase);
    av_free(mag);
}