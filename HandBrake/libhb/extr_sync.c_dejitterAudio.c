#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double next_pts; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_7__ {double duration; double start; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 int ABS (double) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  removeAudioJitter (TYPE_2__*,int) ; 

__attribute__((used)) static void dejitterAudio( sync_stream_t * stream )
{
    int           ii, count, jitter_stop;
    double        duration;
    hb_buffer_t * buf, * buf0, * buf1;

    count = hb_list_count(stream->in_queue);
    if (count < 4)
    {
        return;
    }

    // Look for start of jitter sequence
    jitter_stop = 0;
    buf0 = hb_list_item(stream->in_queue, 0);
    buf1 = hb_list_item(stream->in_queue, 1);
    if (ABS(buf0->s.duration - (buf1->s.start - stream->next_pts)) < 1.1)
    {
        // Ignore very small jitter
        return;
    }
    buf = hb_list_item(stream->in_queue, 0);
    duration = buf->s.duration;

    // Look for end of jitter sequence
    for (ii = 1; ii < count; ii++)
    {
        buf = hb_list_item(stream->in_queue, ii);
        if (ABS(duration - (buf->s.start - stream->next_pts)) < (90 * 40))
        {
            // Finds the largest span that has low jitter
            jitter_stop = ii;
        }
        duration += buf->s.duration;
    }
    if (jitter_stop >= 4)
    {
        removeAudioJitter(stream, jitter_stop);
    }
}