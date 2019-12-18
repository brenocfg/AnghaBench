#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* timer_call_t ;
struct TYPE_12__ {int /*<<< orphan*/  count; int /*<<< orphan*/  earliest_soft_deadline; int /*<<< orphan*/  head; } ;
typedef  TYPE_2__ mpqueue_head_t ;
struct TYPE_13__ {int /*<<< orphan*/  deadline; int /*<<< orphan*/  queue; } ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  soft_deadline; } ;

/* Variables and functions */
 TYPE_2__* MPQUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE (TYPE_2__*) ; 
 TYPE_6__* TCE (TYPE_1__*) ; 
 int TIMER_CALL_RATELIMITED ; 
 int /*<<< orphan*/  call_entry_enqueue_deadline (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ mpqueue_head_t *
timer_call_entry_enqueue_deadline(
	timer_call_t			entry,
	mpqueue_head_t			*queue,
	uint64_t			deadline)
{
	mpqueue_head_t	*old_queue = MPQUEUE(TCE(entry)->queue);

	call_entry_enqueue_deadline(TCE(entry), QUEUE(queue), deadline);

	/* For efficiency, track the earliest soft deadline on the queue,
	 * so that fuzzy decisions can be made without lock acquisitions.
	 */

	timer_call_t thead = (timer_call_t)queue_first(&queue->head);
	queue->earliest_soft_deadline = thead->flags & TIMER_CALL_RATELIMITED ? TCE(thead)->deadline : thead->soft_deadline;

	if (old_queue)
		old_queue->count--;
	queue->count++;

	return old_queue;
}