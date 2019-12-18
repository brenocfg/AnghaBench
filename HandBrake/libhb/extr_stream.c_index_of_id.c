#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; int /*<<< orphan*/ * list; } ;
struct TYPE_5__ {TYPE_1__ pes; } ;
typedef  TYPE_2__ hb_stream_t ;

/* Variables and functions */
 int get_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int index_of_id(hb_stream_t *stream, int id)
{
    int i;

    for ( i = 0; i < stream->pes.count; ++i )
    {
        if ( id == get_id( &stream->pes.list[i] ) )
            return i;
    }

    return -1;
}