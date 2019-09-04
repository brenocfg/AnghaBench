#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int /*<<< orphan*/  mpqueue_head_t ;
typedef  TYPE_2__* call_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  param1; int /*<<< orphan*/ * queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; void* ttd; int /*<<< orphan*/  flags; void* soft_deadline; scalar_t__ async_dequeue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * MPQUEUE (int /*<<< orphan*/ *) ; 
 TYPE_2__* TCE (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_call_entry_enqueue_deadline (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  timer_longterm_dequeued_locked (TYPE_1__*) ; 
 int /*<<< orphan*/ * timer_longterm_queue ; 
 int /*<<< orphan*/  timer_queue_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_queue_unlock (int /*<<< orphan*/ *) ; 

__inline__ mpqueue_head_t *
timer_call_enqueue_deadline_unlocked(
	timer_call_t 			call,
	mpqueue_head_t			*queue,
	uint64_t			deadline,
	uint64_t			soft_deadline,
	uint64_t			ttd,
	timer_call_param_t		param1,
	uint32_t			callout_flags)
{
	call_entry_t	entry = TCE(call);
	mpqueue_head_t	*old_queue;

	DBG("timer_call_enqueue_deadline_unlocked(%p,%p,)\n", call, queue);

	simple_lock(&call->lock);

	old_queue = MPQUEUE(entry->queue);

	if (old_queue != NULL) {
		timer_queue_lock_spin(old_queue);
		if (call->async_dequeue) {
			/* collision (1c): timer already dequeued, clear flag */
#if TIMER_ASSERT
			TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
				DECR_TIMER_ASYNC_DEQ | DBG_FUNC_NONE,
				VM_KERNEL_UNSLIDE_OR_PERM(call),
				call->async_dequeue,
				VM_KERNEL_UNSLIDE_OR_PERM(TCE(call)->queue),
				0x1c, 0);
			timer_call_enqueue_deadline_unlocked_async1++;
#endif
			call->async_dequeue = FALSE;
			entry->queue = NULL;
		} else if (old_queue != queue) {
			timer_call_entry_dequeue(call);
#if TIMER_ASSERT
			timer_call_enqueue_deadline_unlocked_async2++;
#endif
		}
		if (old_queue == timer_longterm_queue)
			timer_longterm_dequeued_locked(call);
		if (old_queue != queue) {
			timer_queue_unlock(old_queue);
			timer_queue_lock_spin(queue);
		}
	} else {
		timer_queue_lock_spin(queue);
	}

	call->soft_deadline = soft_deadline;
	call->flags = callout_flags;
	TCE(call)->param1 = param1;
	call->ttd = ttd;

	timer_call_entry_enqueue_deadline(call, queue, deadline);
	timer_queue_unlock(queue);
	simple_unlock(&call->lock);

	return (old_queue);
}