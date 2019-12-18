#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_call_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ mpqueue_head_t ;
struct TYPE_7__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 TYPE_1__* MPQUEUE (int /*<<< orphan*/ ) ; 
 TYPE_3__* TCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_entry_dequeue (TYPE_3__*) ; 

__attribute__((used)) static __inline__ mpqueue_head_t *
timer_call_entry_dequeue(
	timer_call_t		entry)
{
	mpqueue_head_t	*old_queue = MPQUEUE(TCE(entry)->queue);

	call_entry_dequeue(TCE(entry));
	old_queue->count--;

	return old_queue;
}