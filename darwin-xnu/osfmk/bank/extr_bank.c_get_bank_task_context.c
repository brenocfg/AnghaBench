#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  TYPE_2__* bank_task_t ;
struct TYPE_12__ {TYPE_1__* bt_task; int /*<<< orphan*/  bt_ledger; } ;
struct TYPE_11__ {TYPE_2__* bank_context; int /*<<< orphan*/  ledger; } ;

/* Variables and functions */
 TYPE_2__* BANK_TASK_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* bank_task_alloc_init (TYPE_1__*) ; 
 int /*<<< orphan*/  bank_task_dealloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  global_bank_task_lock () ; 
 int /*<<< orphan*/  global_bank_task_unlock () ; 
 int /*<<< orphan*/  ledger_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

__attribute__((used)) static bank_task_t
get_bank_task_context
	(task_t task,
	boolean_t initialize)
{
	bank_task_t bank_task;

	if (task->bank_context || !initialize) {
		assert(task->bank_context != NULL);
		return (task->bank_context);
	}

	bank_task = bank_task_alloc_init(task);

	/* Grab the task lock and check if we won the race. */
	task_lock(task);
	if (task->bank_context) {
		task_unlock(task);
		if (bank_task != BANK_TASK_NULL) 
			bank_task_dealloc(bank_task, 1);
		return (task->bank_context);
	} else if (bank_task == BANK_TASK_NULL) {
		task_unlock(task);
		return BANK_TASK_NULL;
	}
	/* We won the race. Take a ref on the ledger and initialize bank task. */
	bank_task->bt_ledger = task->ledger;
#if DEVELOPMENT || DEBUG
	bank_task->bt_task = task;
#endif
	ledger_reference(task->ledger);

	/* Grab the global bank task lock before setting the bank context on a task */
	global_bank_task_lock();
	task->bank_context = bank_task;
	global_bank_task_unlock();

	task_unlock(task);
	
	return (bank_task);
}