#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int win_scale; scalar_t__ scale; scalar_t__ orientation; int h; int w; double const gain; float** magnitudes; } ;
typedef  TYPE_1__ ShowSpectrumContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ LOG ; 
 float const MAGNITUDE (int,int const) ; 
 scalar_t__ VERTICAL ; 

__attribute__((used)) static int calc_channel_magnitudes(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ShowSpectrumContext *s = ctx->priv;
    const double w = s->win_scale * (s->scale == LOG ? s->win_scale : 1);
    int y, h = s->orientation == VERTICAL ? s->h : s->w;
    const float f = s->gain * w;
    const int ch = jobnr;
    float *magnitudes = s->magnitudes[ch];

    for (y = 0; y < h; y++)
        magnitudes[y] = MAGNITUDE(y, ch) * f;

    return 0;
}