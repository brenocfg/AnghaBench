#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int win_scale; scalar_t__ scale; scalar_t__ orientation; int h; int w; double const gain; int nb_display_channels; float** magnitudes; } ;
typedef  TYPE_1__ ShowSpectrumContext ;

/* Variables and functions */
 scalar_t__ LOG ; 
 float const MAGNITUDE (int,int) ; 
 scalar_t__ VERTICAL ; 

__attribute__((used)) static void acalc_magnitudes(ShowSpectrumContext *s)
{
    const double w = s->win_scale * (s->scale == LOG ? s->win_scale : 1);
    int ch, y, h = s->orientation == VERTICAL ? s->h : s->w;
    const float f = s->gain * w;

    for (ch = 0; ch < s->nb_display_channels; ch++) {
        float *magnitudes = s->magnitudes[ch];

        for (y = 0; y < h; y++)
            magnitudes[y] += MAGNITUDE(y, ch) * f;
    }
}