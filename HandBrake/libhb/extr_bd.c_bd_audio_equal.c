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
struct TYPE_6__ {int audio_stream_count; TYPE_1__* audio_streams; } ;
struct TYPE_5__ {scalar_t__ pid; scalar_t__ coding_type; } ;
typedef  TYPE_1__ BLURAY_STREAM_INFO ;
typedef  TYPE_2__ BLURAY_CLIP_INFO ;

/* Variables and functions */

__attribute__((used)) static int bd_audio_equal( BLURAY_CLIP_INFO *a, BLURAY_CLIP_INFO *b )
{
    int ii, jj, equal;

    if ( a->audio_stream_count != b->audio_stream_count )
        return 0;

    if ( a->audio_stream_count == 0 )
        return 0;

    for ( ii = 0; ii < a->audio_stream_count; ii++ )
    {
        BLURAY_STREAM_INFO * s = &a->audio_streams[ii];
        equal = 0;
        for ( jj = 0; jj < b->audio_stream_count; jj++ )
        {
            if ( s->pid == b->audio_streams[jj].pid &&
                 s->coding_type == b->audio_streams[jj].coding_type)
            {
                equal = 1;
                break;
            }
        }
        if ( !equal )
            return 0;
    }
    return 1;
}