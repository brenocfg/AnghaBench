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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int /*<<< orphan*/  clusterMsgDataJobID ;
typedef  int /*<<< orphan*/  clusterMsgDataFail ;
struct TYPE_8__ {char* sig; int /*<<< orphan*/  totlen; int /*<<< orphan*/  state; void* flags; void* port; int /*<<< orphan*/  sender; void* type; void* ver; } ;
typedef  TYPE_2__ clusterMsg ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int port; TYPE_1__* cluster; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int CLUSTERMSG_TYPE_DELJOB ; 
 int CLUSTERMSG_TYPE_ENQUEUE ; 
 int CLUSTERMSG_TYPE_FAIL ; 
 int CLUSTERMSG_TYPE_GOTACK ; 
 int CLUSTERMSG_TYPE_GOTJOB ; 
 int CLUSTERMSG_TYPE_QUEUED ; 
 int CLUSTERMSG_TYPE_SETACK ; 
 int CLUSTERMSG_TYPE_WILLQUEUE ; 
 int CLUSTERMSG_TYPE_WORKING ; 
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int CLUSTER_PROTO_VER ; 
 int /*<<< orphan*/  htonl (int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* myself ; 
 TYPE_3__ server ; 

void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
    int totlen = 0;

    memset(hdr,0,sizeof(*hdr));
    hdr->ver = htons(CLUSTER_PROTO_VER);
    hdr->sig[0] = 'D';
    hdr->sig[1] = 'b';
    hdr->sig[2] = 'u';
    hdr->sig[3] = 'Z';
    hdr->type = htons(type);
    memcpy(hdr->sender,myself->name,CLUSTER_NAMELEN);
    hdr->port = htons(server.port);
    hdr->flags = htons(myself->flags);
    hdr->state = server.cluster->state;

    /* Compute the message length for certain messages. For other messages
     * this is up to the caller. */
    if (type == CLUSTERMSG_TYPE_FAIL) {
        totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
        totlen += sizeof(clusterMsgDataFail);
    } else if (type == CLUSTERMSG_TYPE_GOTJOB ||
               type == CLUSTERMSG_TYPE_ENQUEUE ||
               type == CLUSTERMSG_TYPE_QUEUED ||
               type == CLUSTERMSG_TYPE_WORKING ||
               type == CLUSTERMSG_TYPE_SETACK ||
               type == CLUSTERMSG_TYPE_GOTACK ||
               type == CLUSTERMSG_TYPE_DELJOB ||
               type == CLUSTERMSG_TYPE_WILLQUEUE)
    {
        totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
        totlen += sizeof(clusterMsgDataJobID);
    }
    hdr->totlen = htonl(totlen);
    /* For PING, PONG, and MEET, fixing the totlen field is up to the caller. */
}