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
struct TYPE_10__ {int h; int w; int ir_channel; int channels; scalar_t__ format; TYPE_1__* iir; } ;
struct TYPE_9__ {double** ab; int* nb_ab; float g; } ;
typedef  TYPE_2__ AudioIIRContext ;
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
 double const cos (double) ; 
 int /*<<< orphan*/  draw_line (TYPE_3__*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drawtext (TYPE_3__*,int,int,char*,int) ; 
 float fmaxf (float,float) ; 
 float fminf (float,float) ; 
 float hypot (double,double) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double const sin (double) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 

__attribute__((used)) static void draw_response(AVFilterContext *ctx, AVFrame *out)
{
    AudioIIRContext *s = ctx->priv;
    float *mag, *phase, min = FLT_MAX, max = FLT_MIN;
    int prev_ymag = -1, prev_yphase = -1;
    char text[32];
    int ch, i, x;

    memset(out->data[0], 0, s->h * out->linesize[0]);

    phase = av_malloc_array(s->w, sizeof(*phase));
    mag = av_malloc_array(s->w, sizeof(*mag));
    if (!mag || !phase)
        goto end;

    ch = av_clip(s->ir_channel, 0, s->channels - 1);
    for (i = 0; i < s->w; i++) {
        const double *b = s->iir[ch].ab[0];
        const double *a = s->iir[ch].ab[1];
        double w = i * M_PI / (s->w - 1);
        double realz, realp;
        double imagz, imagp;
        double real, imag, div;

        if (s->format == 0) {
            realz = 0., realp = 0.;
            imagz = 0., imagp = 0.;
            for (x = 0; x < s->iir[ch].nb_ab[1]; x++) {
                realz += cos(-x * w) * a[x];
                imagz += sin(-x * w) * a[x];
            }

            for (x = 0; x < s->iir[ch].nb_ab[0]; x++) {
                realp += cos(-x * w) * b[x];
                imagp += sin(-x * w) * b[x];
            }

            div = realp * realp + imagp * imagp;
            real = (realz * realp + imagz * imagp) / div;
            imag = (imagz * realp - imagp * realz) / div;
        } else {
            real = 1;
            imag = 0;
            for (x = 0; x < s->iir[ch].nb_ab[1]; x++) {
                double ore, oim, re, im;

                re = cos(w) - a[2 * x];
                im = sin(w) - a[2 * x + 1];

                ore = real;
                oim = imag;

                real = ore * re - oim * im;
                imag = ore * im + oim * re;
            }

            for (x = 0; x < s->iir[ch].nb_ab[0]; x++) {
                double ore, oim, re, im;

                re = cos(w) - b[2 * x];
                im = sin(w) - b[2 * x + 1];

                ore = real;
                oim = imag;
                div = re * re + im * im;

                real = (ore * re + oim * im) / div;
                imag = (oim * re - ore * im) / div;
            }
        }

        mag[i] = s->iir[ch].g * hypot(real, imag);
        phase[i] = atan2(imag, real);
        min = fminf(min, mag[i]);
        max = fmaxf(max, mag[i]);
    }

    for (i = 0; i < s->w; i++) {
        int ymag = mag[i] / max * (s->h - 1);
        int yphase = (0.5 * (1. + phase[i] / M_PI)) * (s->h - 1);

        ymag = s->h - 1 - av_clip(ymag, 0, s->h - 1);
        yphase = s->h - 1 - av_clip(yphase, 0, s->h - 1);

        if (prev_ymag < 0)
            prev_ymag = ymag;
        if (prev_yphase < 0)
            prev_yphase = yphase;

        draw_line(out, i,   ymag, FFMAX(i - 1, 0),   prev_ymag, 0xFFFF00FF);
        draw_line(out, i, yphase, FFMAX(i - 1, 0), prev_yphase, 0xFF00FF00);

        prev_ymag   = ymag;
        prev_yphase = yphase;
    }

    if (s->w > 400 && s->h > 100) {
        drawtext(out, 2, 2, "Max Magnitude:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", max);
        drawtext(out, 15 * 8 + 2, 2, text, 0xDDDDDDDD);

        drawtext(out, 2, 12, "Min Magnitude:", 0xDDDDDDDD);
        snprintf(text, sizeof(text), "%.2f", min);
        drawtext(out, 15 * 8 + 2, 12, text, 0xDDDDDDDD);
    }

end:
    av_free(phase);
    av_free(mag);
}