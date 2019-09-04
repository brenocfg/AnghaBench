#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mstime_t ;
struct TYPE_5__ {scalar_t__ added_node_time; int /*<<< orphan*/  job; } ;
struct TYPE_6__ {int flags; scalar_t__ btype; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_7__ {scalar_t__ mstime; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_JOB_REPL ; 
 int CLIENT_BLOCKED ; 
 scalar_t__ DELAYED_JOB_ADD_NODE_MIN_PERIOD ; 
 scalar_t__ clusterReplicateJob (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mstime () ; 
 TYPE_3__ server ; 

int clientsCronHandleDelayedJobReplication(client *c) {
    /* Return ASAP if this client is not blocked for job replication. */
    if (!(c->flags & CLIENT_BLOCKED) || c->btype != BLOCKED_JOB_REPL)
        return 0;

    /* Note that clientsCronHandleDelayedJobReplication() is called after
     * refreshing server.mstime, so no need to call mstime() again here,
     * we can use the cached value. However we use a fresh timestamp if
     * we have to set added_node_time again. */
    mstime_t elapsed = server.mstime - c->bpop.added_node_time;
    if (elapsed >= DELAYED_JOB_ADD_NODE_MIN_PERIOD) {
        if (clusterReplicateJob(c->bpop.job, 1, 0) > 0)
            c->bpop.added_node_time = mstime();
    }
    return 0;
}