#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* timer_call_t ;
typedef  int /*<<< orphan*/  mpqueue_head_t ;
typedef  TYPE_2__* call_entry_t ;
struct TYPE_12__ {TYPE_1__* queue; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; scalar_t__ async_dequeue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*) ; 
 int DBG_FUNC_NONE ; 
 int DECR_TIMER_ASYNC_DEQ ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/ * MPQUEUE (TYPE_1__*) ; 
 TYPE_2__* TCE (TYPE_1__*) ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_dequeue_unlocked_async1 ; 
 int /*<<< orphan*/  timer_call_entry_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_longterm_dequeued_locked (TYPE_1__*) ; 
 int /*<<< orphan*/ * timer_longterm_queue ; 
 int /*<<< orphan*/  timer_queue_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_queue_unlock (int /*<<< orphan*/ *) ; 

mpqueue_head_t *
timer_call_dequeue_unlocked(
	timer_call_t 		call)
{
	call_entry_t	entry = TCE(call);
	mpqueue_head_t	*old_queue;

	DBG("timer_call_dequeue_unlocked(%p)\n", call);

	simple_lock(&call->lock);
	old_queue = MPQUEUE(entry->queue);
#if TIMER_ASSERT
	TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
		DECR_TIMER_ASYNC_DEQ | DBG_FUNC_NONE,
		VM_KERNEL_UNSLIDE_OR_PERM(call),
		call->async_dequeue,
		VM_KERNEL_UNSLIDE_OR_PERM(TCE(call)->queue),
		0, 0);
#endif
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
			timer_call_dequeue_unlocked_async1++;
#endif
			call->async_dequeue = FALSE;
			entry->queue = NULL;
		} else {
			timer_call_entry_dequeue(call);
		}
		if (old_queue == timer_longterm_queue)
			timer_longterm_dequeued_locked(call);
		timer_queue_unlock(old_queue);
	}
	simple_unlock(&call->lock);
	return (old_queue);
}