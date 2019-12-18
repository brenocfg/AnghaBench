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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/ * bank_task_t ;
struct TYPE_3__ {int /*<<< orphan*/ * bank_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  bank_destroy_bank_task_ledger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bank_task_dealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  global_bank_task_lock () ; 
 int /*<<< orphan*/  global_bank_task_unlock () ; 

void
bank_task_destroy(task_t task)
{
	bank_task_t bank_task;

	/* Grab the global bank task lock before dropping the ref on task bank context */
	global_bank_task_lock();
	bank_task = task->bank_context;
	task->bank_context = NULL;
	global_bank_task_unlock();

	bank_destroy_bank_task_ledger(bank_task);
	bank_task_dealloc(bank_task, 1);
}