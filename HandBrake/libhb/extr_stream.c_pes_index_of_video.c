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
struct TYPE_5__ {scalar_t__ stream_kind; } ;

/* Variables and functions */
 scalar_t__ V ; 

__attribute__((used)) static int pes_index_of_video(hb_stream_t *stream)
{
    int i;

    for ( i = 0; i < stream->pes.count; ++i )
        if ( V == stream->pes.list[i].stream_kind )
            return i;

    return -1;
}