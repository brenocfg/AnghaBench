#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_2__* timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  param1; scalar_t__ deadline; } ;
struct TYPE_7__ {int /*<<< orphan*/ * func; } ;
struct TYPE_8__ {int flags; scalar_t__ ttd; TYPE_1__ call_entry; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_ENTER ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_5__* TCE (TYPE_2__*) ; 
 int TIMER_CALL_LOCAL ; 
 int TIMER_CALL_SYS_CRITICAL ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int VM_KERNEL_ADDRHIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_2__*) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 scalar_t__ past_deadline_timer_handle (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  quantum_timer_set_deadline (scalar_t__) ; 

boolean_t 
timer_call_quantum_timer_enter(
	timer_call_t 		call,
	timer_call_param_t	param1,
	uint64_t 		deadline,
	uint64_t		ctime)
{
	assert(call->call_entry.func != NULL);
	assert(ml_get_interrupts_enabled() == FALSE);

	uint32_t flags = TIMER_CALL_SYS_CRITICAL | TIMER_CALL_LOCAL;

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, DECR_TIMER_ENTER | DBG_FUNC_START,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		VM_KERNEL_ADDRHIDE(param1), deadline,
		flags, 0); 
	
	if (__improbable(deadline < ctime)) {
		deadline = past_deadline_timer_handle(deadline, ctime);
	}

	uint64_t ttd = deadline - ctime;
#if CONFIG_DTRACE
	DTRACE_TMR7(callout__create, timer_call_func_t, TCE(call)->func,
		timer_call_param_t, TCE(call)->param0, uint32_t, flags, 0,
		(ttd >> 32), (unsigned) (ttd & 0xFFFFFFFF), call);
#endif
	
	quantum_timer_set_deadline(deadline);
	TCE(call)->deadline = deadline;
	TCE(call)->param1 = param1;
	call->ttd = ttd;
	call->flags = flags;

#if TIMER_TRACE
	TCE(call)->entry_time = ctime;
#endif

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, DECR_TIMER_ENTER | DBG_FUNC_END,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		1, deadline, 0, 0); 
	
	return true;
}