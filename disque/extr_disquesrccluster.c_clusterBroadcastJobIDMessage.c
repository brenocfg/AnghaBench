#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_12__ {scalar_t__ link; } ;
typedef  TYPE_4__ clusterNode ;
struct TYPE_9__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ job; } ;
struct TYPE_11__ {TYPE_2__ jobid; } ;
struct TYPE_13__ {unsigned char* mflags; int /*<<< orphan*/  totlen; TYPE_3__ data; } ;
typedef  TYPE_5__ clusterMsg ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_5__*,int) ; 
 int /*<<< orphan*/  clusterSendMessage (scalar_t__,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 TYPE_4__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* myself ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void clusterBroadcastJobIDMessage(dict *nodes, char *id, int type, uint32_t aux, unsigned char flags) {
    dictIterator *di = dictGetIterator(nodes);
    dictEntry *de;
    unsigned char buf[sizeof(clusterMsg)];
    clusterMsg *hdr = (clusterMsg*) buf;

    /* Build the message one time, send the same to everybody. */
    clusterBuildMessageHdr(hdr,type);
    memcpy(hdr->data.jobid.job.id,id,JOB_ID_LEN);
    hdr->data.jobid.job.aux = htonl(aux);
    hdr->mflags[0] = flags;

    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);
        if (node == myself) continue;
        if (node->link)
            clusterSendMessage(node->link,buf,ntohl(hdr->totlen));
    }
    dictReleaseIterator(di);
}