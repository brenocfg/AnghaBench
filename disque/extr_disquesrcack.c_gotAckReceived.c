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
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  id; scalar_t__ nodes_delivered; scalar_t__ nodes_confirmed; } ;
typedef  TYPE_2__ job ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ clusterNode ;
struct TYPE_14__ {TYPE_1__* cluster; } ;
struct TYPE_11__ {scalar_t__ nodes; } ;

/* Variables and functions */
 scalar_t__ JOB_STATE_ACKED ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterBroadcastDelJob (TYPE_2__*) ; 
 int /*<<< orphan*/  dictAdd (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * dictFind (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dictSize (scalar_t__) ; 
 int /*<<< orphan*/  freeJob (TYPE_2__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  unregisterJob (TYPE_2__*) ; 

void gotAckReceived(clusterNode *sender, job *job, int known) {
    /* A dummy ACK is an acknowledged job that we created just becakse a client
     * send us ACKJOB about a job we were not aware. */
    int dummy_ack = dictSize(job->nodes_delivered) == 0;

    serverLog(LL_VERBOSE,"RECEIVED GOTACK FROM %.40s FOR JOB %.48s",
        sender->name, job->id);

    /* We should never receive a GOTACK for a job which is not acknowledged,
     * but it is more robust to handle it explicitly. */
    if (job->state != JOB_STATE_ACKED) return;

    /* If this is a dummy ACK, and we reached a node that knows about this job,
     * it's up to it to perform the garbage collection, so we can forget about
     * this job and reclaim memory. */
    if (dummy_ack && known) {
        serverLog(LL_VERBOSE,"Deleting %.48s: authoritative node reached",
            job->id);
        unregisterJob(job);
        freeJob(job);
        return;
    }

    /* If the sender knows about the job, or if we have the sender in the list
     * of nodes that may have the job (even if it no longer remembers about
     * the job), we do two things:
     *
     * 1) Add the node to the list of nodes_delivered. It is likely already
     *    there... so this should be useless, but is a good invariant
     *    to enforce.
     * 2) Add the node to the list of nodes that acknowledged the ACK. */
    if (known || dictFind(job->nodes_delivered,sender->name) != NULL) {
        dictAdd(job->nodes_delivered,sender->name,sender);
        /* job->nodes_confirmed exists if we started a job garbage collection,
         * but we may receive GOTACK messages in other conditions sometimes,
         * since we reply with SETACK to QUEUED and WILLQUEUE if the job is
         * acknowledged but we did not yet started to GC. So we need to test
         * if the hash table actually exists. */
        if (job->nodes_confirmed)
            dictAdd(job->nodes_confirmed,sender->name,sender);
    }

    /* If our job is actually a dummy ACK, we are still interested to collect
     * all the nodes in the cluster that reported they don't have a clue:
     * eventually if everybody in the cluster has no clue, we can safely remove
     * the dummy ACK. */
    if (!known && dummy_ack) {
        dictAdd(job->nodes_confirmed,sender->name,sender);
        if (dictSize(job->nodes_confirmed) >= dictSize(server.cluster->nodes))
        {
            serverLog(LL_VERBOSE,
                "Deleting %.48s: dummy ACK not known cluster-wide",
                job->id);
            unregisterJob(job);
            freeJob(job);
            return;
        }
    }

    /* Finally the common case: our SETACK reached everybody. Broadcast
     * a DELJOB to all the nodes involved, and delete the job. */
    if (!dummy_ack && job->nodes_confirmed &&
         dictSize(job->nodes_confirmed) >= dictSize(job->nodes_delivered))
    {
        serverLog(LL_VERBOSE,
            "Deleting %.48s: All nodes involved acknowledged the job",
            job->id);
        clusterBroadcastDelJob(job);
        unregisterJob(job);
        freeJob(job);
        return;
    }
}