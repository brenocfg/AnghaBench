#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct video_data {scalar_t__ ts_mode; int /*<<< orphan*/  timefilter; } ;
typedef  int int64_t ;
struct TYPE_11__ {scalar_t__ num; } ;
struct TYPE_10__ {TYPE_1__** streams; struct video_data* priv_data; } ;
struct TYPE_9__ {int member_0; int member_1; } ;
struct TYPE_8__ {TYPE_6__ avg_frame_rate; } ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ V4L_TS_ABS ; 
 void* V4L_TS_CONVERT_READY ; 
 scalar_t__ V4L_TS_MONO2ABS ; 
 int av_gettime () ; 
 int av_gettime_monotonic () ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_rescale_q (int,TYPE_2__,TYPE_6__) ; 
 int /*<<< orphan*/  ff_timefilter_new (int,int,double) ; 

__attribute__((used)) static int init_convert_timestamp(AVFormatContext *ctx, int64_t ts)
{
    struct video_data *s = ctx->priv_data;
    int64_t now;

    now = av_gettime();
    if (s->ts_mode == V4L_TS_ABS &&
        ts <= now + 1 * AV_TIME_BASE && ts >= now - 10 * AV_TIME_BASE) {
        av_log(ctx, AV_LOG_INFO, "Detected absolute timestamps\n");
        s->ts_mode = V4L_TS_CONVERT_READY;
        return 0;
    }
#if HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
    if (ctx->streams[0]->avg_frame_rate.num) {
        now = av_gettime_monotonic();
        if (s->ts_mode == V4L_TS_MONO2ABS ||
            (ts <= now + 1 * AV_TIME_BASE && ts >= now - 10 * AV_TIME_BASE)) {
            AVRational tb = {AV_TIME_BASE, 1};
            int64_t period = av_rescale_q(1, tb, ctx->streams[0]->avg_frame_rate);
            av_log(ctx, AV_LOG_INFO, "Detected monotonic timestamps, converting\n");
            /* microseconds instead of seconds, MHz instead of Hz */
            s->timefilter = ff_timefilter_new(1, period, 1.0E-6);
            if (!s->timefilter)
                return AVERROR(ENOMEM);
            s->ts_mode = V4L_TS_CONVERT_READY;
            return 0;
        }
    }
#endif
    av_log(ctx, AV_LOG_ERROR, "Unknown timestamps\n");
    return AVERROR(EIO);
}