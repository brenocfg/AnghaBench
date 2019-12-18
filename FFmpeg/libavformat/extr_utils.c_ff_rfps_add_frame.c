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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* info; int /*<<< orphan*/  time_base; } ;
struct TYPE_4__ {scalar_t__ last_dts; int*** duration_error; scalar_t__ rfps_duration_sum; int duration_count; int /*<<< orphan*/  duration_gcd; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INT64_MAX ; 
 int MAX_STD_TIMEBASES ; 
 scalar_t__ RELATIVE_TS_BASE ; 
 int /*<<< orphan*/  av_gcd (int /*<<< orphan*/ ,scalar_t__) ; 
 int*** av_mallocz (int) ; 
 scalar_t__ av_q2d (int /*<<< orphan*/ ) ; 
 int get_std_framerate (int) ; 
 scalar_t__ is_relative (scalar_t__) ; 
 scalar_t__ llrint (double) ; 

int ff_rfps_add_frame(AVFormatContext *ic, AVStream *st, int64_t ts)
{
    int i, j;
    int64_t last = st->info->last_dts;

    if (   ts != AV_NOPTS_VALUE && last != AV_NOPTS_VALUE && ts > last
       && ts - (uint64_t)last < INT64_MAX) {
        double dts = (is_relative(ts) ?  ts - RELATIVE_TS_BASE : ts) * av_q2d(st->time_base);
        int64_t duration = ts - last;

        if (!st->info->duration_error)
            st->info->duration_error = av_mallocz(sizeof(st->info->duration_error[0])*2);
        if (!st->info->duration_error)
            return AVERROR(ENOMEM);

//         if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)
//             av_log(NULL, AV_LOG_ERROR, "%f\n", dts);
        for (i = 0; i<MAX_STD_TIMEBASES; i++) {
            if (st->info->duration_error[0][1][i] < 1e10) {
                int framerate = get_std_framerate(i);
                double sdts = dts*framerate/(1001*12);
                for (j= 0; j<2; j++) {
                    int64_t ticks = llrint(sdts+j*0.5);
                    double error= sdts - ticks + j*0.5;
                    st->info->duration_error[j][0][i] += error;
                    st->info->duration_error[j][1][i] += error*error;
                }
            }
        }
        if (st->info->rfps_duration_sum <= INT64_MAX - duration) {
            st->info->duration_count++;
            st->info->rfps_duration_sum += duration;
        }

        if (st->info->duration_count % 10 == 0) {
            int n = st->info->duration_count;
            for (i = 0; i<MAX_STD_TIMEBASES; i++) {
                if (st->info->duration_error[0][1][i] < 1e10) {
                    double a0     = st->info->duration_error[0][0][i] / n;
                    double error0 = st->info->duration_error[0][1][i] / n - a0*a0;
                    double a1     = st->info->duration_error[1][0][i] / n;
                    double error1 = st->info->duration_error[1][1][i] / n - a1*a1;
                    if (error0 > 0.04 && error1 > 0.04) {
                        st->info->duration_error[0][1][i] = 2e10;
                        st->info->duration_error[1][1][i] = 2e10;
                    }
                }
            }
        }

        // ignore the first 4 values, they might have some random jitter
        if (st->info->duration_count > 3 && is_relative(ts) == is_relative(last))
            st->info->duration_gcd = av_gcd(st->info->duration_gcd, duration);
    }
    if (ts != AV_NOPTS_VALUE)
        st->info->last_dts = ts;

    return 0;
}