#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  frame_count; TYPE_4__** buf; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_17__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;
struct TYPE_15__ {int flags; } ;
struct TYPE_18__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_set (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* mt_frame_filter (TYPE_2__*) ; 
 TYPE_4__* mt_frame_filter_flush (TYPE_2__*) ; 

__attribute__((used)) static int mt_frame_work(hb_filter_object_t  * filter,
                         hb_buffer_t        ** buf_in,
                         hb_buffer_t        ** buf_out )
{
    hb_filter_private_t *pv = filter->private_data;
    hb_buffer_t *in = *buf_in;

    *buf_in  = NULL;
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        hb_buffer_list_t list;
        hb_buffer_t *buf;

        // Flush buffered frames
        buf = mt_frame_filter_flush(pv);
        hb_buffer_list_set(&list, buf);

        // And terminate the buffer list with a EOF buffer
        hb_buffer_list_append(&list, in);
        *buf_out = hb_buffer_list_clear(&list);

        return HB_FILTER_DONE;
    }

    pv->buf[pv->frame_count++] = in;
    *buf_out = mt_frame_filter(pv);

    return HB_FILTER_OK;
}