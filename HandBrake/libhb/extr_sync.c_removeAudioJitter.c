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
struct TYPE_7__ {double next_pts; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_6__ {double start; double duration; double stop; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void removeAudioJitter(sync_stream_t * stream, int stop)
{
    int           ii;
    hb_buffer_t * buf;
    double        next_pts;

    // If duration of sum of packet durations is close to duration
    // as measured by timestamps, align timestamps to packet durations.
    // The packet durations are computed based on samplerate and
    // number of samples and are therefore a reliable measure
    // of the actual duration of an audio frame.
    buf = hb_list_item(stream->in_queue, 0);
    buf->s.start = stream->next_pts;
    next_pts = stream->next_pts + buf->s.duration;
    for (ii = 1; ii <= stop; ii++)
    {
        // Duration can be fractional, so track fractional PTS
        buf->s.stop = next_pts;
        buf = hb_list_item(stream->in_queue, ii);
        buf->s.start = next_pts;
        next_pts += buf->s.duration;
    }
}