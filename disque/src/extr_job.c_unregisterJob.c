#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ state; int /*<<< orphan*/  id; scalar_t__ awakeme; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_12__ {int /*<<< orphan*/  jobs; int /*<<< orphan*/  awakeme; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOFDelJob (TYPE_1__*) ; 
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ JOB_STATE_ACKED ; 
 scalar_t__ JOB_STATE_ACTIVE ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 scalar_t__ JOB_STATE_WAIT_REPL ; 
 int /*<<< orphan*/  addReplySds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBroadcastDelJob (TYPE_1__*) ; 
 int /*<<< orphan*/  dequeueJob (TYPE_1__*) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jobGetAssociatedValue (TYPE_1__*) ; 
 TYPE_1__* lookupJob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setJobAssociatedValue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skiplistDelete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  unblockClient (int /*<<< orphan*/ *) ; 

int unregisterJob(job *j) {
    j = lookupJob(j->id);
    if (!j) return C_ERR;

    /* Emit a DELJOB command for all the job states but WAITREPL (no
     * ADDJOB emitted yer), and ACKED (DELJOB already emitted). */
    if (j->state >= JOB_STATE_ACTIVE && j->state != JOB_STATE_ACKED)
        AOFDelJob(j);

    /* Remove from awake skip list. */
    if (j->awakeme) serverAssert(skiplistDelete(server.awakeme,j));

    /* If the job is queued, remove from queue. */
    if (j->state == JOB_STATE_QUEUED) dequeueJob(j);

    /* If there is a client blocked for this job, inform it that the job
     * got deleted, and unblock it. This should only happen when the job
     * gets expired before the requested replication level is reached. */
    if (j->state == JOB_STATE_WAIT_REPL) {
        client *c = jobGetAssociatedValue(j);
        setJobAssociatedValue(j,NULL);
        addReplySds(c,
            sdsnew("-NOREPL job removed (expired?) before the requested "
                   "replication level was achieved\r\n"));
        /* Change job state otherwise unblockClientWaitingJobRepl() will
         * try to remove the job itself. */
        j->state = JOB_STATE_ACTIVE;
        clusterBroadcastDelJob(j);
        unblockClient(c);
    }

    /* Remove the job from the jobs hash table. */
    dictDelete(server.jobs, j->id);
    return C_OK;
}