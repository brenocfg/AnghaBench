#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * link; } ;
typedef  TYPE_4__ clusterNode ;
struct TYPE_10__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_3__ job; } ;
struct TYPE_9__ {TYPE_1__ jobid; } ;
struct TYPE_12__ {int /*<<< orphan*/  totlen; TYPE_2__ data; } ;
typedef  TYPE_5__ clusterMsg ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_5__*,int) ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void clusterSendJobIDMessage(int type, clusterNode *node, char *id, int aux) {
    unsigned char buf[sizeof(clusterMsg)];
    clusterMsg *hdr = (clusterMsg*) buf;

    if (node->link == NULL) return; /* This is a best effort message. */
    clusterBuildMessageHdr(hdr,type);
    memcpy(hdr->data.jobid.job.id,id,JOB_ID_LEN);
    hdr->data.jobid.job.aux = htonl(aux);
    clusterSendMessage(node->link,buf,ntohl(hdr->totlen));
}