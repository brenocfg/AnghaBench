#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ delay; int /*<<< orphan*/ * nodes_confirmed; int /*<<< orphan*/  nodes_delivered; int /*<<< orphan*/  state; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  clusterNode ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOFLoadJob (TYPE_1__*) ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  JOB_STATE_ACTIVE ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  addReplyJobID (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  clusterSendEnqueue (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueueJob (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeJob (TYPE_1__*) ; 
 int /*<<< orphan*/ * jobGetAssociatedValue (TYPE_1__*) ; 
 TYPE_5__* myself ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setJobAssociatedValue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unblockClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregisterJob (TYPE_1__*) ; 
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_1__*,int /*<<< orphan*/ ) ; 

int jobReplicationAchieved(job *j) {
    serverLog(LL_VERBOSE,"Replication ACHIEVED %.*s",JOB_ID_LEN,j->id);

    /* Change the job state to active. This is critical to avoid the job
     * will be freed by unblockClient() if found still in the old state. */
    j->state = JOB_STATE_ACTIVE;

    /* Reply to the blocked client with the Job ID and unblock the client. */
    client *c = jobGetAssociatedValue(j);
    setJobAssociatedValue(j,NULL);
    addReplyJobID(c,j);
    unblockClient(c);

    /* If the job was externally replicated, send a QUEUE message to one of
     * the nodes that acknowledged to have a copy, and forget about it ASAP. */
    if (dictFind(j->nodes_delivered,myself->name) == NULL) {
        dictEntry *de = dictGetRandomKey(j->nodes_confirmed);
        if (de) {
            clusterNode *n = dictGetVal(de);
            clusterSendEnqueue(n,j,j->delay);
        }
        unregisterJob(j);
        freeJob(j);
        return C_ERR;
    }

    /* If set, cleanup nodes_confirmed to free memory. We'll reuse this
     * hash table again for ACKs tracking in order to garbage collect the
     * job once processed. */
    if (j->nodes_confirmed) {
        dictRelease(j->nodes_confirmed);
        j->nodes_confirmed = NULL;
    }

    /* Queue the job locally. */
    if (j->delay == 0)
        enqueueJob(j,0); /* Will change the job state. */
    else
        updateJobAwakeTime(j,0); /* Queue with delay. */

    AOFLoadJob(j);
    return C_OK;
}