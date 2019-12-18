#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_data {scalar_t__ timefilter; scalar_t__ last_time_m; scalar_t__ ts_mode; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {struct video_data* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ av_gettime () ; 
 scalar_t__ av_gettime_monotonic () ; 
 scalar_t__ ff_timefilter_eval (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ff_timefilter_update (scalar_t__,scalar_t__,scalar_t__) ; 
 int init_convert_timestamp (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int convert_timestamp(AVFormatContext *ctx, int64_t *ts)
{
    struct video_data *s = ctx->priv_data;

    if (s->ts_mode) {
        int r = init_convert_timestamp(ctx, *ts);
        if (r < 0)
            return r;
    }
#if HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
    if (s->timefilter) {
        int64_t nowa = av_gettime();
        int64_t nowm = av_gettime_monotonic();
        ff_timefilter_update(s->timefilter, nowa, nowm - s->last_time_m);
        s->last_time_m = nowm;
        *ts = ff_timefilter_eval(s->timefilter, *ts - nowm);
    }
#endif
    return 0;
}