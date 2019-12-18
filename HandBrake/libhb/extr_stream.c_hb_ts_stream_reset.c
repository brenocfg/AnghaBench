#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; void* last_timestamp; void* pcr; scalar_t__ found_pcr; TYPE_2__* list; } ;
struct TYPE_9__ {int need_keyframe; int last_error_frame; scalar_t__ last_error_count; scalar_t__ errors; scalar_t__ frames; TYPE_3__ ts; } ;
typedef  TYPE_4__ hb_stream_t ;
struct TYPE_7__ {int skipbad; int continuity; scalar_t__ pes_info_valid; TYPE_1__* buf; } ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 

void hb_ts_stream_reset(hb_stream_t *stream)
{
    int i;

    for (i=0; i < stream->ts.count; i++)
    {
        if ( stream->ts.list[i].buf )
            stream->ts.list[i].buf->size = 0;
        stream->ts.list[i].skipbad = 1;
        stream->ts.list[i].continuity = -1;
        stream->ts.list[i].pes_info_valid = 0;
    }

    stream->need_keyframe = 1;

    stream->ts.found_pcr = 0;
    stream->ts.pcr = AV_NOPTS_VALUE;
    stream->ts.last_timestamp = AV_NOPTS_VALUE;

    stream->frames = 0;
    stream->errors = 0;
    stream->last_error_frame = -10000;
    stream->last_error_count = 0;
}