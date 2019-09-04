#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/ * nodes_confirmed; } ;
typedef  TYPE_1__ job ;

/* Variables and functions */
 int /*<<< orphan*/  AOFAckJob (TYPE_1__*) ; 
 scalar_t__ JOB_STATE_ACKED ; 
 int /*<<< orphan*/  dequeueJob (TYPE_1__*) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_1__*,int /*<<< orphan*/ ) ; 

void acknowledgeJob(job *job) {
    if (job->state == JOB_STATE_ACKED) return;

    dequeueJob(job);
    job->state = JOB_STATE_ACKED;
    /* Remove the nodes_confirmed hash table if it exists.
     * tryJobGC() will take care to create a new one used for the GC
     * process. */
    if (job->nodes_confirmed) {
        dictRelease(job->nodes_confirmed);
        job->nodes_confirmed = NULL;
    }
    updateJobAwakeTime(job,0); /* Make sure we'll schedule a job GC. */
    AOFAckJob(job); /* Change job state in AOF. */
}