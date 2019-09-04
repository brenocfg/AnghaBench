#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_18__ {int flags; scalar_t__ port; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ clusterNode ;
struct TYPE_19__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  nodename; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ clusterMsgDataGossip ;
struct TYPE_16__ {scalar_t__ gossip; } ;
struct TYPE_17__ {TYPE_1__ ping; } ;
struct TYPE_20__ {int /*<<< orphan*/  sender; TYPE_2__ data; int /*<<< orphan*/  count; } ;
typedef  TYPE_5__ clusterMsg ;
struct TYPE_21__ {TYPE_3__* node; } ;
typedef  TYPE_6__ clusterLink ;

/* Variables and functions */
 int CLUSTER_NODE_FAIL ; 
 int CLUSTER_NODE_NOADDR ; 
 int CLUSTER_NODE_PFAIL ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterBlacklistExists (int /*<<< orphan*/ ) ; 
 TYPE_3__* clusterLookupNode (int /*<<< orphan*/ ) ; 
 scalar_t__ clusterNodeAddFailureReport (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ clusterNodeDelFailureReport (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  clusterStartHandshake (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  markNodeAsFailingIfNeeded (TYPE_3__*) ; 
 TYPE_3__* myself ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  representClusterNodeFlags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
    uint16_t count = ntohs(hdr->count);
    clusterMsgDataGossip *g = (clusterMsgDataGossip*) hdr->data.ping.gossip;
    clusterNode *sender = link->node ? link->node : clusterLookupNode(hdr->sender);

    while(count--) {
        uint16_t flags = ntohs(g->flags);
        clusterNode *node;
        sds ci;

        ci = representClusterNodeFlags(sdsempty(), flags);
        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
            ci);
        sdsfree(ci);

        /* Update our state accordingly to the gossip sections */
        node = clusterLookupNode(g->nodename);
        if (node) {
            /* We already know this node. */
            if (sender && node != myself) {
                if (flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) {
                    if (clusterNodeAddFailureReport(node,sender)) {
                        serverLog(LL_VERBOSE,
                            "Node %.40s reported node %.40s as not reachable.",
                            sender->name, node->name);
                    }
                    markNodeAsFailingIfNeeded(node);
                } else {
                    if (clusterNodeDelFailureReport(node,sender)) {
                        serverLog(LL_VERBOSE,
                            "Node %.40s reported node %.40s is back online.",
                            sender->name, node->name);
                    }
                }
            }

            /* If we already know this node, but it is not reachable, and
             * we see a different address in the gossip section, start an
             * handshake with the (possibly) new address: this will result
             * into a node address update if the handshake will be
             * successful. */
            if (node->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL) &&
                (strcasecmp(node->ip,g->ip) || node->port != ntohs(g->port)))
            {
                clusterStartHandshake(g->ip,ntohs(g->port));
            }
        } else {
            /* If it's not in NOADDR state and we don't have it, we
             * start a handshake process against this IP/PORT pairs.
             *
             * Note that we require that the sender of this gossip message
             * is a well known node in our cluster, otherwise we risk
             * joining another cluster. */
            if (sender &&
                !(flags & CLUSTER_NODE_NOADDR) &&
                !clusterBlacklistExists(g->nodename))
            {
                clusterStartHandshake(g->ip,ntohs(g->port));
            }
        }

        /* Next node */
        g++;
    }
}