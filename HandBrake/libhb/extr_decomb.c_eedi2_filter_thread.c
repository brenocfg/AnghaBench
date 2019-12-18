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
struct TYPE_4__ {int /*<<< orphan*/  eedi2_taskset; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_5__ {int plane; TYPE_1__* pv; } ;
typedef  TYPE_2__ eedi2_thread_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  eedi2_interpolate_plane (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int) ; 
 int /*<<< orphan*/  taskset_thread_complete (int /*<<< orphan*/ *,int) ; 
 scalar_t__ taskset_thread_stop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_wait4start (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void eedi2_filter_thread( void *thread_args_v )
{
    hb_filter_private_t * pv;
    int plane;
    eedi2_thread_arg_t *thread_args = thread_args_v;

    pv = thread_args->pv;
    plane = thread_args->plane;

    hb_deep_log(3, "eedi2 thread started for plane %d", plane);

    while (1)
    {
        /*
         * Wait here until there is work to do.
         */
        taskset_thread_wait4start( &pv->eedi2_taskset, plane );

        if( taskset_thread_stop( &pv->eedi2_taskset, plane ) )
        {
            /*
             * No more work to do, exit this thread.
             */
            break;
        }

        /*
         * Process plane
         */
        eedi2_interpolate_plane( pv, plane );

        /*
         * Finished this segment, let everyone know.
         */
        taskset_thread_complete( &pv->eedi2_taskset, plane );
    }

    taskset_thread_complete( &pv->eedi2_taskset, plane );
}