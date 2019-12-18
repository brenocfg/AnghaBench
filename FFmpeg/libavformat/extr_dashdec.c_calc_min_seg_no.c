#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct representation {int fragment_duration; int fragment_timescale; scalar_t__ first_seq_no; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int availability_start_time; int time_shift_buffer_depth; scalar_t__ is_live; } ;
typedef  TYPE_1__ DASHContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int get_current_time_in_sec () ; 

__attribute__((used)) static int64_t calc_min_seg_no(AVFormatContext *s, struct representation *pls)
{
    DASHContext *c = s->priv_data;
    int64_t num = 0;

    if (c->is_live && pls->fragment_duration) {
        av_log(s, AV_LOG_TRACE, "in live mode\n");
        num = pls->first_seq_no + (((get_current_time_in_sec() - c->availability_start_time) - c->time_shift_buffer_depth) * pls->fragment_timescale) / pls->fragment_duration;
    } else {
        num = pls->first_seq_no;
    }
    return num;
}