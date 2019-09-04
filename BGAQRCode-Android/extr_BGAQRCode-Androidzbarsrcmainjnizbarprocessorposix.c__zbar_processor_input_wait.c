#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mutex; TYPE_4__* state; } ;
typedef  TYPE_2__ zbar_processor_t ;
struct TYPE_10__ {int /*<<< orphan*/  pollfd; } ;
typedef  TYPE_3__ zbar_event_t ;
struct TYPE_8__ {scalar_t__ num; } ;
struct TYPE_11__ {int /*<<< orphan*/ * kick_fds; TYPE_1__ thr_polling; } ;
typedef  TYPE_4__ processor_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int proc_poll_inputs (TYPE_2__*,int) ; 
 int proc_sleep (int) ; 

int _zbar_processor_input_wait (zbar_processor_t *proc,
                                zbar_event_t *event,
                                int timeout)
{
    processor_state_t *state = proc->state;
    if(state->thr_polling.num) {
        if(event) {
            _zbar_mutex_lock(&proc->mutex);
            event->pollfd = state->kick_fds[1];
            _zbar_mutex_unlock(&proc->mutex);
        }
        return(proc_poll_inputs(proc, timeout));
    }
    else if(timeout)
        return(proc_sleep(timeout));
    return(-1);
}