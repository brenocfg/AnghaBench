#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int uint32_t ;
typedef  unsigned char* sds ;
struct TYPE_20__ {scalar_t__ nodes_confirmed; int /*<<< orphan*/  nodes_delivered; } ;
typedef  TYPE_5__ job ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_21__ {int /*<<< orphan*/ * link; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ clusterNode ;
typedef  int /*<<< orphan*/  clusterMsgDataJob ;
struct TYPE_17__ {unsigned char* jobs_data; void* datasize; void* numjobs; } ;
struct TYPE_18__ {TYPE_2__ serialized; } ;
struct TYPE_19__ {TYPE_3__ jobs; } ;
struct TYPE_22__ {int /*<<< orphan*/ * mflags; TYPE_4__ data; void* totlen; } ;
typedef  TYPE_7__ clusterMsg ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_23__ {TYPE_1__* cluster; } ;
struct TYPE_16__ {int reachable_nodes_count; TYPE_6__** reachable_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_FLAG0_NOREPLY ; 
 int /*<<< orphan*/  CLUSTERMSG_TYPE_REPLJOB ; 
 scalar_t__ DICT_OK ; 
 int /*<<< orphan*/  SER_MESSAGE ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  clusterShuffleReachableNodes () ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ dictFind (scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_6__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 TYPE_6__* myself ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (unsigned char*) ; 
 int sdslen (unsigned char*) ; 
 unsigned char* serializeJob (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 unsigned char* zmalloc (int) ; 

int clusterReplicateJob(job *j, int repl, int noreply) {
    int i, added = 0;

    if (repl <= 0) return 0;

    /* Add the specified number of nodes to the list of receivers. */
    clusterShuffleReachableNodes();
    for (i = 0; i < server.cluster->reachable_nodes_count; i++) {
        clusterNode *node = server.cluster->reachable_nodes[i];

        if (node->link == NULL) continue; /* No link, no party... */
        if (dictAdd(j->nodes_delivered,node->name,node) == DICT_OK) {
            /* Only counts non-duplicated nodes. */
            added++;
            if (--repl == 0) break;
        }
    }

    /* Resend the message to all the past and new nodes. */
    unsigned char buf[sizeof(clusterMsg)], *payload;
    clusterMsg *hdr = (clusterMsg*) buf;
    uint32_t totlen;

    sds serialized = serializeJob(sdsempty(),j,SER_MESSAGE);

    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += sizeof(clusterMsgDataJob) -
              sizeof(hdr->data.jobs.serialized.jobs_data) +
              sdslen(serialized);

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_REPLJOB);
    hdr->data.jobs.serialized.numjobs = htonl(1);
    hdr->data.jobs.serialized.datasize = htonl(sdslen(serialized));
    hdr->totlen = htonl(totlen);

    if (totlen < sizeof(buf)) {
        payload = buf;
    } else {
        payload = zmalloc(totlen);
        memcpy(payload,buf,sizeof(clusterMsg));
        hdr = (clusterMsg*) payload;
    }
    memcpy(hdr->data.jobs.serialized.jobs_data,serialized,sdslen(serialized));
    sdsfree(serialized);

    /* Actual delivery of the message to the list of nodes. */
    dictIterator *di = dictGetIterator(j->nodes_delivered);
    dictEntry *de;

    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);
        if (node == myself) continue;

        /* We ask for reply only if 'noreply' is false and the target node
         * did not already replied with GOTJOB. */
        int acked = j->nodes_confirmed && dictFind(j->nodes_confirmed,node);
        if (noreply || acked) {
            hdr->mflags[0] |= CLUSTERMSG_FLAG0_NOREPLY;
        } else {
            hdr->mflags[0] &= ~CLUSTERMSG_FLAG0_NOREPLY;
        }

        /* If the target node acknowledged the message already, send it again
         * only if there are additional nodes. We want the target node to refresh
         * its list of receivers. */
        if (node->link && !(acked && added == 0))
            clusterSendMessage(node->link,payload,totlen);
    }
    dictReleaseIterator(di);

    if (payload != buf) zfree(payload);
    return added;
}