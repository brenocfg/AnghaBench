#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int plane; int n; int /*<<< orphan*/ * hdata; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** fft; } ;
typedef  int /*<<< orphan*/  FFTComplex ;
typedef  TYPE_2__ ConvolveContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fft_permute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fft_horizontal(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ConvolveContext *s = ctx->priv;
    ThreadData *td = arg;
    FFTComplex *hdata = td->hdata;
    const int plane = td->plane;
    const int n = td->n;
    int start = (n * jobnr) / nb_jobs;
    int end = (n * (jobnr+1)) / nb_jobs;
    int y;

    for (y = start; y < end; y++) {
        av_fft_permute(s->fft[plane][jobnr], hdata + y * n);
        av_fft_calc(s->fft[plane][jobnr], hdata + y * n);
    }

    return 0;
}