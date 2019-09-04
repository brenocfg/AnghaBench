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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_3__ {long long name; long long ip; char* port; int flags; scalar_t__ link; scalar_t__ pong_received; scalar_t__ ping_sent; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int CLUSTER_NODE_MYSELF ; 
 int /*<<< orphan*/  representClusterNodeFlags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,long long,long long,char*) ; 
 int /*<<< orphan*/  sdsempty () ; 

sds clusterGenNodeDescription(clusterNode *node) {
    sds ci;

    /* Node coordinates */
    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
        node->name,
        node->ip,
        node->port);

    /* Flags */
    ci = representClusterNodeFlags(ci, node->flags);

    /* Latency from the POV of this node, link status */
    ci = sdscatprintf(ci," %lld %lld %s",
        (long long) node->ping_sent,
        (long long) node->pong_received,
        (node->link || node->flags & CLUSTER_NODE_MYSELF) ?
                    "connected" : "disconnected");

    return ci;
}