#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_16__ {scalar_t__ needjobs_adhoc_attempt; int /*<<< orphan*/ * needjobs_responders; scalar_t__ needjobs_bcast_attempt; } ;
typedef  TYPE_1__ queue ;
struct TYPE_17__ {scalar_t__ retry; int /*<<< orphan*/  queue; int /*<<< orphan*/  qtime; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ job ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ clusterNode ;
struct TYPE_19__ {int /*<<< orphan*/  unixtime; int /*<<< orphan*/  mstime; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ DICT_OK ; 
 int /*<<< orphan*/  JOB_FLAG_BCAST_QUEUED ; 
 int /*<<< orphan*/  JOB_STATE_ACTIVE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SER_MESSAGE ; 
 int /*<<< orphan*/  clusterNodesDictType ; 
 TYPE_1__* createQueue (int /*<<< orphan*/ ) ; 
 TYPE_2__* deserializeJob (unsigned char*,scalar_t__,unsigned char**,int /*<<< orphan*/ ) ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dictSetSignedIntegerVal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ enqueueJob (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeJob (TYPE_2__*) ; 
 TYPE_2__* lookupJob (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registerJob (TYPE_2__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updateQueueImportRate (TYPE_1__*) ; 

void receiveYourJobs(clusterNode *node, uint32_t numjobs, unsigned char *serializedjobs, uint32_t serializedlen) {
    dictEntry *de;
    queue *q;
    uint32_t j;
    unsigned char *nextjob = serializedjobs;

    for (j = 0; j < numjobs; j++) {
        uint32_t remlen = serializedlen - (nextjob-serializedjobs);
        job *job, *sj = deserializeJob(nextjob,remlen,&nextjob,SER_MESSAGE);

        if (sj == NULL) {
            serverLog(LL_WARNING,
                "The %d-th job received via YOURJOBS from %.40s is corrupted.",
                (int)j+1, node->name);
            return;
        }

        /* If the job does not exist, we need to add it to our jobs.
         * Otherwise just get a reference to the job we already have
         * in memory and free the deserialized one. */
        job = lookupJob(sj->id);
        if (job) {
            freeJob(sj);
        } else {
            job = sj;
            job->state = JOB_STATE_ACTIVE;
            registerJob(job);
        }
        /* Don't need to send QUEUED when adding this job into the queue,
         * we are just moving from the queue of one node to another. */
        job->flags &= ~JOB_FLAG_BCAST_QUEUED;

        /* If we are receiving a job with retry set to 0, let's set
         * job->qtime to non-zero, to force enqueueJob() to queue the job
         * the first time. As a side effect the function will set the qtime
         * value to 0, preventing a successive enqueue of the job */
        if (job->retry == 0)
            job->qtime = server.mstime; /* Any value will do. */

        if (enqueueJob(job,0) == C_ERR) continue;

        /* Update queue stats needed to optimize nodes federation. */
        q = lookupQueue(job->queue);
        if (!q) q = createQueue(job->queue);
        if (q->needjobs_responders == NULL)
            q->needjobs_responders = dictCreate(&clusterNodesDictType,NULL);

        if (dictAdd(q->needjobs_responders, node, NULL) == DICT_OK) {
            /* We reset the broadcast attempt counter, that will model the
             * delay to wait before every cluster-wide broadcast, every time
             * we receive jobs from a node not already known as a source. */
            q->needjobs_bcast_attempt = 0;
        }

        de = dictFind(q->needjobs_responders, node);
        dictSetSignedIntegerVal(de,server.unixtime);
        updateQueueImportRate(q);
        q->needjobs_adhoc_attempt = 0;
    }
}