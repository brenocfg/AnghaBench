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
struct TYPE_3__ {int channels; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  fir_channel (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int fir_channels(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AVFrame *out = arg;
    const int start = (out->channels * jobnr) / nb_jobs;
    const int end = (out->channels * (jobnr+1)) / nb_jobs;

    for (int ch = start; ch < end; ch++) {
        fir_channel(ctx, out, ch);
    }

    return 0;
}