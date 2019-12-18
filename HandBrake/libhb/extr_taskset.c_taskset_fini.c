#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int thread_count; int /*<<< orphan*/ * task_stop_bitmap; int /*<<< orphan*/ * task_complete_bitmap; int /*<<< orphan*/ * task_begin_bitmap; int /*<<< orphan*/ * task_threads_args; int /*<<< orphan*/ * task_threads; int /*<<< orphan*/  task_complete; int /*<<< orphan*/  task_begin; int /*<<< orphan*/  task_cond_lock; } ;
typedef  TYPE_1__ taskset_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_cond_broadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_cond_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_thread_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void
taskset_fini( taskset_t *ts )
{
    int i;

    hb_lock( ts->task_cond_lock );
    /*
     * Tell each thread to stop, and then cleanup.
     */
    bit_nset( ts->task_stop_bitmap, 0, ts->thread_count - 1 );
    bit_nset( ts->task_begin_bitmap, 0, ts->thread_count - 1 );
    hb_cond_broadcast( ts->task_begin );

    /*
     * Wait for all threads to exit.
     */
    hb_cond_wait( ts->task_complete, ts->task_cond_lock );
    hb_unlock( ts->task_cond_lock );

    /*
     * Clean up taskset memory.
     */
    for( i = 0; i < ts->thread_count; i++)
    {
        hb_thread_close( &ts->task_threads[i] );
    }
    hb_lock_close( &ts->task_cond_lock );
    hb_cond_close( &ts->task_begin );
    hb_cond_close( &ts->task_complete );
    free( ts->task_threads );
    if( ts->task_threads_args != NULL )
        free( ts->task_threads_args );
    free( ts->task_begin_bitmap );
    free( ts->task_complete_bitmap );
    free( ts->task_stop_bitmap );
}