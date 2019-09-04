#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int mstime_t ;
struct TYPE_13__ {int ctime; scalar_t__ state; int retry; int /*<<< orphan*/  flags; scalar_t__ etime; } ;
typedef  TYPE_1__ job ;
struct TYPE_14__ {TYPE_5__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_16__ {int mstime; } ;
struct TYPE_15__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  DISQUE_TIME_ERR ; 
 int /*<<< orphan*/  JOB_FLAG_BCAST_WILLQUEUE ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBroadcastWorking (TYPE_1__*) ; 
 int /*<<< orphan*/  dequeueJob (TYPE_1__*) ; 
 TYPE_1__* lookupJob (int /*<<< orphan*/ ) ; 
 int randomTimeError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  updateJobRequeueTime (TYPE_1__*,int) ; 
 scalar_t__ validateJobIDs (TYPE_2__*,TYPE_5__**,int) ; 

void workingCommand(client *c) {
    if (validateJobIDs(c,c->argv+1,1) == C_ERR) return;

    job *job = lookupJob(c->argv[1]->ptr);
    if (job == NULL) {
        addReplySds(c,
            sdsnew("-NOJOB Job not known in the context of this node.\r\n"));
        return;
    }

    /* Don't allow to postpone jobs that have less than 50% of time to live
     * left, in order to prevent a worker from monopolizing a job for all its
     * lifetime. */
    mstime_t ttl = ((mstime_t)job->etime*1000) - (job->ctime/1000000);
    mstime_t elapsed = server.mstime - (job->ctime/1000000);
    if (ttl > 0 && elapsed > ttl/2) {
        addReplySds(c,
            sdsnew("-TOOLATE Half of job TTL already elapsed, "
                   "you are no longer allowed to postpone the "
                   "next delivery.\r\n"));
        return;
    }

    if (job->state == JOB_STATE_QUEUED) dequeueJob(job);
    job->flags |= JOB_FLAG_BCAST_WILLQUEUE;
    updateJobRequeueTime(job,server.mstime+
                         job->retry*1000+
                         randomTimeError(DISQUE_TIME_ERR));
    clusterBroadcastWorking(job);
    addReplyLongLong(c,job->retry);
}