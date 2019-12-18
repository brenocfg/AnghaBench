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
struct representation {int n_fragments; int first_seq_no; int n_timelines; int fragment_timescale; int fragment_duration; TYPE_1__** timelines; } ;
typedef  int int64_t ;
struct TYPE_5__ {int period_duration; int availability_start_time; int media_presentation_duration; scalar_t__ is_live; } ;
struct TYPE_4__ {int repeat; int duration; } ;
typedef  TYPE_2__ DASHContext ;

/* Variables and functions */
 int get_current_time_in_sec () ; 

__attribute__((used)) static int64_t calc_max_seg_no(struct representation *pls, DASHContext *c)
{
    int64_t num = 0;

    if (pls->n_fragments) {
        num = pls->first_seq_no + pls->n_fragments - 1;
    } else if (pls->n_timelines) {
        int i = 0;
        num = pls->first_seq_no + pls->n_timelines - 1;
        for (i = 0; i < pls->n_timelines; i++) {
            if (pls->timelines[i]->repeat == -1) {
                int length_of_each_segment = pls->timelines[i]->duration / pls->fragment_timescale;
                num =  c->period_duration / length_of_each_segment;
            } else {
                num += pls->timelines[i]->repeat;
            }
        }
    } else if (c->is_live && pls->fragment_duration) {
        num = pls->first_seq_no + (((get_current_time_in_sec() - c->availability_start_time)) * pls->fragment_timescale)  / pls->fragment_duration;
    } else if (pls->fragment_duration) {
        num = pls->first_seq_no + (c->media_presentation_duration * pls->fragment_timescale) / pls->fragment_duration;
    }

    return num;
}