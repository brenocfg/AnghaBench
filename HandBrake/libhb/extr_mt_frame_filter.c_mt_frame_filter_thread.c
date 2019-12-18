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
struct TYPE_5__ {int segment; int /*<<< orphan*/  out; TYPE_2__* pv; } ;
typedef  TYPE_1__ mt_frame_thread_arg_t ;
struct TYPE_6__ {int /*<<< orphan*/  taskset; int /*<<< orphan*/ ** buf; TYPE_3__* sub_filter; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* work ) (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* work_thread ) (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskset_thread_complete (int /*<<< orphan*/ *,int) ; 
 scalar_t__ taskset_thread_stop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_wait4start (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mt_frame_filter_thread(void *thread_args_v)
{
    mt_frame_thread_arg_t *thread_data = thread_args_v;
    hb_filter_private_t *pv = thread_data->pv;
    int segment = thread_data->segment;

    hb_log("MTFrame thread started for segment %d", segment);

    while (1)
    {
        // Wait until there is work to do.
        taskset_thread_wait4start(&pv->taskset, segment);

        if (taskset_thread_stop(&pv->taskset, segment))
        {
            break;
        }

        if (pv->sub_filter->work_thread != NULL)
        {
            pv->sub_filter->work_thread(pv->sub_filter,
                                 &pv->buf[segment], &thread_data->out, segment);
        }
        else
        {
            pv->sub_filter->work(pv->sub_filter,
                                 &pv->buf[segment], &thread_data->out);
        }
        if (pv->buf[segment] != NULL)
        {
            hb_buffer_close(&pv->buf[segment]);
        }

        // Finished this segment, notify.
        taskset_thread_complete(&pv->taskset, segment);
    }
    taskset_thread_complete(&pv->taskset, segment);
}