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
struct TYPE_4__ {int /*<<< orphan*/ * maskp; int /*<<< orphan*/  arg1; int /*<<< orphan*/  arg0; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mp_call_t ;
typedef  int /*<<< orphan*/  mp_call_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_MP_CPUS_CALL_ACTION ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t cpu_number () ; 
 int /*<<< orphan*/  i_bit_set (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 TYPE_1__* mp_call_dequeue_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_call_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_call_head_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_call_head_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_cpus_call_head ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mp_cpus_call_action(void)
{
	mp_call_queue_t	*cqp;
	boolean_t	intrs_enabled;
	mp_call_t	*callp;
	mp_call_t	call;

	assert(!ml_get_interrupts_enabled());
	cqp = &mp_cpus_call_head[cpu_number()];
	intrs_enabled = mp_call_head_lock(cqp);
	while ((callp = mp_call_dequeue_locked(cqp)) != NULL) {
		/* Copy call request to the stack to free buffer */
		call = *callp;
		mp_call_free(callp);
		if (call.func != NULL) {
			mp_call_head_unlock(cqp, intrs_enabled);
			KERNEL_DEBUG_CONSTANT(
				TRACE_MP_CPUS_CALL_ACTION,
				VM_KERNEL_UNSLIDE(call.func), VM_KERNEL_UNSLIDE_OR_PERM(call.arg0),
				VM_KERNEL_UNSLIDE_OR_PERM(call.arg1), VM_KERNEL_ADDRPERM(call.maskp), 0);
			call.func(call.arg0, call.arg1);
			(void) mp_call_head_lock(cqp);
		}
		if (call.maskp != NULL)
			i_bit_set(cpu_number(), call.maskp);
	}
	mp_call_head_unlock(cqp, intrs_enabled);
}