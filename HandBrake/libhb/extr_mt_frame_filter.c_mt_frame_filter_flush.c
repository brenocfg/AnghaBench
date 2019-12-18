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
struct TYPE_4__ {int frame_count; int /*<<< orphan*/ ** buf; TYPE_2__* sub_filter; } ;
typedef  TYPE_1__ hb_filter_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* work ) (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static hb_buffer_t * mt_frame_filter_flush(hb_filter_private_t *pv)
{
    hb_buffer_list_t list;

    hb_buffer_list_clear(&list);
    for (int f = 0; f < pv->frame_count; f++)
    {
        hb_buffer_t * out;
        pv->sub_filter->work(pv->sub_filter, &pv->buf[f], &out);

        if (pv->buf[f] != NULL)
        {
            hb_buffer_close(&pv->buf[f]);
        }
        hb_buffer_list_append(&list, out);
    }
    pv->frame_count = 0;
    return hb_buffer_list_clear(&list);
}