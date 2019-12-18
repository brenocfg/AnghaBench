#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_9__ {TYPE_1__* cluster; } ;
struct TYPE_7__ {scalar_t__ reachable_nodes_count; TYPE_2__** reachable_nodes; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int CLUSTER_NODE_FAIL ; 
 int CLUSTER_NODE_HANDSHAKE ; 
 int CLUSTER_NODE_LEAVING ; 
 int CLUSTER_NODE_MYSELF ; 
 int CLUSTER_NODE_PFAIL ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 TYPE_5__ server ; 
 TYPE_2__** zrealloc (TYPE_2__**,int) ; 

void clusterUpdateReachableNodes(void) {
    dictIterator *di;
    dictEntry *de;
    int maxsize = dictSize(server.cluster->nodes) * sizeof(clusterNode*);

    server.cluster->reachable_nodes =
        zrealloc(server.cluster->reachable_nodes,maxsize);
    server.cluster->reachable_nodes_count = 0;

    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (node->flags & (CLUSTER_NODE_MYSELF|
                           CLUSTER_NODE_HANDSHAKE|
                           CLUSTER_NODE_LEAVING|
                           CLUSTER_NODE_PFAIL|
                           CLUSTER_NODE_FAIL)) continue;
        server.cluster->reachable_nodes[server.cluster->reachable_nodes_count++]
            = node;
    }
    dictReleaseIterator(di);
}