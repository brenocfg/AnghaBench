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
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_6__ {double start; double duration; double stop; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ SYNC_TYPE_VIDEO ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void updateDuration( sync_stream_t * stream )
{
    // The video decoder sets a nominal duration for frames.  But the
    // actual duration needs to be computed from timestamps.
    if (stream->type == SYNC_TYPE_VIDEO)
    {
        int count = hb_list_count(stream->in_queue);
        if (count >= 2)
        {
            hb_buffer_t * buf1 = hb_list_item(stream->in_queue, count - 1);
            hb_buffer_t * buf2 = hb_list_item(stream->in_queue, count - 2);
            double duration = buf1->s.start - buf2->s.start;
            if (duration > 0)
            {
                buf2->s.duration = duration;
                buf2->s.stop = buf1->s.start;
            }
            else
            {
                buf2->s.duration = 0.;
                buf2->s.start = buf2->s.stop = buf1->s.start;
            }
        }
    }
}