#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* timer_call_t ;
typedef  int boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  param0; int /*<<< orphan*/  func; scalar_t__ entry_time; scalar_t__ deadline; } ;
struct TYPE_6__ {int ttd; scalar_t__ flags; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_CANCEL ; 
 int /*<<< orphan*/  DTRACE_TMR6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_4__* TCE (TYPE_1__*) ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callout__cancel ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  quantum_timer_set_deadline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_call_func_t ; 
 int /*<<< orphan*/  timer_call_param_t ; 
 int /*<<< orphan*/  uint32_t ; 

boolean_t
timer_call_quantum_timer_cancel(
	timer_call_t            call)
{
	assert(ml_get_interrupts_enabled() == FALSE);

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_CANCEL | DBG_FUNC_START,
		VM_KERNEL_UNSLIDE_OR_PERM(call), TCE(call)->deadline, 
		0, call->flags, 0);
	
	TCE(call)->deadline = 0;
	quantum_timer_set_deadline(0);

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_CANCEL | DBG_FUNC_END,
		VM_KERNEL_UNSLIDE_OR_PERM(call), 0,
		TCE(call)->deadline - mach_absolute_time(),
		TCE(call)->deadline - TCE(call)->entry_time, 0);
	
#if CONFIG_DTRACE
	DTRACE_TMR6(callout__cancel, timer_call_func_t, TCE(call)->func,
	    timer_call_param_t, TCE(call)->param0, uint32_t, call->flags, 0,
	    (call->ttd >> 32), (unsigned) (call->ttd & 0xFFFFFFFF));
#endif

	return true;
}