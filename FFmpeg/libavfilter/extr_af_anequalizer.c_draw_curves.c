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
typedef  int uint8_t ;
struct TYPE_16__ {TYPE_3__* priv; } ;
struct TYPE_15__ {int channels; } ;
struct TYPE_14__ {int* linesize; scalar_t__* data; } ;
struct TYPE_13__ {int h; double w; int nb_filters; int mag; TYPE_1__* filters; scalar_t__ fscale; int /*<<< orphan*/  colors; } ;
struct TYPE_12__ {int b4; double b2; double b1; double b3; int b0; int a4; double a2; double a1; double a3; int a0; } ;
struct TYPE_11__ {int channel; TYPE_2__* section; scalar_t__ ignore; } ;
typedef  TYPE_2__ FoSection ;
typedef  TYPE_3__ AudioNEqualizerContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL32 (int*) ; 
 int /*<<< orphan*/  AV_WL32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int FILTER_ORDER ; 
 double M_PI ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_parse_color (int*,char*,int,TYPE_6__*) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 char* av_strtok (char*,char*,char**) ; 
 double cos (double) ; 
 double hypot (double,double) ; 
 int log10 (double) ; 
 int lrint (double) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 double pow (int,double) ; 
 double sin (double) ; 

__attribute__((used)) static void draw_curves(AVFilterContext *ctx, AVFilterLink *inlink, AVFrame *out)
{
    AudioNEqualizerContext *s = ctx->priv;
    char *colors, *color, *saveptr = NULL;
    int ch, i, n;

    colors = av_strdup(s->colors);
    if (!colors)
        return;

    memset(out->data[0], 0, s->h * out->linesize[0]);

    for (ch = 0; ch < inlink->channels; ch++) {
        uint8_t fg[4] = { 0xff, 0xff, 0xff, 0xff };
        int prev_v = -1;
        double f;

        color = av_strtok(ch == 0 ? colors : NULL, " |", &saveptr);
        if (color)
            av_parse_color(fg, color, -1, ctx);

        for (f = 0; f < s->w; f++) {
            double zr, zi, zr2, zi2;
            double Hr, Hi;
            double Hmag = 1;
            double w;
            int v, y, x;

            w = M_PI * (s->fscale ? pow(s->w - 1, f / s->w) : f) / (s->w - 1);
            zr = cos(w);
            zr2 = zr * zr;
            zi = -sin(w);
            zi2 = zi * zi;

            for (n = 0; n < s->nb_filters; n++) {
                if (s->filters[n].channel != ch ||
                    s->filters[n].ignore)
                    continue;

                for (i = 0; i < FILTER_ORDER / 2; i++) {
                    FoSection *S = &s->filters[n].section[i];

                    /* H *= (((((S->b4 * z + S->b3) * z + S->b2) * z + S->b1) * z + S->b0) /
                          ((((S->a4 * z + S->a3) * z + S->a2) * z + S->a1) * z + S->a0)); */

                    Hr = S->b4*(1-8*zr2*zi2) + S->b2*(zr2-zi2) + zr*(S->b1+S->b3*(zr2-3*zi2))+ S->b0;
                    Hi = zi*(S->b3*(3*zr2-zi2) + S->b1 + 2*zr*(2*S->b4*(zr2-zi2) + S->b2));
                    Hmag *= hypot(Hr, Hi);
                    Hr = S->a4*(1-8*zr2*zi2) + S->a2*(zr2-zi2) + zr*(S->a1+S->a3*(zr2-3*zi2))+ S->a0;
                    Hi = zi*(S->a3*(3*zr2-zi2) + S->a1 + 2*zr*(2*S->a4*(zr2-zi2) + S->a2));
                    Hmag /= hypot(Hr, Hi);
                }
            }

            v = av_clip((1. + -20 * log10(Hmag) / s->mag) * s->h / 2, 0, s->h - 1);
            x = lrint(f);
            if (prev_v == -1)
                prev_v = v;
            if (v <= prev_v) {
                for (y = v; y <= prev_v; y++)
                    AV_WL32(out->data[0] + y * out->linesize[0] + x * 4, AV_RL32(fg));
            } else {
                for (y = prev_v; y <= v; y++)
                    AV_WL32(out->data[0] + y * out->linesize[0] + x * 4, AV_RL32(fg));
            }

            prev_v = v;
        }
    }

    av_free(colors);
}