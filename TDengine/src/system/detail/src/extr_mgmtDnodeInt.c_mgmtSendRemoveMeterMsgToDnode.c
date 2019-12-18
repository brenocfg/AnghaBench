#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_17__ {int /*<<< orphan*/  status; } ;
struct TYPE_16__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_13__ {int /*<<< orphan*/  sid; } ;
struct TYPE_15__ {TYPE_2__ gid; int /*<<< orphan*/  meterId; } ;
struct TYPE_14__ {int numOfVnodes; int /*<<< orphan*/  lastRemove; TYPE_1__* vnodeGid; } ;
struct TYPE_12__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ STabObj ;
typedef  TYPE_5__ SRemoveMeterMsg ;
typedef  TYPE_6__ SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_REMOVE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 char* taosBuildReqMsgToDnode (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosSendMsgToDnode (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  tinet_ntoa (char*,int /*<<< orphan*/ ) ; 

int mgmtSendRemoveMeterMsgToDnode(STabObj *pMeter, SVgObj *pVgroup) {
  SRemoveMeterMsg *pRemove;
  char *           pMsg, *pStart;
  int              i, msgLen = 0;
  SDnodeObj *      pObj;
  char             ipstr[20];
  uint64_t         timeStamp;

  timeStamp = taosGetTimestampMs();

  for (i = 0; i < pVgroup->numOfVnodes; ++i) {
    //if (pVgroup->vnodeGid[i].ip == 0) continue;

    pObj = mgmtGetDnode(pVgroup->vnodeGid[i].ip);
    if (pObj == NULL) continue;

    pStart = taosBuildReqMsgToDnode(pObj, TSDB_MSG_TYPE_REMOVE);
    if (pStart == NULL) continue;
    pMsg = pStart;

    pRemove = (SRemoveMeterMsg *)pMsg;
    pRemove->vnode = htons(pVgroup->vnodeGid[i].vnode);
    pRemove->sid = htonl(pMeter->gid.sid);
    memcpy(pRemove->meterId, pMeter->meterId, TSDB_METER_ID_LEN);

    pMsg += sizeof(SRemoveMeterMsg);
    msgLen = pMsg - pStart;

    taosSendMsgToDnode(pObj, pStart, msgLen);

    tinet_ntoa(ipstr, pVgroup->vnodeGid[i].ip);
    mTrace("dnode:%s vid:%d, send remove meter msg, sid:%d status:%d", ipstr, pVgroup->vnodeGid[i].vnode,
           pMeter->gid.sid, pObj->status);
  }

  pVgroup->lastRemove = timeStamp;

  return 0;
}