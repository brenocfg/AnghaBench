#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_19__ {scalar_t__* last_start; scalar_t__* last_stop; int* lost_time; int total_lost_time; int /*<<< orphan*/  extended_frames; int /*<<< orphan*/  total_gained_time; int /*<<< orphan*/  delay_queue; int /*<<< orphan*/  drops; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_20__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;
struct TYPE_18__ {int flags; scalar_t__ start; scalar_t__ stop; } ;
struct TYPE_21__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 TYPE_4__* adjust_frame_rate (TYPE_2__*,TYPE_4__*) ; 
 TYPE_4__* flush_frames (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_4__**) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 TYPE_4__* hb_fifo_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_fifo_push (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int hb_fifo_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hb_vfr_work( hb_filter_object_t * filter,
                        hb_buffer_t ** buf_in,
                        hb_buffer_t ** buf_out )
{
    hb_filter_private_t * pv = filter->private_data;
    hb_buffer_t         * in = *buf_in;
    hb_buffer_t         * out = NULL;

    *buf_in = NULL;
    *buf_out = NULL;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        hb_buffer_list_t   list;
        hb_buffer_t      * next;
        int                counter = 2;

        // Flush the delay_queue and frame rate adjustment
        hb_buffer_list_clear(&list);
        while ((next = hb_fifo_get(pv->delay_queue)) != NULL)
        {

            /* We can't use the given time stamps. Previous frames
               might already have been extended, throwing off the
               raw values fed to render.c. Instead, their
               stop and start times are stored in arrays.
               The 4th cached frame will be the to use.
               If it needed its duration extended to make up
               lost time, it will have happened above. */
            next->s.start = pv->last_start[counter];
            next->s.stop  = pv->last_stop[counter--];

            hb_buffer_list_append(&list, adjust_frame_rate(pv, next));
        }
        hb_buffer_list_append(&list, flush_frames(pv));
        hb_buffer_list_append(&list, in);
        *buf_out = hb_buffer_list_clear(&list);
        return HB_FILTER_DONE;
    }

    // If there is a gap between the last stop and the current start
    // then frame(s) were dropped.
    if (hb_fifo_size(pv->delay_queue) > 0 && in->s.start > pv->last_stop[0])
    {
        /* We need to compensate for the time lost by dropping frame(s).
           Spread its duration out in quarters, because usually dropped frames
           maintain a 1-out-of-5 pattern and this spreads it out amongst
           the remaining ones.  Store these in the lost_time array, which
           has 4 slots in it.  Because not every frame duration divides
           evenly by 4, and we can't lose the remainder, we have to go
           through an awkward process to preserve it in the 4th array index.
        */
        int64_t temp_duration = in->s.start - pv->last_stop[0];
        pv->lost_time[0] += (temp_duration / 4);
        pv->lost_time[1] += (temp_duration / 4);
        pv->lost_time[2] += (temp_duration / 4);
        pv->lost_time[3] += ( temp_duration - 3 * (temp_duration / 4) );

        pv->total_lost_time += temp_duration;
    }
    else if ( in->s.stop <= pv->last_stop[0] )
    {
        // This is generally an error somewhere (bad source or hb bug).
        // But lets do our best to straighten out the mess.
        ++pv->drops;
        hb_buffer_close(&in);
        return HB_FILTER_OK;
    }

    /* Cache frame start and stop times, so we can renumber
       time stamps if dropping frames for VFR.              */
    int i;
    for( i = 3; i >= 1; i-- )
    {
        pv->last_start[i] = pv->last_start[i-1];
        pv->last_stop[i] = pv->last_stop[i-1];
    }

    /* In order to make sure we have continuous time stamps, store
       the current frame's duration as starting when the last one stopped. */
    if (hb_fifo_size(pv->delay_queue) == 0)
    {
        pv->last_start[0] = in->s.start;
        pv->last_stop[0]  = in->s.stop;
    }
    else
    {
        pv->last_start[0] = pv->last_stop[1];
        pv->last_stop[0] = pv->last_start[0] + (in->s.stop - in->s.start);
    }

    hb_fifo_push( pv->delay_queue, in );

    /*
     * Keep the last three frames in our queue, this ensures that we have
     * the last two always in there should we need to rewrite the
     * durations on them.
     */

    if (hb_fifo_size(pv->delay_queue) < 4)
    {
        *buf_out = NULL;
        return HB_FILTER_OK;
    }

    out = hb_fifo_get(pv->delay_queue);
    /* The current frame exists. That means it hasn't been dropped by a
     * filter. We may edit its duration if needed.
     */
    if( pv->lost_time[3] > 0 )
    {
        int time_shift = 0;

        for( i = 3; i >= 0; i-- )
        {
            /*
             * A frame's been dropped earlier by VFR detelecine.
             * Gotta make up the lost time. This will also
             * slow down the video.
             * The dropped frame's has to be accounted for, so
             * divvy it up amongst the 4 frames left behind.
             * This is what the delay_queue is for;
             * telecined sequences start 2 frames before
             * the dropped frame, so to slow down the right
             * ones you need a 2 frame delay between
             * reading input and writing output.
             */

            /* We want to extend the outputted frame's duration by the value
              stored in the 4th slot of the lost_time array. Because we need
              to adjust all the values in the array so they're contiguous,
              extend the duration inside the array first, before applying
              it to the current frame buffer. */
            pv->last_start[i] += time_shift;
            pv->last_stop[i] += pv->lost_time[i] + time_shift;

            /* Log how much time has been added back in to the video. */
            pv->total_gained_time += pv->lost_time[i];
            time_shift += pv->lost_time[i];

            pv->lost_time[i] = 0;

            /* Log how many frames have had their durations extended. */
            pv->extended_frames++;
        }
    }

    /* We can't use the given time stamps. Previous frames
       might already have been extended, throwing off the
       raw values fed to render.c. Instead, their
       stop and start times are stored in arrays.
       The 4th cached frame will be the to use.
       If it needed its duration extended to make up
       lost time, it will have happened above. */
    out->s.start = pv->last_start[3];
    out->s.stop = pv->last_stop[3];

    *buf_out = adjust_frame_rate(pv, out);

    return HB_FILTER_OK;
}