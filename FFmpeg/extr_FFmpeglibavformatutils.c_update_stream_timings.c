#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {scalar_t__ den; } ;
struct TYPE_15__ {int nb_streams; int nb_programs; scalar_t__ duration; double bit_rate; scalar_t__ pb; TYPE_3__** programs; scalar_t__ start_time; TYPE_2__** streams; } ;
struct TYPE_14__ {scalar_t__ start_time; scalar_t__ end_time; } ;
struct TYPE_13__ {scalar_t__ start_time; scalar_t__ duration; TYPE_6__ time_base; TYPE_1__* codecpar; } ;
struct TYPE_12__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVProgram ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_DATA ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_ROUND_NEAR_INF ; 
 int AV_ROUND_PASS_MINMAX ; 
 scalar_t__ AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 scalar_t__ FFMIN (scalar_t__,scalar_t__) ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 TYPE_3__* av_find_program_from_stream (TYPE_4__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ av_rescale_q (scalar_t__,TYPE_6__,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q_rnd (scalar_t__,TYPE_6__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_size (scalar_t__) ; 

__attribute__((used)) static void update_stream_timings(AVFormatContext *ic)
{
    int64_t start_time, start_time1, start_time_text, end_time, end_time1, end_time_text;
    int64_t duration, duration1, duration_text, filesize;
    int i;
    AVProgram *p;

    start_time = INT64_MAX;
    start_time_text = INT64_MAX;
    end_time   = INT64_MIN;
    end_time_text   = INT64_MIN;
    duration   = INT64_MIN;
    duration_text = INT64_MIN;

    for (i = 0; i < ic->nb_streams; i++) {
        AVStream *st = ic->streams[i];
        int is_text = st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE ||
                      st->codecpar->codec_type == AVMEDIA_TYPE_DATA;
        if (st->start_time != AV_NOPTS_VALUE && st->time_base.den) {
            start_time1 = av_rescale_q(st->start_time, st->time_base,
                                       AV_TIME_BASE_Q);
            if (is_text)
                start_time_text = FFMIN(start_time_text, start_time1);
            else
                start_time = FFMIN(start_time, start_time1);
            end_time1 = av_rescale_q_rnd(st->duration, st->time_base,
                                         AV_TIME_BASE_Q,
                                         AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
            if (end_time1 != AV_NOPTS_VALUE && (end_time1 > 0 ? start_time1 <= INT64_MAX - end_time1 : start_time1 >= INT64_MIN - end_time1)) {
                end_time1 += start_time1;
                if (is_text)
                    end_time_text = FFMAX(end_time_text, end_time1);
                else
                    end_time = FFMAX(end_time, end_time1);
            }
            for (p = NULL; (p = av_find_program_from_stream(ic, p, i)); ) {
                if (p->start_time == AV_NOPTS_VALUE || p->start_time > start_time1)
                    p->start_time = start_time1;
                if (p->end_time < end_time1)
                    p->end_time = end_time1;
            }
        }
        if (st->duration != AV_NOPTS_VALUE) {
            duration1 = av_rescale_q(st->duration, st->time_base,
                                     AV_TIME_BASE_Q);
            if (is_text)
                duration_text = FFMAX(duration_text, duration1);
            else
                duration = FFMAX(duration, duration1);
        }
    }
    if (start_time == INT64_MAX || (start_time > start_time_text && start_time - (uint64_t)start_time_text < AV_TIME_BASE))
        start_time = start_time_text;
    else if (start_time > start_time_text)
        av_log(ic, AV_LOG_VERBOSE, "Ignoring outlier non primary stream starttime %f\n", start_time_text / (float)AV_TIME_BASE);

    if (end_time == INT64_MIN || (end_time < end_time_text && end_time_text - (uint64_t)end_time < AV_TIME_BASE))
        end_time = end_time_text;
    else if (end_time < end_time_text)
        av_log(ic, AV_LOG_VERBOSE, "Ignoring outlier non primary stream endtime %f\n", end_time_text / (float)AV_TIME_BASE);

     if (duration == INT64_MIN || (duration < duration_text && duration_text - duration < AV_TIME_BASE))
         duration = duration_text;
     else if (duration < duration_text)
         av_log(ic, AV_LOG_VERBOSE, "Ignoring outlier non primary stream duration %f\n", duration_text / (float)AV_TIME_BASE);

    if (start_time != INT64_MAX) {
        ic->start_time = start_time;
        if (end_time != INT64_MIN) {
            if (ic->nb_programs > 1) {
                for (i = 0; i < ic->nb_programs; i++) {
                    p = ic->programs[i];
                    if (p->start_time != AV_NOPTS_VALUE &&
                        p->end_time > p->start_time &&
                        p->end_time - (uint64_t)p->start_time <= INT64_MAX)
                        duration = FFMAX(duration, p->end_time - p->start_time);
                }
            } else if (end_time >= start_time && end_time - (uint64_t)start_time <= INT64_MAX) {
                duration = FFMAX(duration, end_time - start_time);
            }
        }
    }
    if (duration != INT64_MIN && duration > 0 && ic->duration == AV_NOPTS_VALUE) {
        ic->duration = duration;
    }
    if (ic->pb && (filesize = avio_size(ic->pb)) > 0 && ic->duration > 0) {
        /* compute the bitrate */
        double bitrate = (double) filesize * 8.0 * AV_TIME_BASE /
                         (double) ic->duration;
        if (bitrate >= 0 && bitrate <= INT64_MAX)
            ic->bit_rate = bitrate;
    }
}