#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* list; } ;
struct TYPE_8__ {TYPE_1__* list; } ;
struct TYPE_11__ {TYPE_4__ ts; TYPE_2__ pes; } ;
typedef  TYPE_5__ hb_stream_t ;
struct TYPE_9__ {int pes_list; int /*<<< orphan*/  pid; } ;
struct TYPE_7__ {int next; scalar_t__ stream_id; } ;

/* Variables and functions */

__attribute__((used)) static int hb_stream_try_delete_ts_entry(hb_stream_t *stream, int indx)
{
    int ii;

    if ( stream->ts.list[indx].pid < 0 )
        return 1;

    for ( ii = stream->ts.list[indx].pes_list; ii != -1;
          ii = stream->pes.list[ii].next )
    {
        if ( stream->pes.list[ii].stream_id >= 0 )
            return 0;
    }
    stream->ts.list[indx].pid = -stream->ts.list[indx].pid;
    return 1;
}