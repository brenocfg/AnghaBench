#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int /*<<< orphan*/  jobs_in; int /*<<< orphan*/  atime; int /*<<< orphan*/  sl; } ;
typedef  TYPE_1__ queue ;
struct TYPE_12__ {scalar_t__ state; scalar_t__ qtime; int retry; int flags; int /*<<< orphan*/  queue; int /*<<< orphan*/  num_deliv; int /*<<< orphan*/  num_nacks; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ job ;
struct TYPE_13__ {scalar_t__ mstime; int /*<<< orphan*/  unixtime; } ;

/* Variables and functions */
 unsigned char CLUSTERMSG_FLAG0_INCR_DELIV ; 
 unsigned char CLUSTERMSG_FLAG0_INCR_NACKS ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  DISQUE_TIME_ERR ; 
 int JOB_FLAG_BCAST_QUEUED ; 
 int JOB_FLAG_BCAST_WILLQUEUE ; 
 int JOB_FLAG_DELIVERED ; 
 int /*<<< orphan*/  JOB_ID_LEN ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int QUEUE_FLAG_PAUSED_OUT ; 
 int /*<<< orphan*/  clusterBroadcastQueued (TYPE_2__*,unsigned char) ; 
 TYPE_1__* createQueue (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupQueue (int /*<<< orphan*/ ) ; 
 scalar_t__ randomTimeError (int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalQueueAsReady (TYPE_1__*) ; 
 int /*<<< orphan*/ * skiplistInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_2__*,int /*<<< orphan*/ ) ; 

int enqueueJob(job *job, int nack) {
    if (job->state == JOB_STATE_QUEUED || job->qtime == 0) return C_ERR;
    if (job->retry == 0 && job->flags & JOB_FLAG_DELIVERED) return C_ERR;

    serverLog(LL_VERBOSE,"QUEUED %.*s", JOB_ID_LEN, job->id);

    job->state = JOB_STATE_QUEUED;

    /* Put the job into the queue and update the time we'll queue it again. */
    if (job->retry) {
        job->flags |= JOB_FLAG_BCAST_WILLQUEUE;
        job->qtime = server.mstime +
                     job->retry*1000 +
                     randomTimeError(DISQUE_TIME_ERR);
    } else {
        job->qtime = 0; /* Never re-queue at most once jobs. */
    }

    /* The first time a job is queued we don't need to broadcast a QUEUED
     * message, to save bandwidth. But the next times, when the job is
     * re-queued for lack of acknowledge, this is useful to (best effort)
     * avoid multiple nodes to re-queue the same job. */
    if (job->flags & JOB_FLAG_BCAST_QUEUED || nack) {
        unsigned char flags = nack ? CLUSTERMSG_FLAG0_INCR_NACKS :
                                     CLUSTERMSG_FLAG0_INCR_DELIV;
        clusterBroadcastQueued(job, flags);
        /* Other nodes will increment their NACKs / additional deliveries
         * counters when they'll receive the QUEUED message. We need to
         * do the same for the local copy of the job. */
        if (nack)
            job->num_nacks++;
        else
            job->num_deliv++;
    } else {
        job->flags |= JOB_FLAG_BCAST_QUEUED; /* Next time, broadcast. */
    }

    updateJobAwakeTime(job,0);
    queue *q = lookupQueue(job->queue);
    if (!q) q = createQueue(job->queue);
    serverAssert(skiplistInsert(q->sl,job) != NULL);
    q->atime = server.unixtime;
    q->jobs_in++;
    if (!(q->flags & QUEUE_FLAG_PAUSED_OUT)) signalQueueAsReady(q);
    return C_OK;
}