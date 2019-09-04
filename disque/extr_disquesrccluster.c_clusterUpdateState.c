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
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_7__ {TYPE_1__* cluster; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  nodes; int /*<<< orphan*/  todo_before_sleep; } ;

/* Variables and functions */
 int CLUSTER_NODE_HANDSHAKE ; 
 int /*<<< orphan*/  CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 

void clusterUpdateState(void) {
    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_UPDATE_STATE;

    /* Compute the cluster size, that is the number of nodes
     * actually partecipating to the cluster (so nodes in handshake
     * state are excluded).
     *
     * Disque does not use any quorum, so this is only useful in order to
     * mark node from PFAIL to FAIL when we have failure reports from
     * majority. The notion of failure is only used for optimizations,
     * for example if a node appears to be failing we don't try to send
     * it ACKs or replicate messages to it. */
    {
        dictIterator *di;
        dictEntry *de;

        server.cluster->size = 0;
        di = dictGetSafeIterator(server.cluster->nodes);
        while((de = dictNext(di)) != NULL) {
            clusterNode *node = dictGetVal(de);

            if (!(node->flags & CLUSTER_NODE_HANDSHAKE))
                server.cluster->size++;
        }
        dictReleaseIterator(di);
    }
}