#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  scalar_t__ mach_voucher_attr_value_handle_array_size_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;
typedef  TYPE_1__* bank_element_t ;
typedef  TYPE_2__* bank_account_t ;
struct TYPE_14__ {scalar_t__ ba_holder; scalar_t__ ba_merchant; } ;
struct TYPE_13__ {scalar_t__ be_type; } ;

/* Variables and functions */
 scalar_t__ BANK_ACCOUNT ; 
 TYPE_2__* BANK_ACCOUNT_NULL ; 
 TYPE_1__* BANK_DEFAULT_TASK_VALUE ; 
 TYPE_1__* BANK_DEFAULT_VALUE ; 
 TYPE_1__* BANK_ELEMENT_NULL ; 
 scalar_t__ BANK_TASK ; 
 TYPE_2__* CAST_TO_BANK_ACCOUNT (TYPE_1__*) ; 
 TYPE_1__* CAST_TO_BANK_ELEMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* HANDLE_TO_BANK_ELEMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_VOUCHER_ATTR_VALUE_MAX_NESTED ; 
 scalar_t__ bank_get_bank_account_thread_group (TYPE_2__*) ; 
 scalar_t__ bank_get_bank_task_thread_group (scalar_t__) ; 
 int /*<<< orphan*/  bank_voucher_attr_control ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  get_bank_task_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_voucher_attr_control_get_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

__attribute__((used)) static bank_account_t
bank_get_voucher_bank_account(ipc_voucher_t voucher)
{
	bank_element_t bank_element = BANK_ELEMENT_NULL;
	bank_account_t bank_account = BANK_ACCOUNT_NULL;
	mach_voucher_attr_value_handle_t vals[MACH_VOUCHER_ATTR_VALUE_MAX_NESTED];
	mach_voucher_attr_value_handle_array_size_t val_count;
	kern_return_t kr;

	val_count = MACH_VOUCHER_ATTR_VALUE_MAX_NESTED;
	kr = mach_voucher_attr_control_get_values(bank_voucher_attr_control,
				voucher,
				vals,
				&val_count);

	if (kr != KERN_SUCCESS || val_count == 0)
		return BANK_ACCOUNT_NULL;

	bank_element = HANDLE_TO_BANK_ELEMENT(vals[0]);
	if (bank_element == BANK_DEFAULT_VALUE)
		return BANK_ACCOUNT_NULL;
	if (bank_element == BANK_DEFAULT_TASK_VALUE)
		bank_element = CAST_TO_BANK_ELEMENT(get_bank_task_context(current_task(), FALSE));

	if (bank_element->be_type == BANK_TASK) {
		return BANK_ACCOUNT_NULL;
	} else if (bank_element->be_type == BANK_ACCOUNT) {
		bank_account = CAST_TO_BANK_ACCOUNT(bank_element);
		/*
		 * Return BANK_ACCOUNT_NULL if the ba_holder is same as ba_merchant
		 * and bank account thread group is same as current thread group
		 * i.e. ba_merchant's thread group.
		 *
		 * The bank account might have ba_holder same as ba_merchant but different
		 * thread group if daemon sends a voucher to an App and then App sends the
		 * same voucher back to the daemon (IPC code will replace thread group in the
		 * voucher to App's thread group when it gets auto redeemed by the App).
		 */
		if (bank_account->ba_holder != bank_account->ba_merchant ||
			bank_get_bank_account_thread_group(bank_account) !=
				bank_get_bank_task_thread_group(bank_account->ba_merchant)) {
			return bank_account;
		} else {
			return BANK_ACCOUNT_NULL;
		}
	} else {
		panic("Bogus bank type: %d passed in bank_get_voucher_bank_account\n", bank_element->be_type);
	}
	return BANK_ACCOUNT_NULL;
}