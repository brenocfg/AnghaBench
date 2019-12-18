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
struct TYPE_3__ {int /*<<< orphan*/  task_cond_lock; int /*<<< orphan*/  task_begin_bitmap; int /*<<< orphan*/  task_begin; } ;
typedef  TYPE_1__ taskset_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bit_is_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void
taskset_thread_wait4start( taskset_t *ts, int thr_idx )
{
    hb_lock( ts->task_cond_lock );
    while ( bit_is_clear( ts->task_begin_bitmap, thr_idx ) )
        hb_cond_wait( ts->task_begin, ts->task_cond_lock );

    /*
     * We've been released for one run.  Insure we block the next
     * time through the loop.
     */
    bit_clear( ts->task_begin_bitmap, thr_idx );
    hb_unlock( ts->task_cond_lock );
}