#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int /*<<< orphan*/  logical_writes; int /*<<< orphan*/  physical_writes; } ;
struct TYPE_6__ {int /*<<< orphan*/  ledger; } ;

/* Variables and functions */
 int IOMON_DISABLE ; 
 int IOMON_ENABLE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  ledger_disable_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_disable_refill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_set_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int task_iomon_interval_secs ; 
 int task_iomon_limit_mb ; 
 TYPE_4__ task_ledgers ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

kern_return_t
task_io_monitor_ctl(task_t task, uint32_t *flags)
{
	ledger_t ledger = task->ledger;

	task_lock(task);
	if (*flags & IOMON_ENABLE) {
		/* Configure the physical I/O ledger */	
		ledger_set_limit(ledger, task_ledgers.physical_writes, (task_iomon_limit_mb * 1024 * 1024), 0);
		ledger_set_period(ledger, task_ledgers.physical_writes, (task_iomon_interval_secs * NSEC_PER_SEC));

		/* Configure the logical I/O ledger */
		ledger_set_limit(ledger, task_ledgers.logical_writes, (task_iomon_limit_mb * 1024 * 1024), 0);
		ledger_set_period(ledger, task_ledgers.logical_writes, (task_iomon_interval_secs * NSEC_PER_SEC));
		
	} else if (*flags & IOMON_DISABLE) {
		/*
		 * Caller wishes to disable I/O monitor on the task.
		 */
		ledger_disable_refill(ledger, task_ledgers.physical_writes);
		ledger_disable_callback(ledger, task_ledgers.physical_writes);
		ledger_disable_refill(ledger, task_ledgers.logical_writes);
		ledger_disable_callback(ledger, task_ledgers.logical_writes);
	}

	task_unlock(task);
	return KERN_SUCCESS;
}