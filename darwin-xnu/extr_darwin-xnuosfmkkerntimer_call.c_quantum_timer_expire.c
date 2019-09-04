#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int /*<<< orphan*/  (* timer_call_func_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* processor_t ;
struct TYPE_5__ {scalar_t__ deadline; scalar_t__ entry_time; int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  quantum_timer; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_CALLOUT ; 
 int DECR_TIMER_EXPIRE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_3__* TCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_CALL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_ADDRHIDE (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_UNSLIDE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (int /*<<< orphan*/ ) ; 
 scalar_t__ __improbable (int) ; 
 TYPE_1__* current_processor () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
quantum_timer_expire(
	uint64_t		deadline)
{
	processor_t processor = current_processor();
	timer_call_t call = TIMER_CALL(&(processor->quantum_timer));

	if (__improbable(TCE(call)->deadline > deadline))
		panic("CPU quantum timer deadlin out of sync with timer call deadline");

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
	    DECR_TIMER_EXPIRE | DBG_FUNC_NONE,
	    VM_KERNEL_UNSLIDE_OR_PERM(call),
	    TCE(call)->deadline,
	    TCE(call)->deadline,
	    TCE(call)->entry_time, 0);
	
	timer_call_func_t func = TCE(call)->func;
	timer_call_param_t param0 = TCE(call)->param0; 
	timer_call_param_t param1 = TCE(call)->param1;
	
	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
		DECR_TIMER_CALLOUT | DBG_FUNC_START,
		VM_KERNEL_UNSLIDE_OR_PERM(call), VM_KERNEL_UNSLIDE(func),
		VM_KERNEL_ADDRHIDE(param0),
		VM_KERNEL_ADDRHIDE(param1),
		0);

#if CONFIG_DTRACE
	DTRACE_TMR7(callout__start, timer_call_func_t, func,
		timer_call_param_t, param0, unsigned, call->flags,
		0, (call->ttd >> 32),
		(unsigned) (call->ttd & 0xFFFFFFFF), call);
#endif
	(*func)(param0, param1);
			
	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
		DECR_TIMER_CALLOUT | DBG_FUNC_END,
		VM_KERNEL_UNSLIDE_OR_PERM(call), VM_KERNEL_UNSLIDE(func),
		VM_KERNEL_ADDRHIDE(param0),
		VM_KERNEL_ADDRHIDE(param1),
		0);
}