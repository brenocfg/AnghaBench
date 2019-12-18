#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ done; int /*<<< orphan*/  flush; } ;
typedef  TYPE_1__ sync_stream_t ;
struct TYPE_6__ {int stream_count; TYPE_1__* streams; } ;
typedef  TYPE_2__ sync_common_t ;

/* Variables and functions */
 int /*<<< orphan*/  streamFlush (TYPE_1__*) ; 

__attribute__((used)) static void flushStreams( sync_common_t * common )
{
    int ii;

    // Make sure all streams are complete
    for (ii = 0; ii < common->stream_count; ii++)
    {
        sync_stream_t * stream = &common->streams[ii];
        if (!stream->done && !stream->flush)
        {
            return;
        }
    }

    // Flush all streams
    for (ii = 0; ii < common->stream_count; ii++)
    {
        sync_stream_t * stream = &common->streams[ii];
        if (stream->done)
        {
            continue;
        }
        streamFlush(stream);
    }
}