#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint32_t ;
struct TYPE_8__ {int needjobs_bcast_attempt; void* needjobs_bcast_time; int needjobs_adhoc_attempt; void* needjobs_adhoc_time; int /*<<< orphan*/  needjobs_responders; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ queue ;
typedef  void* mstime_t ;
struct TYPE_9__ {TYPE_1__* cluster; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 void* NEEDJOBS_BCAST_ADHOC_MAX_DELAY ; 
 int NEEDJOBS_BCAST_ADHOC_MIN_DELAY ; 
 void* NEEDJOBS_BCAST_ALL_MAX_DELAY ; 
 int NEEDJOBS_BCAST_ALL_MIN_DELAY ; 
 unsigned long NEEDJOBS_MAX_REQUEST ; 
 unsigned long NEEDJOBS_MIN_REQUEST ; 
 int NEEDJOBS_REACHED_ZERO ; 
 int /*<<< orphan*/  clusterSendNeedJobs (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long getQueueImportRate (TYPE_2__*) ; 
 unsigned long getQueueValidResponders (TYPE_2__*) ; 
 void* mstime () ; 
 scalar_t__ myselfLeaving () ; 
 TYPE_3__ server ; 

void needJobsForQueue(queue *q, int type) {
    uint32_t import_per_sec; /* Jobs import rate in the latest secs. */
    uint32_t to_fetch;       /* Number of jobs we should try to obtain. */
    unsigned long num_responders = 0;
    mstime_t bcast_delay, adhoc_delay;
    mstime_t now = mstime();

    /* Don't ask for jobs if we are leaving the cluster. */
    if (myselfLeaving()) return;

    import_per_sec = getQueueImportRate(q);

    /* When called with NEEDJOBS_REACHED_ZERO, we have to do something only
     * if there is some active traffic, in order to improve latency.
     * Otherwise we wait for the first client to block, that will trigger
     * a new call to this function, but with NEEDJOBS_CLIENTS_WAITING type. */
    if (type == NEEDJOBS_REACHED_ZERO && import_per_sec == 0) return;

    /* Guess how many replies we need from each node. If we already have
     * a list of sources, assume that each source is capable of providing
     * some message. */
    num_responders = getQueueValidResponders(q);
    to_fetch = NEEDJOBS_MIN_REQUEST;
    if (num_responders > 0)
        to_fetch = import_per_sec / num_responders;

    /* Trim number of jobs to request to min/max values. */
    if (to_fetch < NEEDJOBS_MIN_REQUEST) to_fetch = NEEDJOBS_MIN_REQUEST;
    else if (to_fetch > NEEDJOBS_MAX_REQUEST) to_fetch = NEEDJOBS_MAX_REQUEST;

    /* Broadcast the message cluster from time to time.
     * We use exponential intervals (with a max time limit) */
    bcast_delay = NEEDJOBS_BCAST_ALL_MIN_DELAY *
                  (1 << q->needjobs_bcast_attempt);
    if (bcast_delay > NEEDJOBS_BCAST_ALL_MAX_DELAY)
        bcast_delay = NEEDJOBS_BCAST_ALL_MAX_DELAY;

    if (now - q->needjobs_bcast_time > bcast_delay) {
        q->needjobs_bcast_time = now;
        q->needjobs_bcast_attempt++;
        /* Cluster-wide broadcasts are just to discover nodes,
         * ask for a single job in this case. */
        clusterSendNeedJobs(q->name,1,server.cluster->nodes);
    }

    /* If the queue reached zero, or if the delay elapsed and we
     * have at least a source node, send an ad-hoc message to
     * nodes known to be sources for this queue.
     *
     * We use exponential delays here as well (but don't care about
     * the delay if the queue just dropped to zero), however with
     * much shorter times compared to the cluster-wide broadcast. */
    adhoc_delay = NEEDJOBS_BCAST_ADHOC_MIN_DELAY *
                  (1 << q->needjobs_adhoc_attempt);
    if (adhoc_delay > NEEDJOBS_BCAST_ADHOC_MAX_DELAY)
        adhoc_delay = NEEDJOBS_BCAST_ADHOC_MAX_DELAY;

    if ((type == NEEDJOBS_REACHED_ZERO ||
         now - q->needjobs_adhoc_time > adhoc_delay) &&
         num_responders > 0)
    {
        q->needjobs_adhoc_time = now;
        q->needjobs_adhoc_attempt++;
        clusterSendNeedJobs(q->name,to_fetch,q->needjobs_responders);
    }
}