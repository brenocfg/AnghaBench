#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_timer_t ;
struct TYPE_13__ {int lock_level; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/ * wait_next; scalar_t__ threaded; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_14__ {unsigned int events; int /*<<< orphan*/  notify; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 unsigned int EVENTS_PENDING ; 
 int EVENT_CANCELED ; 
 int _zbar_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_processor_unlock (TYPE_1__*,int) ; 
 int _zbar_thread_is_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int proc_wait_unthreaded (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* proc_waiter_dequeue (TYPE_1__*) ; 
 TYPE_2__* proc_waiter_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_waiter_release (TYPE_1__*,TYPE_2__*) ; 

int _zbar_processor_wait (zbar_processor_t *proc,
                          unsigned events,
                          zbar_timer_t *timeout)
{
    _zbar_mutex_lock(&proc->mutex);
    int save_level = proc->lock_level;
    proc_waiter_t *waiter = proc_waiter_queue(proc);
    waiter->events = events & EVENTS_PENDING;

    _zbar_processor_unlock(proc, 1);
    int rc;
    if(proc->threaded)
        rc = _zbar_event_wait(&waiter->notify, &proc->mutex, timeout);
    else
        rc = proc_wait_unthreaded(proc, waiter, timeout);

    if(rc <= 0 || !proc->threaded) {
        /* reacquire api lock */
        waiter->events &= EVENT_CANCELED;
        proc->wait_next = NULL;
        if(!proc->lock_level) {
            proc_waiter_t *w = proc_waiter_dequeue(proc);
            assert(w == waiter);
        }
        else
            _zbar_event_wait(&waiter->notify, &proc->mutex, NULL);
    }
    if(rc > 0 && (waiter->events & EVENT_CANCELED))
        rc = -1;

    assert(proc->lock_level == 1);
    assert(_zbar_thread_is_self(proc->lock_owner));

    proc->lock_level = save_level;
    proc_waiter_release(proc, waiter);
    _zbar_mutex_unlock(&proc->mutex);
    return(rc);
}