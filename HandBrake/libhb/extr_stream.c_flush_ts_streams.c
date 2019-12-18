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
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * generate_output_data (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_buffer_list_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t * flush_ts_streams( hb_stream_t *stream )
{
    hb_buffer_list_t list;
    hb_buffer_t *buf;
    int ii;

    hb_buffer_list_clear(&list);
    for (ii = 0; ii < stream->ts.count; ii++)
    {
        buf = generate_output_data(stream, ii);
        hb_buffer_list_append(&list, buf);
    }
    return hb_buffer_list_clear(&list);
}