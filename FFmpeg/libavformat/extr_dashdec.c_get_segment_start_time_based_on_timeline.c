#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct representation {size_t n_timelines; TYPE_1__** timelines; } ;
typedef  size_t int64_t ;
struct TYPE_2__ {scalar_t__ starttime; size_t duration; int repeat; } ;

/* Variables and functions */

__attribute__((used)) static int64_t get_segment_start_time_based_on_timeline(struct representation *pls, int64_t cur_seq_no)
{
    int64_t start_time = 0;
    int64_t i = 0;
    int64_t j = 0;
    int64_t num = 0;

    if (pls->n_timelines) {
        for (i = 0; i < pls->n_timelines; i++) {
            if (pls->timelines[i]->starttime > 0) {
                start_time = pls->timelines[i]->starttime;
            }
            if (num == cur_seq_no)
                goto finish;

            start_time += pls->timelines[i]->duration;

            if (pls->timelines[i]->repeat == -1) {
                start_time = pls->timelines[i]->duration * cur_seq_no;
                goto finish;
            }

            for (j = 0; j < pls->timelines[i]->repeat; j++) {
                num++;
                if (num == cur_seq_no)
                    goto finish;
                start_time += pls->timelines[i]->duration;
            }
            num++;
        }
    }
finish:
    return start_time;
}