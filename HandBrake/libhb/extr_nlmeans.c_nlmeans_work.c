#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_filter_private_t ;
struct TYPE_14__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_13__ {int flags; } ;
struct TYPE_15__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_set (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  nlmeans_add_frame (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* nlmeans_filter (int /*<<< orphan*/ *) ; 
 TYPE_3__* nlmeans_filter_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nlmeans_work(hb_filter_object_t *filter,
                           hb_buffer_t **buf_in,
                           hb_buffer_t **buf_out )
{
    hb_filter_private_t *pv = filter->private_data;
    hb_buffer_t *in = *buf_in;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        hb_buffer_list_t list;
        hb_buffer_t *buf;

        // Flush buffered frames
        buf = nlmeans_filter_flush(pv);
        hb_buffer_list_set(&list, buf);

        // And terminate the buffer list with a EOF buffer
        hb_buffer_list_append(&list, in);
        *buf_out = hb_buffer_list_clear(&list);

        *buf_in  = NULL;
        return HB_FILTER_DONE;
    }

    nlmeans_add_frame(pv, in);
    *buf_out = nlmeans_filter(pv);

    return HB_FILTER_OK;
}