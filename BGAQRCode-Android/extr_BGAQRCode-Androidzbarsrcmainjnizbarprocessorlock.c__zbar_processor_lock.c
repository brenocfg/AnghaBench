#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int lock_level; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_9__ {int /*<<< orphan*/  notify; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _zbar_thread_is_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zbar_thread_self () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* proc_waiter_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_waiter_release (TYPE_1__*,TYPE_2__*) ; 

int _zbar_processor_lock (zbar_processor_t *proc)
{
    if(!proc->lock_level) {
        proc->lock_owner = _zbar_thread_self();
        proc->lock_level = 1;
        return(0);
    }

    if(_zbar_thread_is_self(proc->lock_owner)) {
        proc->lock_level++;
        return(0);
    }

    proc_waiter_t *waiter = proc_waiter_queue(proc);
    _zbar_event_wait(&waiter->notify, &proc->mutex, NULL);

    assert(proc->lock_level == 1);
    assert(_zbar_thread_is_self(proc->lock_owner));

    proc_waiter_release(proc, waiter);
    return(0);
}