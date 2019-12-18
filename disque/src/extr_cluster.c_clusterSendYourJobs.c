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
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int uint32_t ;
typedef  unsigned char* sds ;
typedef  int /*<<< orphan*/  job ;
struct TYPE_11__ {int /*<<< orphan*/  link; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ clusterNode ;
typedef  int /*<<< orphan*/  clusterMsgDataJob ;
struct TYPE_8__ {unsigned char* jobs_data; void* datasize; void* numjobs; } ;
struct TYPE_9__ {TYPE_1__ serialized; } ;
struct TYPE_10__ {TYPE_2__ jobs; } ;
struct TYPE_12__ {TYPE_3__ data; void* totlen; } ;
typedef  TYPE_5__ clusterMsg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_YOURJOBS ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  SER_MESSAGE ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterSendMessage (int /*<<< orphan*/ ,unsigned char*,int) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (unsigned char*) ; 
 int sdslen (unsigned char*) ; 
 unsigned char* serializeJob (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 unsigned char* zmalloc (int) ; 

void clusterSendYourJobs(clusterNode *node, job **jobs, uint32_t count) {
    unsigned char buf[sizeof(clusterMsg)], *payload;
    clusterMsg *hdr = (clusterMsg*) buf;
    uint32_t totlen, j;

    if (!node->link) return;

    serverLog(LL_VERBOSE,"Sending %d jobs to %.40s", (int)count,node->name);

    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    totlen += sizeof(clusterMsgDataJob) -
              sizeof(hdr->data.jobs.serialized.jobs_data);

    sds serialized = sdsempty();
    for (j = 0; j < count; j++)
        serialized = serializeJob(serialized,jobs[j],SER_MESSAGE);
    totlen += sdslen(serialized);

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_YOURJOBS);
    hdr->data.jobs.serialized.numjobs = htonl(count);
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
    clusterSendMessage(node->link,payload,totlen);
    if (payload != buf) zfree(payload);
}