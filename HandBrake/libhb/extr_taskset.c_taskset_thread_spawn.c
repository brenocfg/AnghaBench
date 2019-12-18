#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_func_t ;
struct TYPE_4__ {int /*<<< orphan*/ ** task_threads; } ;
typedef  TYPE_1__ taskset_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_thread_init (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskset_thread_args (TYPE_1__*,int) ; 

int
taskset_thread_spawn( taskset_t *ts, int thr_idx, const char *descr,
                      thread_func_t *func, int priority )
{
    ts->task_threads[thr_idx] = hb_thread_init( descr, func,
                                                taskset_thread_args( ts, thr_idx ),
                                                priority);
    return( ts->task_threads[thr_idx] != NULL );
}