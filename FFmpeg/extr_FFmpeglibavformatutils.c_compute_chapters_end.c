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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  time_base; } ;
struct TYPE_4__ {scalar_t__ duration; scalar_t__ start_time; unsigned int nb_chapters; TYPE_2__** chapters; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVChapter ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compute_chapters_end(AVFormatContext *s)
{
    unsigned int i, j;
    int64_t max_time = 0;

    if (s->duration > 0 && s->start_time < INT64_MAX - s->duration)
        max_time = s->duration +
                       ((s->start_time == AV_NOPTS_VALUE) ? 0 : s->start_time);

    for (i = 0; i < s->nb_chapters; i++)
        if (s->chapters[i]->end == AV_NOPTS_VALUE) {
            AVChapter *ch = s->chapters[i];
            int64_t end = max_time ? av_rescale_q(max_time, AV_TIME_BASE_Q,
                                                  ch->time_base)
                                   : INT64_MAX;

            for (j = 0; j < s->nb_chapters; j++) {
                AVChapter *ch1     = s->chapters[j];
                int64_t next_start = av_rescale_q(ch1->start, ch1->time_base,
                                                  ch->time_base);
                if (j != i && next_start > ch->start && next_start < end)
                    end = next_start;
            }
            ch->end = (end == INT64_MAX || end < ch->start) ? ch->start : end;
        }
}