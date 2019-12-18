#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ next_pts; scalar_t__ type; int /*<<< orphan*/  delta_list; int /*<<< orphan*/  pts_slip; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_11__ {scalar_t__ pts; scalar_t__ delta; } ;
typedef  TYPE_3__ sync_delta_t ;
struct TYPE_12__ {int stream_count; TYPE_2__* streams; } ;
typedef  TYPE_4__ sync_common_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ start; scalar_t__ stop; scalar_t__ duration; } ;
struct TYPE_13__ {TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ SYNC_TYPE_AUDIO ; 
 scalar_t__ SYNC_TYPE_SUBTITLE ; 
 scalar_t__ SYNC_TYPE_VIDEO ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void applyDeltas( sync_common_t * common )
{
    int     ii;

    // Apply delta to any applicable buffers in the queue
    for (ii = 0; ii < common->stream_count; ii++)
    {
        sync_stream_t * stream = &common->streams[ii];

        // Make adjustments for deltas found in other streams
        sync_delta_t * delta = hb_list_item(stream->delta_list, 0);
        if (delta != NULL)
        {
            int           jj, index = -1;
            int64_t       prev_start, max = 0;
            hb_buffer_t * buf;

            prev_start = stream->next_pts;
            for (jj = 0; jj < hb_list_count(stream->in_queue); jj++)
            {
                buf = hb_list_item(stream->in_queue, jj);
                if (stream->type == SYNC_TYPE_SUBTITLE)
                {
                    if (buf->s.start > delta->pts)
                    {
                        // absorb gaps in subtitles as soon as possible
                        index = jj;
                        break;
                    }
                }
                else if (buf->s.start > delta->pts)
                {
                    // absorb gap in largest gap found in this stream.
                    if (buf->s.start - prev_start > max)
                    {
                        max = buf->s.start - prev_start;
                        index = jj;
                    }
                    if (stream->type == SYNC_TYPE_AUDIO && max >= delta->delta)
                    {
                        // absorb gaps in audio as soon as possible
                        // when there is a gap that will absorb it.
                        break;
                    }
                }
                prev_start = buf->s.start;
            }

            if (index >= 0)
            {
                for (jj = index; jj < hb_list_count(stream->in_queue); jj++)
                {
                    buf = hb_list_item(stream->in_queue, jj);
                    buf->s.start -= delta->delta;
                    if (buf->s.stop != AV_NOPTS_VALUE)
                    {
                        buf->s.stop  -= delta->delta;
                    }
                }
                // Correct the duration of the video buffer before
                // the affected timestamp correction.
                if (stream->type == SYNC_TYPE_VIDEO && index > 0)
                {
                    buf = hb_list_item(stream->in_queue, index - 1);
                    if (buf->s.duration > delta->delta)
                    {
                        buf->s.duration -= delta->delta;
                        buf->s.stop -= delta->delta;
                    }
                    else
                    {
                        buf->s.duration = 0;
                        buf->s.stop = buf->s.start;
                    }
                }
                stream->pts_slip += delta->delta;
                hb_list_rem(stream->delta_list, delta);
                free(delta);
            }
        }
    }
}