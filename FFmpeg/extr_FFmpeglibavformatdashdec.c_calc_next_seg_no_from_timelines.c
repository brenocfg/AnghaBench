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
struct TYPE_2__ {scalar_t__ starttime; size_t duration; size_t repeat; } ;

/* Variables and functions */

__attribute__((used)) static int64_t calc_next_seg_no_from_timelines(struct representation *pls, int64_t cur_time)
{
    int64_t i = 0;
    int64_t j = 0;
    int64_t num = 0;
    int64_t start_time = 0;

    for (i = 0; i < pls->n_timelines; i++) {
        if (pls->timelines[i]->starttime > 0) {
            start_time = pls->timelines[i]->starttime;
        }
        if (start_time > cur_time)
            goto finish;

        start_time += pls->timelines[i]->duration;
        for (j = 0; j < pls->timelines[i]->repeat; j++) {
            num++;
            if (start_time > cur_time)
                goto finish;
            start_time += pls->timelines[i]->duration;
        }
        num++;
    }

    return -1;

finish:
    return num;
}