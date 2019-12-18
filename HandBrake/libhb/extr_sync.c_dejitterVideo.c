#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {double next_pts; int /*<<< orphan*/  in_queue; TYPE_4__* common; } ;
typedef  TYPE_6__ sync_stream_t ;
struct TYPE_15__ {double start; double duration; double stop; } ;
struct TYPE_17__ {TYPE_5__ s; } ;
typedef  TYPE_7__ hb_buffer_t ;
struct TYPE_14__ {TYPE_3__* job; } ;
struct TYPE_13__ {TYPE_2__* title; } ;
struct TYPE_11__ {int den; int num; } ;
struct TYPE_12__ {TYPE_1__ vrate; } ;

/* Variables and functions */
 double ABS (double) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_7__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  removeVideoJitter (TYPE_6__*,int) ; 

__attribute__((used)) static void dejitterVideo( sync_stream_t * stream )
{
    int           ii, count, jitter_stop;
    double        frame_duration, duration;
    hb_buffer_t * buf;

    count = hb_list_count(stream->in_queue);
    if (count < 2)
    {
        return;
    }

    frame_duration = 90000. * stream->common->job->title->vrate.den /
                              stream->common->job->title->vrate.num;

    // Look for start of jittered sequence
    buf      = hb_list_item(stream->in_queue, 1);
    duration = buf->s.start - stream->next_pts;
    if (ABS(duration - frame_duration) < 1.1)
    {
        // Ignore small jitter
        buf->s.start = stream->next_pts + frame_duration;
        buf = hb_list_item(stream->in_queue, 0);
        buf->s.start = stream->next_pts;
        buf->s.duration = frame_duration;
        buf->s.stop = stream->next_pts + frame_duration;
        return;
    }

    // Look for end of jittered sequence
    jitter_stop = 0;
    for (ii = 1; ii < count; ii++)
    {
        buf      = hb_list_item(stream->in_queue, ii);
        duration = buf->s.start - stream->next_pts;

        // Only dejitter video that aligns periodically
        // with the frame durations.
        if (ABS(duration - ii * frame_duration) < frame_duration / 3)
        {
            jitter_stop = ii;
        }
    }

    if (jitter_stop > 0)
    {
        removeVideoJitter(stream, jitter_stop);
    }
}