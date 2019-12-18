#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int script_initialized; TYPE_5__* current_sub; int /*<<< orphan*/  ssaTrack; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_18__ {TYPE_1__* subtitle; TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_filter_object_t ;
struct TYPE_16__ {int flags; int start; long long stop; } ;
struct TYPE_19__ {TYPE_2__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_15__ {int /*<<< orphan*/  fifo_out; int /*<<< orphan*/  extradata_size; scalar_t__ extradata; } ;

/* Variables and functions */
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ApplySSASubs (TYPE_3__*,TYPE_5__*) ; 
 int HB_BUF_FLAG_EOF ; 
 int HB_BUF_FLAG_EOS ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  ass_process_codec_private (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_5__**) ; 
 TYPE_5__* hb_fifo_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_sub (TYPE_3__*,TYPE_5__*) ; 

__attribute__((used)) static int textsub_work(hb_filter_object_t * filter,
                    hb_buffer_t ** buf_in,
                    hb_buffer_t ** buf_out)
{
    hb_filter_private_t * pv = filter->private_data;
    hb_buffer_t * in = *buf_in;
    hb_buffer_t * sub;

    if (!pv->script_initialized)
    {
        ass_process_codec_private(pv->ssaTrack,
                                  (char*)filter->subtitle->extradata,
                                  filter->subtitle->extradata_size);
        pv->script_initialized = 1;
    }

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_in = NULL;
        *buf_out = in;
        return HB_FILTER_DONE;
    }

    int in_start_ms = in->s.start / 90;

    // Get any pending subtitles and add them to the active
    // subtitle list
    while ((sub = hb_fifo_get(filter->subtitle->fifo_out)))
    {
        if (sub->s.flags & HB_BUF_FLAG_EOF)
        {
            hb_buffer_close(&sub);
            if (pv->current_sub != NULL)
            {
                // Make us some duration for final sub
                pv->current_sub->s.stop = pv->current_sub->s.start +
                                          90000LL * 10;
                process_sub(pv, pv->current_sub);
                hb_buffer_close(&pv->current_sub);
            }
            break;
        }

        // libass expects times in ms.  So to make the math easy,
        // convert to ms immediately.
        sub->s.start /= 90;
        if (sub->s.stop != AV_NOPTS_VALUE)
        {
            sub->s.stop /= 90;
        }

        // Subtitle formats such as CC can have stop times
        // that are not known until an "erase display" command
        // is encountered in the stream.  For these formats
        // current_sub is the currently active subtitle for which
        // we do not yet know the stop time.  We do not currently
        // support overlapping subtitles of this type.
        if (pv->current_sub != NULL)
        {
            // Next sub start time tells us the stop time of the
            // current sub when it is not known in advance.
            pv->current_sub->s.stop = sub->s.start;
            process_sub(pv, pv->current_sub);
            hb_buffer_close(&pv->current_sub);
        }
        if (sub->s.flags & HB_BUF_FLAG_EOS)
        {
            // marker used to "clear" previous sub that had
            // an unknown duration
            hb_buffer_close(&sub);
        }
        else if (sub->s.stop == AV_NOPTS_VALUE)
        {
            // We don't know the duration of this sub.  So we will
            // apply it to every video frame until we see a "clear" sub.
            pv->current_sub = sub;
            pv->current_sub->s.stop = pv->current_sub->s.start;
        }
        else
        {
            // Duration of this subtitle is known, so we can just
            // process it normally.
            process_sub(pv, sub);
            hb_buffer_close(&sub);
        }
    }
    if (pv->current_sub != NULL && pv->current_sub->s.start <= in_start_ms)
    {
        // We don't know the duration of this subtitle, but we know
        // that it started before the current video frame and that
        // it is still active.  So render it on this video frame.
        pv->current_sub->s.start = pv->current_sub->s.stop;
        pv->current_sub->s.stop = in_start_ms + 1;
        process_sub(pv, pv->current_sub);
    }

    ApplySSASubs(pv, in);
    *buf_in = NULL;
    *buf_out = in;

    return HB_FILTER_OK;
}