#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ state; } ;
typedef  TYPE_2__ job ;
struct TYPE_18__ {int argc; TYPE_5__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_20__ {TYPE_1__* cluster; } ;
struct TYPE_19__ {char* ptr; } ;
struct TYPE_16__ {int size; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 scalar_t__ JOB_STATE_ACKED ; 
 int /*<<< orphan*/  acknowledgeJob (TYPE_2__*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_3__*,int) ; 
 TYPE_2__* createJob (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dequeueJob (TYPE_2__*) ; 
 int getRawTTLFromJobID (char*) ; 
 TYPE_2__* lookupJob (char*) ; 
 int /*<<< orphan*/  myselfLeaving () ; 
 scalar_t__ registerJob (TYPE_2__*) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  setJobTTLFromID (TYPE_2__*) ; 
 int /*<<< orphan*/  tryJobGC (TYPE_2__*) ; 
 scalar_t__ validateJobIDs (TYPE_3__*,TYPE_5__**,int) ; 

void ackjobCommand(client *c) {
    int j, known = 0;

    if (validateJobIDs(c,c->argv+1,c->argc-1) == C_ERR) return;

    /* Perform the appropriate action for each job. */
    for (j = 1; j < c->argc; j++) {
        job *job = lookupJob(c->argv[j]->ptr);
        /* Case 1: No such job. Create one just to hold the ACK. However
         * if the cluster is composed by a single node we are sure the job
         * does not exist in the whole cluster, so do this only if the
         * cluster size is greater than one. */
        if (job == NULL && server.cluster->size > 1 && !myselfLeaving()) {
            char *id = c->argv[j]->ptr;
            int ttl = getRawTTLFromJobID(id);

            /* TTL is even for "at most once" jobs. In this case we
             * don't need to create a dummy hack. */
            if (ttl & 1) {
                job = createJob(id,JOB_STATE_ACKED,0,0);
                setJobTTLFromID(job);
                serverAssert(registerJob(job) == C_OK);
            }
        }
        /* Case 2: Job exists and is not acknowledged. Change state. */
        else if (job && job->state != JOB_STATE_ACKED) {
            dequeueJob(job); /* Safe to call if job is not queued. */
            acknowledgeJob(job);
            known++;
        }
        /* Anyway... start a GC attempt on the acked job. */
        if (job) tryJobGC(job);
    }
    addReplyLongLong(c,known);
}