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
typedef  int /*<<< orphan*/  hb_ts_stream_t ;
struct TYPE_7__ {int alloc; int count; TYPE_3__* list; } ;
struct TYPE_8__ {TYPE_1__ ts; } ;
typedef  TYPE_2__ hb_stream_t ;
struct TYPE_9__ {int continuity; int pid; int pes_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* realloc (TYPE_3__*,int) ; 

__attribute__((used)) static int new_pid( hb_stream_t * stream )
{
    int num = stream->ts.alloc;

    if ( stream->ts.count == stream->ts.alloc )
    {
        num = stream->ts.alloc ? stream->ts.alloc * 2 : 32;
        stream->ts.list = realloc( stream->ts.list,
                                   sizeof( hb_ts_stream_t ) * num );
    }
    int ii;
    for ( ii = stream->ts.alloc; ii < num; ii++ )
    {
        memset(&stream->ts.list[ii], 0, sizeof( hb_ts_stream_t ));
        stream->ts.list[ii].continuity = -1;
        stream->ts.list[ii].pid = -1;
        stream->ts.list[ii].pes_list = -1;
    }
    stream->ts.alloc = num;
    num = stream->ts.count;
    stream->ts.count++;

    return num;
}