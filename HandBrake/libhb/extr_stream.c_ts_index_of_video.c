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
struct TYPE_5__ {int count; } ;
struct TYPE_6__ {TYPE_1__ ts; } ;
typedef  TYPE_2__ hb_stream_t ;

/* Variables and functions */
 scalar_t__ V ; 
 scalar_t__ ts_stream_kind (TYPE_2__*,int) ; 

__attribute__((used)) static int ts_index_of_video(hb_stream_t *stream)
{
    int i;

    for ( i = 0; i < stream->ts.count; ++i )
        if ( V == ts_stream_kind( stream, i ) )
            return i;

    return -1;
}