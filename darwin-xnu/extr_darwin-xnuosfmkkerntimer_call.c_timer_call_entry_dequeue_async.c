#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* timer_call_t ;
struct TYPE_9__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ mpqueue_head_t ;
struct TYPE_10__ {int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  async_dequeue; } ;

/* Variables and functions */
 TYPE_2__* MPQUEUE (int /*<<< orphan*/ ) ; 
 TYPE_5__* TCE (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  qe (TYPE_1__*) ; 
 int /*<<< orphan*/  remque (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void
timer_call_entry_dequeue_async(
	timer_call_t		entry)
{
	mpqueue_head_t	*old_queue = MPQUEUE(TCE(entry)->queue);
	if (old_queue) {
		old_queue->count--;
		(void) remque(qe(entry));
		entry->async_dequeue = TRUE;
	}
	return;
}