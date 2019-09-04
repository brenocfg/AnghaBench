#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* bank_task_t ;
struct TYPE_8__ {int bt_refs; int /*<<< orphan*/  bt_macho_uuid; int /*<<< orphan*/  bt_gid; int /*<<< orphan*/  bt_uid; int /*<<< orphan*/  bt_persona_id; int /*<<< orphan*/  bt_pidversion; int /*<<< orphan*/  bt_pid; int /*<<< orphan*/  bt_unique_pid; scalar_t__ bt_flags; int /*<<< orphan*/  bt_proc_persona; int /*<<< orphan*/  bt_acc_to_charge_lock; int /*<<< orphan*/  bt_acc_to_pay_lock; int /*<<< orphan*/  bt_accounts_to_charge; int /*<<< orphan*/  bt_accounts_to_pay; int /*<<< orphan*/  bt_hasentitlement; int /*<<< orphan*/  bt_ledger; scalar_t__ bt_made; scalar_t__ bt_voucher_ref; int /*<<< orphan*/  bt_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  bsd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_TASK ; 
 TYPE_2__* BANK_TASK_NULL ; 
 int /*<<< orphan*/  LEDGER_NULL ; 
 int /*<<< orphan*/  bank_lock_attr ; 
 int /*<<< orphan*/  bank_lock_grp ; 
 int /*<<< orphan*/  bank_task_is_propagate_entitled (TYPE_1__*) ; 
 int /*<<< orphan*/  bank_task_zone ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_getgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_persona_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pidversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_uniqueid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bank_task_t
bank_task_alloc_init(task_t task)
{
	bank_task_t new_bank_task;

	new_bank_task = (bank_task_t) zalloc(bank_task_zone);
	if (new_bank_task == BANK_TASK_NULL)
		return BANK_TASK_NULL;

	new_bank_task->bt_type = BANK_TASK;
	new_bank_task->bt_voucher_ref = 0;
	new_bank_task->bt_refs = 1;
	new_bank_task->bt_made = 0;
	new_bank_task->bt_ledger = LEDGER_NULL;
	new_bank_task->bt_hasentitlement = bank_task_is_propagate_entitled(task);
	queue_init(&new_bank_task->bt_accounts_to_pay);
	queue_init(&new_bank_task->bt_accounts_to_charge);
	lck_mtx_init(&new_bank_task->bt_acc_to_pay_lock, &bank_lock_grp, &bank_lock_attr);
	lck_mtx_init(&new_bank_task->bt_acc_to_charge_lock, &bank_lock_grp, &bank_lock_attr);

	/*
	 * Initialize the persona_id struct
	 */
	bzero(&new_bank_task->bt_proc_persona, sizeof(new_bank_task->bt_proc_persona));
	new_bank_task->bt_flags = 0;
	new_bank_task->bt_unique_pid = proc_uniqueid(task->bsd_info);
	new_bank_task->bt_pid = proc_pid(task->bsd_info);
	new_bank_task->bt_pidversion = proc_pidversion(task->bsd_info);
	new_bank_task->bt_persona_id = proc_persona_id(task->bsd_info);
	new_bank_task->bt_uid = proc_getuid(task->bsd_info);
	new_bank_task->bt_gid = proc_getgid(task->bsd_info);
	proc_getexecutableuuid(task->bsd_info, new_bank_task->bt_macho_uuid, sizeof(new_bank_task->bt_macho_uuid));

#if DEVELOPMENT || DEBUG
	new_bank_task->bt_task = NULL;
	lck_mtx_lock(&bank_tasks_list_lock);
	queue_enter(&bank_tasks_list, new_bank_task, bank_task_t, bt_global_elt);
	lck_mtx_unlock(&bank_tasks_list_lock);
#endif
	return (new_bank_task);
}