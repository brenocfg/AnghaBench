#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* target_thread; struct TYPE_4__* next; } ;
typedef  TYPE_1__ CallQueue ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void*) ; 
 TYPE_1__* callQueue_head ; 

__attribute__((used)) static CallQueue *GetQueue(void *target) // Not thread safe, call while having call_queue_lock obtained.
{
	assert(target);
	CallQueue *q = callQueue_head;
	while(q && q->target_thread != target)
		q = q->next;
	return q;
}