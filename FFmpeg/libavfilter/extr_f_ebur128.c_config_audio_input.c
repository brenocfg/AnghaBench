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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int min_samples; int max_samples; int partial_buf_size; int sample_rate; TYPE_3__* dst; } ;
struct TYPE_5__ {int peak_mode; scalar_t__ metadata; } ;
typedef  TYPE_1__ EBUR128Context ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int PEAK_MODE_TRUE_PEAKS ; 

__attribute__((used)) static int config_audio_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    EBUR128Context *ebur128 = ctx->priv;

    /* Force 100ms framing in case of metadata injection: the frames must have
     * a granularity of the window overlap to be accurately exploited.
     * As for the true peaks mode, it just simplifies the resampling buffer
     * allocation and the lookup in it (since sample buffers differ in size, it
     * can be more complex to integrate in the one-sample loop of
     * filter_frame()). */
    if (ebur128->metadata || (ebur128->peak_mode & PEAK_MODE_TRUE_PEAKS))
        inlink->min_samples =
        inlink->max_samples =
        inlink->partial_buf_size = inlink->sample_rate / 10;
    return 0;
}