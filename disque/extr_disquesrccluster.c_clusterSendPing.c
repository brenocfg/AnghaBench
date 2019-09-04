#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_19__ {int flags; int ping_sent; int pong_received; int port; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; int /*<<< orphan*/ * link; } ;
typedef  TYPE_5__ clusterNode ;
struct TYPE_20__ {scalar_t__ notused2; scalar_t__ notused1; void* flags; void* port; int /*<<< orphan*/  ip; void* pong_received; void* ping_sent; int /*<<< orphan*/  nodename; } ;
typedef  TYPE_6__ clusterMsgDataGossip ;
struct TYPE_17__ {TYPE_6__* gossip; } ;
struct TYPE_18__ {TYPE_3__ ping; } ;
struct TYPE_21__ {void* totlen; void* count; TYPE_4__ data; } ;
typedef  TYPE_7__ clusterMsg ;
struct TYPE_22__ {TYPE_1__* node; } ;
typedef  TYPE_8__ clusterLink ;
struct TYPE_23__ {TYPE_2__* cluster; } ;
struct TYPE_16__ {int /*<<< orphan*/  nodes; } ;
struct TYPE_15__ {int /*<<< orphan*/  ping_sent; } ;

/* Variables and functions */
 int CLUSTERMSG_TYPE_PING ; 
 int CLUSTER_NAMELEN ; 
 int CLUSTER_NODE_FAIL ; 
 int CLUSTER_NODE_HANDSHAKE ; 
 int CLUSTER_NODE_NOADDR ; 
 int CLUSTER_NODE_PFAIL ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_7__*,int) ; 
 int /*<<< orphan*/  clusterSendMessage (TYPE_8__*,unsigned char*,int) ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ ) ; 
 TYPE_5__* dictGetVal (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 int floor (int) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mstime () ; 
 TYPE_5__* myself ; 
 TYPE_9__ server ; 
 unsigned char* zcalloc (int) ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 

void clusterSendPing(clusterLink *link, int type) {
    unsigned char *buf;
    clusterMsg *hdr;
    int gossipcount = 0; /* Number of gossip sections added so far. */
    int wanted; /* Number of gossip sections we want to append if possible. */
    int totlen; /* Total packet length. */
    /* freshnodes is the max number of nodes we can hope to append at all:
     * nodes available minus two (ourself and the node we are sending the
     * message to). However practically there may be less valid nodes since
     * nodes in handshake state, disconnected, are not considered. */
    int freshnodes = dictSize(server.cluster->nodes)-2;

    /* How many gossip sections we want to add? 1/10 of the number of nodes
     * and anyway at least 3. Why 1/10?
     *
     * If we have N masters, with N/10 entries, and we consider that in
     * node_timeout we exchange with each other node at least 4 packets
     * (we ping in the worst case in node_timeout/2 time, and we also
     * receive two pings from the host), we have a total of 8 packets
     * in the node_timeout*2 falure reports validity time. So we have
     * that, for a single PFAIL node, we can expect to receive the following
     * number of failure reports (in the specified window of time):
     *
     * PROB * GOSSIP_ENTRIES_PER_PACKET * TOTAL_PACKETS:
     *
     * PROB = probability of being featured in a single gossip entry,
     *        which is 1 / NUM_OF_NODES.
     * ENTRIES = 10.
     * TOTAL_PACKETS = 2 * 4 * NUM_OF_MASTERS.
     *
     * If we assume we have just masters (so num of nodes and num of masters
     * is the same), with 1/10 we always get over the majority, and specifically
     * 80% of the number of nodes, to account for many masters failing at the
     * same time.
     *
     * Since we have non-voting slaves that lower the probability of an entry
     * to feature our node, we set the number of entires per packet as
     * 10% of the total nodes we have. */
    wanted = floor(dictSize(server.cluster->nodes)/10);
    if (wanted < 3) wanted = 3;
    if (wanted > freshnodes) wanted = freshnodes;

    /* Compute the maxium totlen to allocate our buffer. We'll fix the totlen
     * later according to the number of gossip sections we really were able
     * to put inside the packet. */
    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += (sizeof(clusterMsgDataGossip)*wanted);
    /* Note: clusterBuildMessageHdr() expects the buffer to be always at least
     * sizeof(clusterMsg) or more. */
    if (totlen < (int)sizeof(clusterMsg)) totlen = sizeof(clusterMsg);
    buf = zcalloc(totlen);
    hdr = (clusterMsg*) buf;

    /* Populate the header. */
    if (link->node && type == CLUSTERMSG_TYPE_PING)
        link->node->ping_sent = mstime();
    clusterBuildMessageHdr(hdr,type);

    /* Populate the gossip fields */
    int maxiterations = wanted*3;
    while(freshnodes > 0 && gossipcount < wanted && maxiterations--) {
        dictEntry *de = dictGetRandomKey(server.cluster->nodes);
        clusterNode *this = dictGetVal(de);
        clusterMsgDataGossip *gossip;
        int j;

        /* Don't include this node: the whole packet header is about us
         * already, so we just gossip about other nodes. */
        if (this == myself) continue;

        /* Give a bias to FAIL/PFAIL nodes. */
        if (maxiterations > wanted*2 &&
            !(this->flags & (CLUSTER_NODE_PFAIL|CLUSTER_NODE_FAIL)))
            continue;

        /* In the gossip section don't include:
         * 1) Nodes in HANDSHAKE state.
         * 3) Nodes with the NOADDR flag set.
         * 4) Disconnected nodes if they don't have configured slots.
         */
        if (this->flags & (CLUSTER_NODE_HANDSHAKE|CLUSTER_NODE_NOADDR) ||
            this->link == NULL)
        {
            freshnodes--; /* Tecnically not correct, but saves CPU. */
            continue;
        }

        /* Check if we already added this node */
        for (j = 0; j < gossipcount; j++) {
            if (memcmp(hdr->data.ping.gossip[j].nodename,this->name,
                    CLUSTER_NAMELEN) == 0) break;
        }
        if (j != gossipcount) continue;

        /* Add it */
        freshnodes--;
        gossip = &(hdr->data.ping.gossip[gossipcount]);
        memcpy(gossip->nodename,this->name,CLUSTER_NAMELEN);
        gossip->ping_sent = htonl(this->ping_sent);
        gossip->pong_received = htonl(this->pong_received);
        memcpy(gossip->ip,this->ip,sizeof(this->ip));
        gossip->port = htons(this->port);
        gossip->flags = htons(this->flags);
        gossip->notused1 = 0;
        gossip->notused2 = 0;
        gossipcount++;
    }

    /* Ready to send... fix the totlen field and queue the message in the
     * output buffer. */
    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += (sizeof(clusterMsgDataGossip)*gossipcount);
    hdr->count = htons(gossipcount);
    hdr->totlen = htonl(totlen);
    clusterSendMessage(link,buf,totlen);
    zfree(buf);
}