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
typedef  int /*<<< orphan*/  ledger_t ;
typedef  TYPE_1__* bank_task_t ;
struct TYPE_3__ {int /*<<< orphan*/  bt_acc_to_pay_lock; int /*<<< orphan*/  bt_ledger; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDGER_NULL ; 
 int /*<<< orphan*/  LEDGER_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ledger_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bank_destroy_bank_task_ledger(bank_task_t bank_task)
{
	ledger_t ledger;

	/* Remove the ledger reference from the bank task */
	lck_mtx_lock(&bank_task->bt_acc_to_pay_lock);
	assert(LEDGER_VALID(bank_task->bt_ledger));
	ledger = bank_task->bt_ledger;
	bank_task->bt_ledger = LEDGER_NULL;
	lck_mtx_unlock(&bank_task->bt_acc_to_pay_lock);

	ledger_dereference(ledger);
}