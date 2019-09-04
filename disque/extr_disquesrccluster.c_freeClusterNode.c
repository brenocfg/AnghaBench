#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  fail_reports; scalar_t__ link; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_10__ {TYPE_1__* cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  deleted_nodes; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NODE_DELETED ; 
 scalar_t__ DICT_OK ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClusterLink (scalar_t__) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 scalar_t__ nodeInHandshake (TYPE_2__*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClusterNode(clusterNode *n) {
    serverAssert(dictDelete(server.cluster->nodes,n->name) == DICT_OK);
    if (n->link) freeClusterLink(n->link);
    /* We can free nodes in handshake state, but we can't free nodes
     * that were part of the cluster: they may still be referenced
     * by jobs. */
    if (nodeInHandshake(n)) {
        listRelease(n->fail_reports);
        zfree(n);
    } else {
        dictAdd(server.cluster->deleted_nodes,n->name,n);
        n->flags |= CLUSTER_NODE_DELETED;
    }
}