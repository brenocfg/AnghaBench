#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_2__* timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_15__ {int count; } ;
typedef  TYPE_3__ mpqueue_head_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/ * func; } ;
struct TYPE_14__ {TYPE_1__ call_entry; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_ENTER ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int TIMER_CALL_LEEWAY ; 
 int TIMER_CALL_RATELIMITED ; 
 int TIMER_CALL_URGENCY_MASK ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_2__*) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ past_deadline_timer_handle (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 TYPE_3__* timer_call_enqueue_deadline_unlocked (TYPE_2__*,TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ timer_call_slop (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__* timer_longterm_enqueue_unlocked (TYPE_2__*,scalar_t__,scalar_t__,TYPE_3__**,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* timer_queue_assign (scalar_t__) ; 

__attribute__((used)) static boolean_t 
timer_call_enter_internal(
	timer_call_t 		call,
	timer_call_param_t	param1,
	uint64_t 		deadline,
	uint64_t 		leeway,
	uint32_t 		flags,
	boolean_t		ratelimited)
{
	mpqueue_head_t		*queue = NULL;
	mpqueue_head_t		*old_queue;
	spl_t			s;
	uint64_t 		slop;
	uint32_t		urgency;
	uint64_t		sdeadline, ttd;

	assert(call->call_entry.func != NULL);
	s = splclock();

	sdeadline = deadline;
	uint64_t ctime = mach_absolute_time();

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_ENTER | DBG_FUNC_START,
	    VM_KERNEL_UNSLIDE_OR_PERM(call),
	    VM_KERNEL_ADDRHIDE(param1), deadline, flags, 0);

	urgency = (flags & TIMER_CALL_URGENCY_MASK);

	boolean_t slop_ratelimited = FALSE;
	slop = timer_call_slop(deadline, ctime, urgency, current_thread(), &slop_ratelimited);

	if ((flags & TIMER_CALL_LEEWAY) != 0 && leeway > slop)
		slop = leeway;

	if (UINT64_MAX - deadline <= slop) {
		deadline = UINT64_MAX;
	} else {
		deadline += slop;
	}

	if (__improbable(deadline < ctime)) {
		deadline = past_deadline_timer_handle(deadline, ctime);
		sdeadline = deadline;
	}

	if (ratelimited || slop_ratelimited) {
		flags |= TIMER_CALL_RATELIMITED;
	} else {
		flags &= ~TIMER_CALL_RATELIMITED;
	}

	ttd =  sdeadline - ctime;
#if CONFIG_DTRACE
	DTRACE_TMR7(callout__create, timer_call_func_t, TCE(call)->func,
	timer_call_param_t, TCE(call)->param0, uint32_t, flags,
	    (deadline - sdeadline),
	    (ttd >> 32), (unsigned) (ttd & 0xFFFFFFFF), call);
#endif

	/* Program timer callout parameters under the appropriate per-CPU or
	 * longterm queue lock. The callout may have been previously enqueued
	 * and in-flight on this or another timer queue.
	 */
	if (!ratelimited && !slop_ratelimited) {
		queue = timer_longterm_enqueue_unlocked(call, ctime, deadline, &old_queue, sdeadline, ttd, param1, flags);
	}

	if (queue == NULL) {
		queue = timer_queue_assign(deadline);
		old_queue = timer_call_enqueue_deadline_unlocked(call, queue, deadline, sdeadline, ttd, param1, flags);
	}

#if TIMER_TRACE
	TCE(call)->entry_time = ctime;
#endif

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_ENTER | DBG_FUNC_END,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		(old_queue != NULL), deadline, queue->count, 0); 

	splx(s);

	return (old_queue != NULL);
}