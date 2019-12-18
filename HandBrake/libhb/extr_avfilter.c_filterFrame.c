#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  list; int /*<<< orphan*/  graph; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_12__ {int /*<<< orphan*/  start; int /*<<< orphan*/  stop; } ;
struct TYPE_14__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_avfilter_add_buf (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* hb_avfilter_get_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int hb_buffer_list_count (int /*<<< orphan*/ *) ; 
 TYPE_3__* hb_buffer_list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* hb_buffer_list_rem_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t* filterFrame( hb_filter_private_t * pv, hb_buffer_t * in )
{
    hb_buffer_list_t   list;
    hb_buffer_t      * buf, * next;

    hb_avfilter_add_buf(pv->graph, in);
    buf = hb_avfilter_get_buf(pv->graph);
    while (buf != NULL)
    {
        hb_buffer_list_append(&pv->list, buf);
        buf = hb_avfilter_get_buf(pv->graph);
    }

    // Delay one frame so we can set the stop time of the output buffer
    hb_buffer_list_clear(&list);
    while (hb_buffer_list_count(&pv->list) > 1)
    {
        buf  = hb_buffer_list_rem_head(&pv->list);
        next = hb_buffer_list_head(&pv->list);

        buf->s.stop = next->s.start;
        hb_buffer_list_append(&list, buf);
    }

    return hb_buffer_list_head(&list);
}