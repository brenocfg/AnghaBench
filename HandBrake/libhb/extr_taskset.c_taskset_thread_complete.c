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
struct TYPE_3__ {int /*<<< orphan*/  task_cond_lock; int /*<<< orphan*/  task_complete; int /*<<< orphan*/  bitmap_elements; int /*<<< orphan*/  task_complete_bitmap; } ;
typedef  TYPE_1__ taskset_t ;

/* Variables and functions */
 scalar_t__ allbits_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void
taskset_thread_complete( taskset_t *ts, int thr_idx )
{
    hb_lock( ts->task_cond_lock );
    bit_set( ts->task_complete_bitmap, thr_idx );
    if( allbits_set( ts->task_complete_bitmap, ts->bitmap_elements ) )
    {
        hb_cond_signal( ts->task_complete );
    }
    hb_unlock( ts->task_cond_lock );
}