#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_11__ {int flags; } ;
typedef  TYPE_1__ queue ;
struct TYPE_12__ {scalar_t__ retry; } ;
typedef  TYPE_2__ job ;
typedef  int /*<<< orphan*/  clusterNode ;

/* Variables and functions */
 int NEEDJOBS_MAX_REQUEST ; 
 int QUEUE_FLAG_PAUSED_OUT ; 
 int /*<<< orphan*/  clusterSendYourJobs (int /*<<< orphan*/ *,TYPE_2__**,int) ; 
 int /*<<< orphan*/  freeJob (TYPE_2__*) ; 
 scalar_t__ getQueueImportRate (TYPE_1__*) ; 
 TYPE_1__* lookupQueue (int /*<<< orphan*/ *) ; 
 TYPE_2__* queueFetchJob (TYPE_1__*,int /*<<< orphan*/ *) ; 
 unsigned long queueLength (TYPE_1__*) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregisterJob (TYPE_2__*) ; 

void receiveNeedJobs(clusterNode *node, robj *qname, uint32_t count) {
    queue *q = lookupQueue(qname);
    unsigned long qlen = queueLength(q);
    uint32_t replyjobs = count; /* Number of jobs we are willing to provide. */
    uint32_t j;

    /* Ignore requests for jobs if:
     * 1) No such queue here, or queue is empty.
     * 2) We are actively importing jobs ourselves for this queue. */
    if (qlen == 0 || getQueueImportRate(q) > 0) return;

    /* Ignore request if queue is paused in output. */
    if (q->flags & QUEUE_FLAG_PAUSED_OUT) return;

    /* To avoid that a single node is able to deplete our queue easily,
     * we provide the number of jobs requested only if we have more than
     * 2 times what it requested. Otherwise we provide at max half the jobs
     * we have, but always at least a single job. */
    if (qlen < count*2) replyjobs = qlen/2;
    if (replyjobs == 0) replyjobs = 1;

    job *jobs[NEEDJOBS_MAX_REQUEST];
    for (j = 0; j < replyjobs; j++) {
        jobs[j] = queueFetchJob(q,NULL);
        serverAssert(jobs[j] != NULL);
    }
    clusterSendYourJobs(node,jobs,replyjobs);

    /* It's possible that we sent jobs with retry=0. Remove them from
     * the local node since to take duplicates does not make sense for
     * jobs having the replication level of 1 by contract. */
    for (j = 0; j < replyjobs; j++) {
        job *job = jobs[j];
        if (job->retry == 0) {
            unregisterJob(job);
            freeJob(job);
        }
    }
}