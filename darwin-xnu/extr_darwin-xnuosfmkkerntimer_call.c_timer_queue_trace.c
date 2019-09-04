#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* timer_call_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_11__ {int /*<<< orphan*/  count; int /*<<< orphan*/  head; } ;
typedef  TYPE_2__ mpqueue_head_t ;
struct TYPE_12__ {int /*<<< orphan*/  func; int /*<<< orphan*/  entry_time; int /*<<< orphan*/  deadline; } ;
struct TYPE_10__ {int /*<<< orphan*/  soft_deadline; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_QUEUE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_8__* TCE (TYPE_1__*) ; 
 TYPE_1__* TIMER_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdebug_enable ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  qe (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_queue_unlock (TYPE_2__*) ; 

void
timer_queue_trace(
	mpqueue_head_t			*queue)
{
	timer_call_t	call;
	spl_t		s;

	if (!kdebug_enable)
		return;

	s = splclock();
	timer_queue_lock_spin(queue);

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_QUEUE | DBG_FUNC_START,
		queue->count, mach_absolute_time(), 0, 0, 0); 

	if (!queue_empty(&queue->head)) {
		call = TIMER_CALL(queue_first(&queue->head));
		do {
			TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        			DECR_TIMER_QUEUE | DBG_FUNC_NONE,
				call->soft_deadline,
				TCE(call)->deadline,
				TCE(call)->entry_time,
				VM_KERNEL_UNSLIDE(TCE(call)->func),
				0);
			call = TIMER_CALL(queue_next(qe(call)));
		} while (!queue_end(&queue->head, qe(call)));
	}

	TIMER_KDEBUG_TRACE(KDEBUG_TRACE,
        	DECR_TIMER_QUEUE | DBG_FUNC_END,
		queue->count, mach_absolute_time(), 0, 0, 0); 

	timer_queue_unlock(queue);
	splx(s);
}