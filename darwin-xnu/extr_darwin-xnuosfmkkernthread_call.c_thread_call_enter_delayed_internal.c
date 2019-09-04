#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  unsigned int uint32_t ;
typedef  TYPE_2__* thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int /*<<< orphan*/  thread_call_group_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
typedef  scalar_t__ thread_call_flavor_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  param1; int /*<<< orphan*/ * func; } ;
struct TYPE_9__ {unsigned int tc_flags; scalar_t__ tc_ttd; TYPE_1__ tc_call; scalar_t__ tc_soft_deadline; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TCF_ABSOLUTE ; 
 scalar_t__ TCF_CONTINUOUS ; 
 unsigned int THREAD_CALL_CONTINUOUS ; 
 unsigned int THREAD_CALL_DELAYED ; 
 unsigned int THREAD_CALL_DELAY_LEEWAY ; 
 unsigned int TIMEOUT_URGENCY_MASK ; 
 unsigned int TIMER_CALL_RATELIMITED ; 
 scalar_t__ TRUE ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  _arm_delayed_call_timer (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _delayed_call_enqueue (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_2__* _internal_call_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ mach_continuous_time () ; 
 int /*<<< orphan*/  thread_call_get_group (TYPE_2__*) ; 
 scalar_t__ timer_call_slop (scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ,scalar_t__*) ; 

boolean_t
thread_call_enter_delayed_internal(
		thread_call_t 		call,
		thread_call_func_t	alt_func,
		thread_call_param_t	alt_param0,
		thread_call_param_t 	param1,
		uint64_t 		deadline,
		uint64_t 		leeway,
		unsigned int 		flags)
{
	boolean_t		result = TRUE;
	thread_call_group_t	group;
	uint64_t		now, sdeadline, slop;
	uint32_t		urgency;

	thread_call_flavor_t flavor = (flags & THREAD_CALL_CONTINUOUS) ? TCF_CONTINUOUS : TCF_ABSOLUTE;

	/* direct mapping between thread_call, timer_call, and timeout_urgency values */
	urgency = (flags & TIMEOUT_URGENCY_MASK);

	spl_t s = disable_ints_and_lock();

	if (call == NULL) {
		/* allocate a structure out of internal storage, as a convenience for BSD callers */
		call = _internal_call_allocate(alt_func, alt_param0);
	}

	assert(call->tc_call.func != NULL);
	group = thread_call_get_group(call);

	/* TODO: assert that call is not enqueued before flipping the flag */
	if (flavor == TCF_CONTINUOUS) {
		now = mach_continuous_time();
		call->tc_flags |= THREAD_CALL_CONTINUOUS;
	} else {
		now = mach_absolute_time();
		call->tc_flags &= ~THREAD_CALL_CONTINUOUS;
	}

	call->tc_flags |= THREAD_CALL_DELAYED;

	call->tc_soft_deadline = sdeadline = deadline;

	boolean_t ratelimited = FALSE;
	slop = timer_call_slop(deadline, now, urgency, current_thread(), &ratelimited);

	if ((flags & THREAD_CALL_DELAY_LEEWAY) != 0 && leeway > slop)
		slop = leeway;

	if (UINT64_MAX - deadline <= slop)
		deadline = UINT64_MAX;
	else
		deadline += slop;

	if (ratelimited) {
		call->tc_flags |= TIMER_CALL_RATELIMITED;
	} else {
		call->tc_flags &= ~TIMER_CALL_RATELIMITED;
	}

	call->tc_call.param1 = param1;

	call->tc_ttd = (sdeadline > now) ? (sdeadline - now) : 0;

	result = _delayed_call_enqueue(call, group, deadline, flavor);

	_arm_delayed_call_timer(call, group, flavor);

#if CONFIG_DTRACE
	DTRACE_TMR5(thread_callout__create, thread_call_func_t, call->tc_call.func,
	            uint64_t, (deadline - sdeadline), uint64_t, (call->tc_ttd >> 32),
	            (unsigned) (call->tc_ttd & 0xFFFFFFFF), call);
#endif

	enable_ints_and_unlock(s);

	return (result);
}