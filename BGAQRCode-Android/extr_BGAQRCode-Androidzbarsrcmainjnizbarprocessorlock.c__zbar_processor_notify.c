#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock_level; TYPE_2__* wait_head; int /*<<< orphan*/ * wait_next; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_7__ {unsigned int events; int /*<<< orphan*/  notify; struct TYPE_7__* next; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 unsigned int EVENT_CANCELED ; 
 int /*<<< orphan*/  _zbar_event_trigger (int /*<<< orphan*/ *) ; 
 TYPE_2__* proc_waiter_dequeue (TYPE_1__*) ; 

void _zbar_processor_notify (zbar_processor_t *proc,
                             unsigned events)
{
    proc->wait_next = NULL;
    proc_waiter_t *waiter;
    for(waiter = proc->wait_head; waiter; waiter = waiter->next)
        waiter->events = ((waiter->events & ~events) |
                          (events & EVENT_CANCELED));

    if(!proc->lock_level) {
        waiter = proc_waiter_dequeue(proc);
        if(waiter)
            _zbar_event_trigger(&waiter->notify);
    }
}