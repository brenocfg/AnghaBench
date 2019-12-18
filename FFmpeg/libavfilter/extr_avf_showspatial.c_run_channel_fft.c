#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float re; scalar_t__ im; } ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_7__ {float* window_func_lut; TYPE_5__** fft_data; int /*<<< orphan*/ * fft; } ;
typedef  TYPE_1__ ShowSpatialContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int run_channel_fft(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ShowSpatialContext *s = ctx->priv;
    const float *window_func_lut = s->window_func_lut;
    AVFrame *fin = arg;
    const int ch = jobnr;
    const float *p = (float *)fin->extended_data[ch];

    for (int n = 0; n < fin->nb_samples; n++) {
        s->fft_data[ch][n].re = p[n] * window_func_lut[n];
        s->fft_data[ch][n].im = 0;
    }

    av_fft_permute(s->fft[ch], s->fft_data[ch]);
    av_fft_calc(s->fft[ch], s->fft_data[ch]);

    return 0;
}