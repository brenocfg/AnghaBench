#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hb_stream_type; int need_keyframe; int /*<<< orphan*/  has_IDRs; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 scalar_t__ program ; 
 scalar_t__ transport ; 

void hb_stream_set_need_keyframe(hb_stream_t *stream, int need_keyframe)
{
    if ( stream->hb_stream_type == transport ||
         stream->hb_stream_type == program )
    {
        // Only wait for a keyframe if the stream is known to have IDRs
        stream->need_keyframe = !!need_keyframe & !!stream->has_IDRs;
    }
    else
    {
        stream->need_keyframe = need_keyframe;
    }
}