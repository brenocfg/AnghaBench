#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* thread_t ;
typedef  TYPE_4__* task_t ;
struct TYPE_8__ {int /*<<< orphan*/ * mtk_counts; } ;
struct TYPE_11__ {TYPE_1__ task_monotonic; } ;
struct TYPE_9__ {scalar_t__* mth_counts; } ;
struct TYPE_10__ {TYPE_2__ t_monotonic; } ;

/* Variables and functions */
 int MT_CORE_NFIXED ; 
 int /*<<< orphan*/  mt_core_supported ; 
 int /*<<< orphan*/  task_lock_assert_owned (TYPE_4__*) ; 

void
mt_update_task(task_t task, thread_t thread)
{
	task_lock_assert_owned(task);

	if (!mt_core_supported) {
		return;
	}

	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		task->task_monotonic.mtk_counts[i] += thread->t_monotonic.mth_counts[i];
	}
}