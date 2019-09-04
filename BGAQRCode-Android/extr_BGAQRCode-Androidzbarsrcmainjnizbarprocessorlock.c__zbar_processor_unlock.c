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
struct TYPE_6__ {scalar_t__ lock_level; int /*<<< orphan*/  lock_owner; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_7__ {int /*<<< orphan*/  notify; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_event_trigger (int /*<<< orphan*/ *) ; 
 int _zbar_thread_is_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* proc_waiter_dequeue (TYPE_1__*) ; 

int _zbar_processor_unlock (zbar_processor_t *proc,
                            int all)
{
    assert(proc->lock_level > 0);
    assert(_zbar_thread_is_self(proc->lock_owner));

    if(all)
        proc->lock_level = 0;
    else
        proc->lock_level--;

    if(!proc->lock_level) {
        proc_waiter_t *waiter = proc_waiter_dequeue(proc);
        if(waiter)
            _zbar_event_trigger(&waiter->notify);
    }
    return(0);
}