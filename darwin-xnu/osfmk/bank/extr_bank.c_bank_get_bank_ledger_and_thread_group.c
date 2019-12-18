#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread_group {int dummy; } ;
typedef  int /*<<< orphan*/  ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;
typedef  int /*<<< orphan*/  bank_account_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  bank_get_bank_account_ledger (int /*<<< orphan*/ ) ; 
 struct thread_group* bank_get_bank_account_thread_group (int /*<<< orphan*/ ) ; 
 struct thread_group* bank_get_bank_task_thread_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bank_get_voucher_bank_account (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  get_bank_task_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
bank_get_bank_ledger_and_thread_group(
	ipc_voucher_t     voucher,
	ledger_t          *bankledger,
	struct thread_group **banktg)
{
	bank_account_t bank_account;
	struct thread_group *thread_group = NULL;

	bank_account = bank_get_voucher_bank_account(voucher);
	*bankledger = bank_get_bank_account_ledger(bank_account);
	thread_group = bank_get_bank_account_thread_group(bank_account);

	/* Return NULL thread group if voucher has current task's thread group */
	if (thread_group == bank_get_bank_task_thread_group(
			get_bank_task_context(current_task(), FALSE))) {
		thread_group = NULL;
	}
	*banktg = thread_group;
	return KERN_SUCCESS;
}