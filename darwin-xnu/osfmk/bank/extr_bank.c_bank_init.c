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
struct bank_task {int dummy; } ;
struct bank_account {int dummy; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_BANK ; 
 int MAX_BANK_ACCOUNT ; 
 int MAX_BANK_TASK ; 
 void* bank_account_zone ; 
 int /*<<< orphan*/  bank_accounts_list ; 
 int /*<<< orphan*/  bank_accounts_list_lock ; 
 int /*<<< orphan*/  bank_dev_lock_attr ; 
 int /*<<< orphan*/  bank_dev_lock_grp ; 
 int /*<<< orphan*/  bank_dev_lock_grp_attr ; 
 int /*<<< orphan*/  bank_lock_attr ; 
 int /*<<< orphan*/  bank_lock_grp ; 
 int /*<<< orphan*/  bank_lock_grp_attr ; 
 int /*<<< orphan*/  bank_manager ; 
 void* bank_task_zone ; 
 int /*<<< orphan*/  bank_tasks_list ; 
 int /*<<< orphan*/  bank_tasks_list_lock ; 
 int /*<<< orphan*/  bank_voucher_attr_control ; 
 int /*<<< orphan*/  global_bank_task_lock_init () ; 
 int /*<<< orphan*/  init_bank_ledgers () ; 
 scalar_t__ ipc_register_well_known_mach_voucher_attr_manager (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 void* zinit (int,int,int,char*) ; 

void
bank_init()
{
	kern_return_t kr = KERN_SUCCESS;
	/* setup zones for bank_task and bank_account objects */
	bank_task_zone       = zinit(sizeof(struct bank_task),
	                       MAX_BANK_TASK * sizeof(struct bank_task),
	                       sizeof(struct bank_task),
	                       "bank_task");

	bank_account_zone    = zinit(sizeof(struct bank_account),
	                       MAX_BANK_ACCOUNT * sizeof(struct bank_account),
	                       sizeof(struct bank_account),
	                       "bank_account");

	init_bank_ledgers();

	/* Initialize bank lock group and lock attributes. */
	lck_grp_attr_setdefault(&bank_lock_grp_attr);
	lck_grp_init(&bank_lock_grp, "bank_lock", &bank_lock_grp_attr);
	lck_attr_setdefault(&bank_lock_attr);
	global_bank_task_lock_init();

#if DEVELOPMENT || DEBUG
	/* Initialize global bank development lock group and lock attributes. */
	lck_grp_attr_setdefault(&bank_dev_lock_grp_attr);
	lck_grp_init(&bank_dev_lock_grp, "bank_dev_lock", &bank_dev_lock_grp_attr);
	lck_attr_setdefault(&bank_dev_lock_attr);

	lck_mtx_init(&bank_tasks_list_lock, &bank_dev_lock_grp, &bank_dev_lock_attr);
	lck_mtx_init(&bank_accounts_list_lock, &bank_dev_lock_grp, &bank_dev_lock_attr);

	queue_init(&bank_tasks_list);
	queue_init(&bank_accounts_list);
#endif

	/* Register the bank manager with the Vouchers sub system. */
	kr = ipc_register_well_known_mach_voucher_attr_manager(
	                &bank_manager,
	                0,
	                MACH_VOUCHER_ATTR_KEY_BANK,
	                &bank_voucher_attr_control);
	if (kr != KERN_SUCCESS )
		panic("BANK subsystem initialization failed");

	kprintf("BANK subsystem is initialized\n");
	return ;
}