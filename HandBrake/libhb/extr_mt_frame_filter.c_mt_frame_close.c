#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* buf; struct TYPE_6__* thread_data; int /*<<< orphan*/  taskset; TYPE_3__* sub_filter; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_7__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  taskset_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt_frame_close(hb_filter_object_t *filter)
{
    hb_filter_private_t *pv = filter->private_data;

    if (pv == NULL)
    {
        return;
    }

    pv->sub_filter->close(pv->sub_filter);
    taskset_fini(&pv->taskset);
    free(pv->thread_data);
    free(pv->buf);
    free(pv);
    filter->private_data = NULL;
}