#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int uint32_t ;
struct TYPE_14__ {scalar_t__ ptr; } ;
typedef  TYPE_4__ robj ;
typedef  int /*<<< orphan*/  dict ;
typedef  int /*<<< orphan*/  clusterMsgDataQueueOp ;
struct TYPE_11__ {int /*<<< orphan*/  qname; void* qnamelen; void* aux; } ;
struct TYPE_12__ {TYPE_1__ about; } ;
struct TYPE_13__ {TYPE_2__ queueop; } ;
struct TYPE_15__ {void* totlen; TYPE_3__ data; } ;
typedef  TYPE_5__ clusterMsg ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_PAUSE ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterBroadcastMessage (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  zfree (TYPE_5__*) ; 
 TYPE_5__* zmalloc (int) ; 

void clusterSendPause(robj *qname, uint32_t flags, dict *nodes) {
    uint32_t totlen, qnamelen = sdslen(qname->ptr);
    uint32_t alloclen;
    clusterMsg *hdr;

    serverLog(LL_VERBOSE,"Sending PAUSE for %s flags=%d, %d nodes",
        (char*)qname->ptr, (int)flags, (int)dictSize(nodes));

    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += sizeof(clusterMsgDataQueueOp) - 8 + qnamelen;
    alloclen = totlen;
    if (alloclen < (int)sizeof(clusterMsg)) alloclen = sizeof(clusterMsg);
    hdr = zmalloc(alloclen);

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_PAUSE);
    hdr->data.queueop.about.aux = htonl(flags);
    hdr->data.queueop.about.qnamelen = htonl(qnamelen);
    memcpy(hdr->data.queueop.about.qname, qname->ptr, qnamelen);
    hdr->totlen = htonl(totlen);
    clusterBroadcastMessage(nodes,hdr,totlen);
    zfree(hdr);
}