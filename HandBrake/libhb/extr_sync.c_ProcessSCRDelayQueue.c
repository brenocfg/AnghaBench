#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ pts_slip; int /*<<< orphan*/  scr_delay_queue; } ;
typedef  TYPE_3__ sync_stream_t ;
struct TYPE_14__ {int stream_count; TYPE_1__* scr; TYPE_3__* streams; } ;
typedef  TYPE_4__ sync_common_t ;
struct TYPE_12__ {int scr_sequence; scalar_t__ start; scalar_t__ stop; } ;
struct TYPE_15__ {TYPE_2__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_11__ {int scr_sequence; scalar_t__ scr_offset; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int SCR_HASH_MASK ; 
 int /*<<< orphan*/  SortedQueueBuffer (TYPE_3__*,TYPE_5__*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_5__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void ProcessSCRDelayQueue( sync_common_t * common )
{
    int ii, jj;

    for (ii = 0; ii < common->stream_count; ii++)
    {
        sync_stream_t * stream = &common->streams[ii];
        for (jj = 0; jj < hb_list_count(stream->scr_delay_queue);)
        {
            hb_buffer_t * buf = hb_list_item(stream->scr_delay_queue, jj);
            int           hash = buf->s.scr_sequence & SCR_HASH_MASK;
            if (buf->s.scr_sequence < 0)
            {
                // Unset scr_sequence indicates an external stream
                // (e.g. SRT subtitle) that is not on the same timebase
                // as the source tracks. Do not adjust timestamps for
                // scr_offset in this case.
                hb_list_rem(stream->scr_delay_queue, buf);
                SortedQueueBuffer(stream, buf);
            }
            else if (buf->s.scr_sequence == common->scr[hash].scr_sequence)
            {
                if (buf->s.start != AV_NOPTS_VALUE)
                {
                    buf->s.start -= common->scr[hash].scr_offset;
                    buf->s.start -= stream->pts_slip;
                }
                if (buf->s.stop != AV_NOPTS_VALUE)
                {
                    buf->s.stop -= common->scr[hash].scr_offset;
                    buf->s.stop -= stream->pts_slip;
                }
                hb_list_rem(stream->scr_delay_queue, buf);
                SortedQueueBuffer(stream, buf);
            }
            else
            {
                jj++;
            }
        }
    }
}