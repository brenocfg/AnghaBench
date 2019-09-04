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
struct TYPE_6__ {TYPE_2__* wait_tail; TYPE_2__* wait_head; TYPE_2__* free_waiter; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  requester; int /*<<< orphan*/  notify; scalar_t__ events; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_thread_self () ; 
 TYPE_2__* calloc (int,int) ; 

__attribute__((used)) static inline proc_waiter_t *proc_waiter_queue (zbar_processor_t *proc)
{
    proc_waiter_t *waiter = proc->free_waiter;
    if(waiter) {
        proc->free_waiter = waiter->next;
        waiter->events = 0;
    }
    else {
        waiter = calloc(1, sizeof(proc_waiter_t));
        _zbar_event_init(&waiter->notify);
    }

    waiter->next = NULL;
    waiter->requester = _zbar_thread_self();

    if(proc->wait_head)
        proc->wait_tail->next = waiter;
    else
        proc->wait_head = waiter;
    proc->wait_tail = waiter;
    return(waiter);
}