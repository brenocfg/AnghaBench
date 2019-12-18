#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_10__ {int count; TYPE_1__* list; } ;
struct TYPE_12__ {TYPE_2__ pes; } ;
typedef  TYPE_4__ hb_stream_t ;
struct TYPE_9__ {scalar_t__ stream_kind; int map_idx; } ;

/* Variables and functions */
 scalar_t__ S ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pes_add_subtitle_to_title (TYPE_4__*,int,TYPE_3__*,int) ; 

__attribute__((used)) static void hb_init_subtitle_list(hb_stream_t *stream, hb_title_t *title)
{
    int ii;
    int map_idx;
    int largest = -1;

    // First add all that were found in a map.
    for ( map_idx = 0; 1; map_idx++ )
    {
        for ( ii = 0; ii < stream->pes.count; ii++ )
        {
            if ( stream->pes.list[ii].stream_kind == S )
            {
                if ( stream->pes.list[ii].map_idx == map_idx )
                {
                    pes_add_subtitle_to_title( stream, ii, title, -1 );
                }
                if ( stream->pes.list[ii].map_idx > largest )
                    largest = stream->pes.list[ii].map_idx;
            }
        }
        if ( map_idx > largest )
            break;
    }

    int count = hb_list_count( title->list_subtitle );
    // Now add the reset.  Sort them by stream id.
    for ( ii = 0; ii < stream->pes.count; ii++ )
    {
        if ( stream->pes.list[ii].stream_kind == S )
        {
            pes_add_subtitle_to_title( stream, ii, title, count );
        }
    }
}