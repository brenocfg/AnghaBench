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
struct TYPE_3__ {int /*<<< orphan*/  task_cond_lock; scalar_t__ thread_count; int /*<<< orphan*/  task_complete_bitmap; int /*<<< orphan*/  task_complete; int /*<<< orphan*/  bitmap_elements; int /*<<< orphan*/  task_begin; int /*<<< orphan*/  task_begin_bitmap; } ;
typedef  TYPE_1__ taskset_t ;

/* Variables and functions */
 int /*<<< orphan*/  allbits_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bit_nclear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hb_cond_broadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void
taskset_cycle( taskset_t *ts )
{
    hb_lock( ts->task_cond_lock );

    /*
     * Signal all threads that their work is available.
     */
    bit_nset( ts->task_begin_bitmap, 0, ts->thread_count - 1 );
    hb_cond_broadcast( ts->task_begin );

    /*
     * Wait until all threads have completed.  Note that we must
     * loop here as hb_cond_wait() on some platforms (e.g pthead_cond_wait)
     * may unblock prematurely.
     */
    do
    {
        hb_cond_wait( ts->task_complete, ts->task_cond_lock );
    } while ( !allbits_set( ts->task_complete_bitmap, ts->bitmap_elements ) );

    /*
     * Clear completion indications for next time.
     */
    bit_nclear( ts->task_complete_bitmap, 0, ts->thread_count - 1 );

    hb_unlock( ts->task_cond_lock );
}