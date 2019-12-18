#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ last_scr_pts; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_10__ {int stream_count; TYPE_2__* streams; } ;
typedef  TYPE_3__ sync_common_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ stop; scalar_t__ duration; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scrSlip (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void shiftTS( sync_common_t * common, int64_t delta )
{
    int ii, jj;

    scrSlip(common, delta);
    for (ii = 0; ii < common->stream_count; ii++)
    {
        hb_buffer_t   * buf = NULL;
        sync_stream_t * stream = &common->streams[ii];
        int             count = hb_list_count(stream->in_queue);

        for (jj = 0; jj < count; jj++)
        {
            buf = hb_list_item(stream->in_queue, jj);
            if (buf->s.start != AV_NOPTS_VALUE)
            {
                buf->s.start -= delta;
            }
            if (buf->s.stop != AV_NOPTS_VALUE)
            {
                buf->s.stop  -= delta;
            }
        }
        if (buf != NULL && buf->s.start != AV_NOPTS_VALUE)
        {
            stream->last_scr_pts = buf->s.start + buf->s.duration;
        }
        else
        {
            stream->last_scr_pts = (int64_t)AV_NOPTS_VALUE;
        }
    }
}