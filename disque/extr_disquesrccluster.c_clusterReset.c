#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_10__ {TYPE_1__* cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int CLUSTER_TODO_FSYNC_CONFIG ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  clusterAddNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterDelNode (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int /*<<< orphan*/  clusterUpdateReachableNodes () ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flushServerData () ; 
 int /*<<< orphan*/  getRandomHexChars (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* myself ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 

void clusterReset(int hard) {
    dictIterator *di;
    dictEntry *de;

    /* Forget all the nodes, but myself. */
    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (node == myself) continue;
        clusterDelNode(node);
    }
    dictReleaseIterator(di);

    /* Information about reachable nodes is no longer valid. Update it. */
    clusterUpdateReachableNodes();

    /* Hard reset only: change node ID. */
    if (hard) {
        sds oldname;

        /* To change the Node ID we need to remove the old name from the
         * nodes table, change the ID, and re-add back with new name. */
        oldname = sdsnewlen(myself->name, CLUSTER_NAMELEN);
        dictDelete(server.cluster->nodes,oldname);
        sdsfree(oldname);
        getRandomHexChars(myself->name, CLUSTER_NAMELEN);
        clusterAddNode(myself);
    }

    flushServerData();

    /* TODO: flush the deleted nodes hash table and the deleted nodes
     * entries. There are no longer jobs or queues that may reference
     * them. */

    /* Make sure to persist the new config and update the state. */
    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                         CLUSTER_TODO_UPDATE_STATE|
                         CLUSTER_TODO_FSYNC_CONFIG);
}