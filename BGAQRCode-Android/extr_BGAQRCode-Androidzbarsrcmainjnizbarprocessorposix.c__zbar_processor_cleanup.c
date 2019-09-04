#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* state; scalar_t__ threaded; } ;
typedef  TYPE_3__ zbar_processor_t ;
struct TYPE_8__ {TYPE_4__* handlers; TYPE_4__* fds; } ;
struct TYPE_7__ {TYPE_4__* handlers; TYPE_4__* fds; } ;
struct TYPE_10__ {int* kick_fds; TYPE_2__ thr_polling; TYPE_1__ polling; } ;
typedef  TYPE_4__ processor_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 

int _zbar_processor_cleanup (zbar_processor_t *proc)
{
    processor_state_t *state = proc->state;
    if(proc->threaded) {
        close(state->kick_fds[0]);
        close(state->kick_fds[1]);
        state->kick_fds[0] = state->kick_fds[1] = -1;
    }
    if(state->polling.fds) {
        free(state->polling.fds);
        state->polling.fds = NULL;
        if(!proc->threaded)
            state->thr_polling.fds = NULL;
    }
    if(state->polling.handlers) {
        free(state->polling.handlers);
        state->polling.handlers = NULL;
        if(!proc->threaded)
            state->thr_polling.handlers = NULL;
    }
    if(state->thr_polling.fds) {
        free(state->thr_polling.fds);
        state->thr_polling.fds = NULL;
    }
    if(state->thr_polling.handlers) {
        free(state->thr_polling.handlers);
        state->thr_polling.handlers = NULL;
    }
    free(proc->state);
    proc->state = NULL;
    return(0);
}