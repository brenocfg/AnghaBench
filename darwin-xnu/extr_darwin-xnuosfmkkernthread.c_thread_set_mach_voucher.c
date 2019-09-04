#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct thread_group {int dummy; } ;
typedef  int /*<<< orphan*/ * ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_voucher_t ;
struct TYPE_9__ {scalar_t__ ith_voucher_name; scalar_t__ ith_voucher; scalar_t__ started; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_IPC ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,uintptr_t,uintptr_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_THREAD_SET_VOUCHER ; 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (uintptr_t) ; 
 int /*<<< orphan*/  bank_get_bank_ledger_and_thread_group (scalar_t__,int /*<<< orphan*/ **,struct thread_group**) ; 
 int /*<<< orphan*/  bank_swap_thread_bank_ledger (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ipc_voucher_reference (scalar_t__) ; 
 int /*<<< orphan*/  ipc_voucher_release (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 scalar_t__ thread_tid (TYPE_1__*) ; 

kern_return_t 
thread_set_mach_voucher(
	thread_t		thread,
	ipc_voucher_t		voucher)
{
	ipc_voucher_t old_voucher;
	ledger_t bankledger = NULL;
	struct thread_group *banktg = NULL;

	if (THREAD_NULL == thread)
		return KERN_INVALID_ARGUMENT;

	if (thread != current_thread() && thread->started)
		return KERN_INVALID_ARGUMENT;

	ipc_voucher_reference(voucher);
	bank_get_bank_ledger_and_thread_group(voucher, &bankledger, &banktg);

	thread_mtx_lock(thread);
	old_voucher = thread->ith_voucher;
	thread->ith_voucher = voucher;
	thread->ith_voucher_name = MACH_PORT_NULL;
	thread_mtx_unlock(thread);

	bank_swap_thread_bank_ledger(thread, bankledger);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				  MACHDBG_CODE(DBG_MACH_IPC,MACH_THREAD_SET_VOUCHER) | DBG_FUNC_NONE,
				  (uintptr_t)thread_tid(thread),
				  (uintptr_t)MACH_PORT_NULL,
				  VM_KERNEL_ADDRPERM((uintptr_t)voucher),
				  3, 0);

	ipc_voucher_release(old_voucher);

	return KERN_SUCCESS;
}