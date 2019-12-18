#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {double* frame_metric; int out_last_stop; int frame_duration; scalar_t__ frame_analysis_duration; int /*<<< orphan*/  frame_rate_list; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_6__ {scalar_t__ stop; scalar_t__ start; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_drop_frame(hb_filter_private_t * pv, int count)
{
    int           ii, min;
    double      * metrics = pv->frame_metric;
    hb_buffer_t * buf, * first;
    double        cfr_stop;

    // compute where the second to last frame in the frame_rate_list would
    // stop if the frame rate were constant.
    //
    // this is our target stopping time for CFR and earliest possible
    // stopping time for PFR.
    cfr_stop = pv->out_last_stop + pv->frame_duration * (count - 1);

    // If the last frame's stop timestamp is before the calculated
    // CFR stop time of the second to last frame, then we need to drop a frame.
    buf   = hb_list_item(pv->frame_rate_list, count - 1);

    // Shortcut exit when entire list is CFR OK
    if (buf->s.stop >= (int64_t)cfr_stop)
    {
        return -1;
    }

    first = hb_list_item(pv->frame_rate_list, 0);
    min = 0;
    for (ii = 1; ii < count; ii++)
    {
        hb_buffer_t * buf = hb_list_item(pv->frame_rate_list, ii);
        // Don't check buffers outside analysis window
        if (buf->s.stop - first->s.start > pv->frame_analysis_duration)
        {
            break;
        }
        if (min < 0 || metrics[ii] < metrics[min])
        {
            min = ii;
        }
    }

    cfr_stop = pv->out_last_stop + pv->frame_duration * (ii - 1);
    buf      = hb_list_item(pv->frame_rate_list, ii - 1);

    // Don't drop buffers if frames fit in CRF time bounds
    if (buf->s.stop >= (int64_t)cfr_stop)
    {
        return -1;
    }

    return min;
}