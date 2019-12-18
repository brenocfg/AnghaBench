#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {scalar_t__ interval; scalar_t__ deadline; TYPE_3__* call; } ;
struct TYPE_17__ {TYPE_1__ threshold; } ;
typedef  TYPE_2__ timer_longterm_t ;
typedef  TYPE_3__* timer_call_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_19__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_4__ mpqueue_head_t ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {scalar_t__ deadline; } ;

/* Variables and functions */
 TYPE_13__* TCE (TYPE_3__*) ; 
 TYPE_3__* TIMER_CALL (int /*<<< orphan*/ ) ; 
 int TIMER_CALL_LOCAL ; 
 scalar_t__ TIMER_LONGTERM_NONE ; 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue (TYPE_3__*) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue_async (TYPE_3__*) ; 
 int /*<<< orphan*/  timer_call_entry_enqueue_tail (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_longterm_queue ; 
 TYPE_4__* timer_queue_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (TYPE_4__*) ; 
 int /*<<< orphan*/  timer_queue_unlock (TYPE_4__*) ; 

__attribute__((used)) static void
timer_master_scan(timer_longterm_t	*tlp,
		  uint64_t		now)
{
	queue_entry_t	qe;
	timer_call_t	call;
	uint64_t	threshold;
	uint64_t	deadline;
	mpqueue_head_t	*timer_master_queue;

	if (tlp->threshold.interval != TIMER_LONGTERM_NONE)
		threshold = now + tlp->threshold.interval;
	else
		threshold = TIMER_LONGTERM_NONE;

	timer_master_queue = timer_queue_cpu(master_cpu);
	timer_queue_lock_spin(timer_master_queue);

	qe = queue_first(&timer_master_queue->head);
	while (!queue_end(&timer_master_queue->head, qe)) {
		call = TIMER_CALL(qe);
		deadline = TCE(call)->deadline;
		qe = queue_next(qe);
		if ((call->flags & TIMER_CALL_LOCAL) != 0)
			continue;
		if (!simple_lock_try(&call->lock)) {
			/* case (2c) lock order inversion, dequeue only */
			timer_call_entry_dequeue_async(call);
			continue;
		}
		if (deadline > threshold) {
			/* move from master to longterm */
			timer_call_entry_dequeue(call);
			timer_call_entry_enqueue_tail(call, timer_longterm_queue);
			if (deadline < tlp->threshold.deadline) {
				tlp->threshold.deadline = deadline;
				tlp->threshold.call = call;
			}
		}
		simple_unlock(&call->lock);
	}
	timer_queue_unlock(timer_master_queue);
}