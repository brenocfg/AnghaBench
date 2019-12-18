#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; TYPE_1__* list; } ;
struct TYPE_7__ {TYPE_2__ pes; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_5__ {int stream_id; int stream_id_ext; } ;

/* Variables and functions */

__attribute__((used)) static int index_of_ps_stream(hb_stream_t *stream, int id, int sid)
{
    int i;

    for ( i = 0; i < stream->pes.count; ++i )
    {
        if ( id == stream->pes.list[i].stream_id &&
             sid == stream->pes.list[i].stream_id_ext )
        {
            return i;
        }
    }
    // If there is no match on the stream_id_ext, try matching
    // on only the stream_id.
    for ( i = 0; i < stream->pes.count; ++i )
    {
        if ( id == stream->pes.list[i].stream_id &&
             0 == stream->pes.list[i].stream_id_ext )
        {
            return i;
        }
    }

    return -1;
}