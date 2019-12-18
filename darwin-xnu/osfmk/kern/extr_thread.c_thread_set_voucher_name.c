#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct thread_group {int dummy; } ;
typedef  scalar_t__ mach_port_name_t ;
typedef  int /*<<< orphan*/ * ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_voucher_t ;
struct TYPE_7__ {scalar_t__ ith_voucher; scalar_t__ ith_voucher_name; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 scalar_t__ IPC_VOUCHER_NULL ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,uintptr_t,uintptr_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_DEAD ; 
 scalar_t__ MACH_PORT_VALID (scalar_t__) ; 
 int /*<<< orphan*/  MACH_THREAD_SET_VOUCHER ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (uintptr_t) ; 
 int /*<<< orphan*/  bank_get_bank_ledger_and_thread_group (scalar_t__,int /*<<< orphan*/ **,struct thread_group**) ; 
 int /*<<< orphan*/  bank_swap_thread_bank_ledger (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ convert_port_name_to_voucher (scalar_t__) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ipc_voucher_release (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 scalar_t__ thread_tid (TYPE_1__*) ; 

kern_return_t
thread_set_voucher_name(mach_port_name_t voucher_name)
{
	thread_t thread = current_thread();
	ipc_voucher_t new_voucher = IPC_VOUCHER_NULL;
	ipc_voucher_t voucher;
	ledger_t bankledger = NULL;
	struct thread_group *banktg = NULL;

	if (MACH_PORT_DEAD == voucher_name)
		return KERN_INVALID_RIGHT;

	/*
	 * agressively convert to voucher reference
	 */
	if (MACH_PORT_VALID(voucher_name)) {
		new_voucher = convert_port_name_to_voucher(voucher_name);
		if (IPC_VOUCHER_NULL == new_voucher)
			return KERN_INVALID_ARGUMENT;
	}
	bank_get_bank_ledger_and_thread_group(new_voucher, &bankledger, &banktg);

	thread_mtx_lock(thread);
	voucher = thread->ith_voucher;
	thread->ith_voucher_name = voucher_name;
	thread->ith_voucher = new_voucher;
	thread_mtx_unlock(thread);

	bank_swap_thread_bank_ledger(thread, bankledger);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				  MACHDBG_CODE(DBG_MACH_IPC,MACH_THREAD_SET_VOUCHER) | DBG_FUNC_NONE,
				  (uintptr_t)thread_tid(thread),
				  (uintptr_t)voucher_name,
				  VM_KERNEL_ADDRPERM((uintptr_t)new_voucher),
				  1, 0);

	if (IPC_VOUCHER_NULL != voucher)
		ipc_voucher_release(voucher);

	return KERN_SUCCESS;
}