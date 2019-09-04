#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_voucher_attr_value_reference_t ;
typedef  TYPE_1__* bank_task_t ;
struct TYPE_5__ {scalar_t__ bt_refs; int /*<<< orphan*/  bt_acc_to_charge_lock; int /*<<< orphan*/  bt_acc_to_pay_lock; int /*<<< orphan*/  bt_ledger; int /*<<< orphan*/  bt_accounts_to_charge; int /*<<< orphan*/  bt_accounts_to_pay; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDGER_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bank_lock_grp ; 
 int bank_task_release_num (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  bank_task_zone ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
bank_task_dealloc(
	bank_task_t bank_task,
	mach_voucher_attr_value_reference_t sync)
{
	assert(bank_task->bt_refs >= 0);

	if (bank_task_release_num(bank_task, sync) > (int)sync)
		return;

	assert(bank_task->bt_refs == 0);
	assert(queue_empty(&bank_task->bt_accounts_to_pay));
	assert(queue_empty(&bank_task->bt_accounts_to_charge));

	assert(!LEDGER_VALID(bank_task->bt_ledger));
	lck_mtx_destroy(&bank_task->bt_acc_to_pay_lock, &bank_lock_grp);
	lck_mtx_destroy(&bank_task->bt_acc_to_charge_lock, &bank_lock_grp);


#if DEVELOPMENT || DEBUG
	lck_mtx_lock(&bank_tasks_list_lock);
	queue_remove(&bank_tasks_list, bank_task, bank_task_t, bt_global_elt);
	lck_mtx_unlock(&bank_tasks_list_lock);
#endif

	zfree(bank_task_zone, bank_task);
}