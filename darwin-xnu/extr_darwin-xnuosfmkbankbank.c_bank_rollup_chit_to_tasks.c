#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ledger_t ;
typedef  int /*<<< orphan*/  ledger_amount_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  energy; int /*<<< orphan*/  cpu_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  energy_billed_to_others; int /*<<< orphan*/  energy_billed_to_me; int /*<<< orphan*/  cpu_time_billed_to_others; int /*<<< orphan*/  cpu_time_billed_to_me; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_ACCOUNT_INFO ; 
 int BANK_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BANK_SETTLE_CPU_TIME ; 
 int /*<<< orphan*/  BANK_SETTLE_ENERGY ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_2__ bank_ledgers ; 
 int /*<<< orphan*/  ledger_credit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_debit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ledger_get_entries (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ task_ledgers ; 

__attribute__((used)) static void
bank_rollup_chit_to_tasks(
	ledger_t bill,
	ledger_t bank_holder_ledger,
	ledger_t bank_merchant_ledger,
	int bank_holder_pid,
	int bank_merchant_pid)
{
	ledger_amount_t credit;
	ledger_amount_t debit;
	kern_return_t ret;

	if (bank_holder_ledger == bank_merchant_ledger)
		return;

	ret = ledger_get_entries(bill, bank_ledgers.cpu_time, &credit, &debit);
	if (ret == KERN_SUCCESS) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(BANK_CODE(BANK_ACCOUNT_INFO, (BANK_SETTLE_CPU_TIME))) | DBG_FUNC_NONE,
			bank_merchant_pid, bank_holder_pid, credit, debit, 0);

		if (bank_holder_ledger) {
			ledger_credit(bank_holder_ledger, task_ledgers.cpu_time_billed_to_me, credit);
			ledger_debit(bank_holder_ledger, task_ledgers.cpu_time_billed_to_me, debit);
		}

		if (bank_merchant_ledger) {
			ledger_credit(bank_merchant_ledger, task_ledgers.cpu_time_billed_to_others, credit);
			ledger_debit(bank_merchant_ledger, task_ledgers.cpu_time_billed_to_others, debit);
		}
	}

	ret = ledger_get_entries(bill, bank_ledgers.energy, &credit, &debit);
	if (ret == KERN_SUCCESS) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(BANK_CODE(BANK_ACCOUNT_INFO, (BANK_SETTLE_ENERGY))) | DBG_FUNC_NONE,
			bank_merchant_pid, bank_holder_pid, credit, debit, 0);

		if (bank_holder_ledger) {
			ledger_credit(bank_holder_ledger, task_ledgers.energy_billed_to_me, credit);
			ledger_debit(bank_holder_ledger, task_ledgers.energy_billed_to_me, debit);
		}

		if (bank_merchant_ledger) {
			ledger_credit(bank_merchant_ledger, task_ledgers.energy_billed_to_others, credit);
			ledger_debit(bank_merchant_ledger, task_ledgers.energy_billed_to_others, debit);
		}
	}
}