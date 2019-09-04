#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ call_queue_tail; scalar_t__ call_queue_head; scalar_t__ call_queue; void* target_thread; } ;
typedef  TYPE_1__ CallQueue ;

/* Variables and functions */
 TYPE_1__* GetQueue (void*) ; 
 TYPE_1__* callQueue_head ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static CallQueue *GetOrAllocateQueue(void *target) // Not thread safe, call while having call_queue_lock obtained.
{
	CallQueue *q = GetQueue(target);
	if (q) return q;

	q = (CallQueue *)malloc(sizeof(CallQueue));
	q->target_thread = target;
	q->call_queue = 0;
	q->call_queue_head = 0;
	q->call_queue_tail = 0;
	q->next = 0;
	if (callQueue_head)
	{
		CallQueue *last = callQueue_head;
		while(last->next) last = last->next;
		last->next = q;
	}
	else
	{
		callQueue_head = q;
	}
	return q;
}