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
struct TYPE_5__ {int mode; int /*<<< orphan*/  decomb_check_taskset; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {int segment; int* segment_start; int* segment_height; TYPE_1__* pv; } ;
typedef  TYPE_2__ decomb_thread_arg_t ;

/* Variables and functions */
 int MODE_FILTER ; 
 int /*<<< orphan*/  check_combing_mask (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  check_filtered_combing_mask (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int) ; 
 int /*<<< orphan*/  taskset_thread_complete (int /*<<< orphan*/ *,int) ; 
 scalar_t__ taskset_thread_stop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_wait4start (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void decomb_check_thread( void *thread_args_v )
{
    hb_filter_private_t * pv;
    int segment, segment_start, segment_stop;
    decomb_thread_arg_t *thread_args = thread_args_v;

    pv = thread_args->pv;
    segment = thread_args->segment;

    hb_deep_log(3, "decomb check thread started for segment %d", segment);

    while (1)
    {
        /*
         * Wait here until there is work to do.
         */
        taskset_thread_wait4start( &pv->decomb_check_taskset, segment );

        if (taskset_thread_stop( &pv->decomb_check_taskset, segment ))
        {
            /*
             * No more work to do, exit this thread.
             */
            break;
        }

        segment_start = thread_args->segment_start[0];
        segment_stop = segment_start + thread_args->segment_height[0];

        if (pv->mode & MODE_FILTER)
        {
            check_filtered_combing_mask(pv, segment, segment_start, segment_stop);
        }
        else
        {
            check_combing_mask(pv, segment, segment_start, segment_stop);
        }

        taskset_thread_complete( &pv->decomb_check_taskset, segment );
    }

    /*
     * Finished this segment, let everyone know.
     */
    taskset_thread_complete( &pv->decomb_check_taskset, segment );
}