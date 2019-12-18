#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ os_reason_t ;
typedef  int /*<<< orphan*/  mach_exception_code_t ;
typedef  int kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_user_faults; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_PROC_EXITREASON_CREATE ; 
 int /*<<< orphan*/  DBG_BSD_PROC ; 
 int DBG_FUNC_NONE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int EQFULL ; 
 int /*<<< orphan*/  EXC_GUARD_ENCODE_FLAVOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXC_GUARD_ENCODE_TARGET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXC_GUARD_ENCODE_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUARD_TYPE_USER ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  KERN_INVALID_ARGUMENT 131 
#define  KERN_NOT_SUPPORTED 130 
#define  KERN_RESOURCE_SHORTAGE 129 
#define  KERN_SUCCESS 128 
 int OS_REASON_FLAG_ABORT ; 
 int OS_REASON_IFLAG_USER_FAULT ; 
 scalar_t__ OS_REASON_NULL ; 
 int OS_REASON_TOTAL_USER_FAULTS_PER_PROC ; 
 int /*<<< orphan*/  SIGABRT ; 
 scalar_t__ atomic_compare_exchange_strong_explicit (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ build_userspace_exit_reason (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  os_reason_free (scalar_t__) ; 
 int /*<<< orphan*/  psignal_try_thread_with_reason (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int task_violated_guard (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int
abort_with_payload_internal(proc_t p,
		uint32_t reason_namespace, uint64_t reason_code,
		user_addr_t payload, uint32_t payload_size,
		user_addr_t reason_string, uint64_t reason_flags,
		uint32_t internal_flags)
{
	os_reason_t exit_reason = OS_REASON_NULL;
	kern_return_t kr = KERN_SUCCESS;

	if (internal_flags & OS_REASON_IFLAG_USER_FAULT) {
		uint32_t old_value = atomic_load_explicit(&p->p_user_faults,
				memory_order_relaxed);
		for (;;) {
			if (old_value >= OS_REASON_TOTAL_USER_FAULTS_PER_PROC) {
				return EQFULL;
			}
			// this reloads the value in old_value
			if (atomic_compare_exchange_strong_explicit(&p->p_user_faults,
					&old_value, old_value + 1, memory_order_relaxed,
					memory_order_relaxed)) {
				break;
			}
		}
	}

	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
					p->p_pid, reason_namespace,
					reason_code, 0, 0);

	exit_reason = build_userspace_exit_reason(reason_namespace, reason_code,
			payload, payload_size, reason_string, reason_flags | OS_REASON_FLAG_ABORT);

	if (internal_flags & OS_REASON_IFLAG_USER_FAULT) {
		mach_exception_code_t code = 0;

		EXC_GUARD_ENCODE_TYPE(code, GUARD_TYPE_USER); /* simulated EXC_GUARD */
		EXC_GUARD_ENCODE_FLAVOR(code, 0);
		EXC_GUARD_ENCODE_TARGET(code, reason_namespace);

		if (exit_reason == OS_REASON_NULL) {
			kr = KERN_RESOURCE_SHORTAGE;
		} else {
			kr = task_violated_guard(code, reason_code, exit_reason);
		}
		os_reason_free(exit_reason);
	} else {
		/*
		 * We use SIGABRT (rather than calling exit directly from here) so that
		 * the debugger can catch abort_with_{reason,payload} calls.
		 */
		psignal_try_thread_with_reason(p, current_thread(), SIGABRT, exit_reason);
	}

	switch (kr) {
	case KERN_SUCCESS:
		return 0;
	case KERN_NOT_SUPPORTED:
		return ENOTSUP;
	case KERN_INVALID_ARGUMENT:
		return EINVAL;
	case KERN_RESOURCE_SHORTAGE:
	default:
		return EBUSY;
	}
}