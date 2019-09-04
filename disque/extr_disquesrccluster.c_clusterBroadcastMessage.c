#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int CLUSTER_NODE_HANDSHAKE ; 
 int CLUSTER_NODE_MYSELF ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ ,void*,size_t) ; 
 TYPE_1__* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 

void clusterBroadcastMessage(dict *nodes, void *buf, size_t len) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetKey(de);

        if (!node->link) continue;
        if (node->flags & (CLUSTER_NODE_MYSELF|CLUSTER_NODE_HANDSHAKE))
            continue;
        clusterSendMessage(node->link,buf,len);
    }
    dictReleaseIterator(di);
}