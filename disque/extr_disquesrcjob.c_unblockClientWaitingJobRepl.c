#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* job; } ;
struct TYPE_6__ {TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_7__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ JOB_STATE_ACTIVE ; 
 scalar_t__ JOB_STATE_WAIT_REPL ; 
 int /*<<< orphan*/  deleteJobFromCluster (TYPE_4__*) ; 

void unblockClientWaitingJobRepl(client *c) {
    /* If the job is still waiting for synchronous replication, but the client
     * waiting it gets freed or reaches the timeout, we unblock the client and
     * forget about the job. */
    if (c->bpop.job->state == JOB_STATE_WAIT_REPL) {
        /* Set the job as active before calling deleteJobFromCluster() since
         * otherwise unregistering the job will, in turn, unblock the client,
         * which we are already doing here. */
        c->bpop.job->state = JOB_STATE_ACTIVE;
        deleteJobFromCluster(c->bpop.job);
    }
    c->bpop.job = NULL;
}