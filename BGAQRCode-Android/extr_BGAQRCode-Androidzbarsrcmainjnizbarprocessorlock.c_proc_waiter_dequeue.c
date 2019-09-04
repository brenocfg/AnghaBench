#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lock_level; int /*<<< orphan*/  lock_owner; TYPE_2__* wait_tail; TYPE_2__* wait_head; TYPE_2__* wait_next; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_6__ {int events; int /*<<< orphan*/  requester; struct TYPE_6__* next; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 int EVENTS_PENDING ; 

__attribute__((used)) static inline proc_waiter_t *proc_waiter_dequeue (zbar_processor_t *proc)
{
    proc_waiter_t *prev = proc->wait_next, *waiter;
    if(prev)
        waiter = prev->next;
    else
        waiter = proc->wait_head;
    while(waiter && (waiter->events & EVENTS_PENDING)) {
        prev = waiter;
        proc->wait_next = waiter;
        waiter = waiter->next;
    }

    if(waiter) {
        if(prev)
            prev->next = waiter->next;
        else
            proc->wait_head = waiter->next;
        if(!waiter->next)
            proc->wait_tail = prev;
        waiter->next = NULL;

        proc->lock_level = 1;
        proc->lock_owner = waiter->requester;
    }
    return(waiter);
}