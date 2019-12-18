#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ next_pts; int /*<<< orphan*/  in_queue; } ;
typedef  TYPE_2__ sync_stream_t ;
struct TYPE_9__ {int stream_count; TYPE_2__* streams; } ;
typedef  TYPE_3__ sync_common_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {scalar_t__ start; } ;
struct TYPE_10__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setNextPts( sync_common_t * common )
{
    int ii;

    for (ii = 0; ii < common->stream_count; ii++)
    {
        sync_stream_t * stream = &common->streams[ii];
        hb_buffer_t   * buf = hb_list_item(stream->in_queue, 0);
        if (buf != NULL)
        {
            stream->next_pts = buf->s.start;
        }
        else
        {
            stream->next_pts = (int64_t)AV_NOPTS_VALUE;
        }
    }
}