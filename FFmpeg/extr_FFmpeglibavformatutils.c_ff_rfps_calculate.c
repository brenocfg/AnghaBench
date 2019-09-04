#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int nb_streams; TYPE_4__** streams; } ;
struct TYPE_16__ {long long den; long long num; } ;
struct TYPE_15__ {TYPE_3__* info; TYPE_5__ r_frame_rate; TYPE_5__ avg_frame_rate; TYPE_5__ time_base; TYPE_2__* internal; TYPE_1__* codecpar; } ;
struct TYPE_14__ {int duration_count; int duration_gcd; int codec_info_duration; int rfps_duration_sum; int*** duration_error; int /*<<< orphan*/  last_dts; } ;
struct TYPE_13__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_12__ {scalar_t__ codec_type; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVRational ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int FFMAX (int,long long) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int MAX_STD_TIMEBASES ; 
 int /*<<< orphan*/  av_freep (int****) ; 
 TYPE_5__ av_inv_q (TYPE_5__) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 double av_q2d (TYPE_5__) ; 
 int /*<<< orphan*/  av_reduce (long long*,long long*,int,int,int /*<<< orphan*/ ) ; 
 double fabs (double) ; 
 double get_std_framerate (int) ; 
 scalar_t__ tb_unreliable (int /*<<< orphan*/ ) ; 

void ff_rfps_calculate(AVFormatContext *ic)
{
    int i, j;

    for (i = 0; i < ic->nb_streams; i++) {
        AVStream *st = ic->streams[i];

        if (st->codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
            continue;
        // the check for tb_unreliable() is not completely correct, since this is not about handling
        // an unreliable/inexact time base, but a time base that is finer than necessary, as e.g.
        // ipmovie.c produces.
        if (tb_unreliable(st->internal->avctx) && st->info->duration_count > 15 && st->info->duration_gcd > FFMAX(1, st->time_base.den/(500LL*st->time_base.num)) && !st->r_frame_rate.num)
            av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, st->time_base.den, st->time_base.num * st->info->duration_gcd, INT_MAX);
        if (st->info->duration_count>1 && !st->r_frame_rate.num
            && tb_unreliable(st->internal->avctx)) {
            int num = 0;
            double best_error= 0.01;
            AVRational ref_rate = st->r_frame_rate.num ? st->r_frame_rate : av_inv_q(st->time_base);

            for (j= 0; j<MAX_STD_TIMEBASES; j++) {
                int k;

                if (st->info->codec_info_duration &&
                    st->info->codec_info_duration*av_q2d(st->time_base) < (1001*11.5)/get_std_framerate(j))
                    continue;
                if (!st->info->codec_info_duration && get_std_framerate(j) < 1001*12)
                    continue;

                if (av_q2d(st->time_base) * st->info->rfps_duration_sum / st->info->duration_count < (1001*12.0 * 0.8)/get_std_framerate(j))
                    continue;

                for (k= 0; k<2; k++) {
                    int n = st->info->duration_count;
                    double a= st->info->duration_error[k][0][j] / n;
                    double error= st->info->duration_error[k][1][j]/n - a*a;

                    if (error < best_error && best_error> 0.000000001) {
                        best_error= error;
                        num = get_std_framerate(j);
                    }
                    if (error < 0.02)
                        av_log(ic, AV_LOG_DEBUG, "rfps: %f %f\n", get_std_framerate(j) / 12.0/1001, error);
                }
            }
            // do not increase frame rate by more than 1 % in order to match a standard rate.
            if (num && (!ref_rate.num || (double)num/(12*1001) < 1.01 * av_q2d(ref_rate)))
                av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, num, 12*1001, INT_MAX);
        }
        if (   !st->avg_frame_rate.num
            && st->r_frame_rate.num && st->info->rfps_duration_sum
            && st->info->codec_info_duration <= 0
            && st->info->duration_count > 2
            && fabs(1.0 / (av_q2d(st->r_frame_rate) * av_q2d(st->time_base)) - st->info->rfps_duration_sum / (double)st->info->duration_count) <= 1.0
            ) {
            av_log(ic, AV_LOG_DEBUG, "Setting avg frame rate based on r frame rate\n");
            st->avg_frame_rate = st->r_frame_rate;
        }

        av_freep(&st->info->duration_error);
        st->info->last_dts = AV_NOPTS_VALUE;
        st->info->duration_count = 0;
        st->info->rfps_duration_sum = 0;
    }
}