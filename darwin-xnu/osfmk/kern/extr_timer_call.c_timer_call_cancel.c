#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* timer_call_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_15__ {int soft_deadline; int flags; int earliest_soft_deadline; int ttd; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ mpqueue_head_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {int deadline; } ;
struct TYPE_13__ {int deadline; int entry_time; int /*<<< orphan*/  param0; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 TYPE_12__* CE (int /*<<< orphan*/ ) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_CANCEL ; 
 int /*<<< orphan*/  DTRACE_TMR6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_10__* TCE (TYPE_1__*) ; 
 int TIMER_CALL_RATELIMITED ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int UINT64_MAX ; 
 int VM_KERNEL_UNSLIDE_OR_PERM (TYPE_1__*) ; 
 int /*<<< orphan*/  callout__cancel ; 
 int mach_absolute_time () ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 TYPE_1__* timer_call_dequeue_unlocked (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_call_func_t ; 
 int /*<<< orphan*/  timer_call_param_t ; 
 int /*<<< orphan*/  timer_queue_cancel (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_queue_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  uint32_t ; 

boolean_t
timer_call_cancel(
	timer_call_t		call)
{
	mpqueue_head_t		*old_queue;
	spl_t			s;

	s = splclock();

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_CANCEL | DBG_FUNC_START,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		TCE(call)->deadline, call->soft_deadline, call->flags, 0);

	old_queue = timer_call_dequeue_unlocked(call);

	if (old_queue != NULL) {
		timer_queue_lock_spin(old_queue);
		if (!queue_empty(&old_queue->head)) {
			timer_queue_cancel(old_queue, TCE(call)->deadline, CE(queue_first(&old_queue->head))->deadline);
 			timer_call_t thead = (timer_call_t)queue_first(&old_queue->head);
 			old_queue->earliest_soft_deadline = thead->flags & TIMER_CALL_RATELIMITED ? TCE(thead)->deadline : thead->soft_deadline;
		}
		else {
			timer_queue_cancel(old_queue, TCE(call)->deadline, UINT64_MAX);
			old_queue->earliest_soft_deadline = UINT64_MAX;
		}
		timer_queue_unlock(old_queue);
	}
	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_CANCEL | DBG_FUNC_END,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		VM_KERNEL_UNSLIDE_OR_PERM(old_queue),
		TCE(call)->deadline - mach_absolute_time(),
		TCE(call)->deadline - TCE(call)->entry_time, 0);
	splx(s);

#if CONFIG_DTRACE
	DTRACE_TMR6(callout__cancel, timer_call_func_t, TCE(call)->func,
	    timer_call_param_t, TCE(call)->param0, uint32_t, call->flags, 0,
	    (call->ttd >> 32), (unsigned) (call->ttd & 0xFFFFFFFF));
#endif

	return (old_queue != NULL);
}