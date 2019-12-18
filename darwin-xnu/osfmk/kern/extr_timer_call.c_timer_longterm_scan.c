#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_21__ {int /*<<< orphan*/  count; } ;
struct TYPE_20__ {scalar_t__ interval; scalar_t__ deadline; TYPE_5__* call; } ;
struct TYPE_22__ {scalar_t__ scan_limit; TYPE_3__ queue; int /*<<< orphan*/  scan_pauses; TYPE_2__ threshold; int /*<<< orphan*/  escalates; } ;
typedef  TYPE_4__ timer_longterm_t ;
typedef  TYPE_5__* timer_call_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  mpqueue_head_t ;
struct TYPE_24__ {int /*<<< orphan*/  head; } ;
struct TYPE_19__ {TYPE_5__* lock_data; } ;
struct TYPE_17__ {TYPE_1__ interlock; } ;
struct TYPE_23__ {scalar_t__ soft_deadline; TYPE_11__ lock; } ;
struct TYPE_18__ {scalar_t__ deadline; scalar_t__ entry_time; int /*<<< orphan*/  func; TYPE_5__* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int DBG_FUNC_NONE ; 
 int DECR_TIMER_ASYNC_DEQ ; 
 int DECR_TIMER_ESCALATE ; 
 int DECR_TIMER_OVERDUE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_15__* TCE (TYPE_5__*) ; 
 TYPE_5__* TIMER_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TIMER_LONGTERM_NONE ; 
 scalar_t__ TIMER_LONGTERM_SCAN_AGAIN ; 
 scalar_t__ VM_KERNEL_UNSLIDE (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock_try (TYPE_11__*) ; 
 int /*<<< orphan*/  simple_unlock (TYPE_11__*) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue (TYPE_5__*) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue_async (TYPE_5__*) ; 
 int /*<<< orphan*/  timer_call_entry_enqueue_deadline (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_7__* timer_longterm_queue ; 
 int /*<<< orphan*/  timer_queue_assign (scalar_t__) ; 
 int /*<<< orphan*/ * timer_queue_cpu (scalar_t__) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_queue_unlock (int /*<<< orphan*/ *) ; 

void
timer_longterm_scan(timer_longterm_t	*tlp,
		    uint64_t		time_start)
{
	queue_entry_t	qe;
	timer_call_t	call;
	uint64_t	threshold;
	uint64_t	deadline;
	uint64_t	time_limit = time_start + tlp->scan_limit;
	mpqueue_head_t	*timer_master_queue;

	assert(!ml_get_interrupts_enabled());
	assert(cpu_number() == master_cpu);

	if (tlp->threshold.interval != TIMER_LONGTERM_NONE)
		threshold = time_start + tlp->threshold.interval;

	tlp->threshold.deadline = TIMER_LONGTERM_NONE;
	tlp->threshold.call = NULL;

	if (queue_empty(&timer_longterm_queue->head))
		return;

	timer_master_queue = timer_queue_cpu(master_cpu);
	timer_queue_lock_spin(timer_master_queue);

	qe = queue_first(&timer_longterm_queue->head);
	while (!queue_end(&timer_longterm_queue->head, qe)) {
		call = TIMER_CALL(qe);
		deadline = call->soft_deadline;
		qe = queue_next(qe);
		if (!simple_lock_try(&call->lock)) {
			/* case (2c) lock order inversion, dequeue only */
#ifdef TIMER_ASSERT
			TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
				DECR_TIMER_ASYNC_DEQ | DBG_FUNC_NONE,
				VM_KERNEL_UNSLIDE_OR_PERM(call),
				VM_KERNEL_UNSLIDE_OR_PERM(TCE(call)->queue),
				VM_KERNEL_UNSLIDE_OR_PERM(call->lock.interlock.lock_data),
				0x2c, 0);
#endif
			timer_call_entry_dequeue_async(call);
			continue;
		}
		if (deadline < threshold) {
			/*
			 * This timer needs moving (escalating)
			 * to the local (boot) processor's queue.
			 */
#ifdef TIMER_ASSERT
			if (deadline < time_start)
				TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
       		 			DECR_TIMER_OVERDUE | DBG_FUNC_NONE,
					VM_KERNEL_UNSLIDE_OR_PERM(call),
					deadline,
					time_start,
					threshold,
					0);
#endif
			TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
       	 			DECR_TIMER_ESCALATE | DBG_FUNC_NONE,
				VM_KERNEL_UNSLIDE_OR_PERM(call),
				TCE(call)->deadline,
				TCE(call)->entry_time,
				VM_KERNEL_UNSLIDE(TCE(call)->func),
				0);
			tlp->escalates++;
			timer_call_entry_dequeue(call);
			timer_call_entry_enqueue_deadline(
				call, timer_master_queue, TCE(call)->deadline);
			/*
			 * A side-effect of the following call is to update
			 * the actual hardware deadline if required.
			 */
			(void) timer_queue_assign(deadline);
		} else {
			if (deadline < tlp->threshold.deadline) {
				tlp->threshold.deadline = deadline;
				tlp->threshold.call = call;
			}
		}
		simple_unlock(&call->lock);

		/* Abort scan if we're taking too long. */
		if (mach_absolute_time() > time_limit) {
			tlp->threshold.deadline = TIMER_LONGTERM_SCAN_AGAIN;
			tlp->scan_pauses++;
			DBG("timer_longterm_scan() paused %llu, qlen: %llu\n",
			    time_limit, tlp->queue.count); 
			break;
		}
	}

	timer_queue_unlock(timer_master_queue);
}