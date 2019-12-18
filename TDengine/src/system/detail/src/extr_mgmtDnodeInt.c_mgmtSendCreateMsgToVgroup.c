#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int numOfVnodes; int /*<<< orphan*/  lastCreate; TYPE_1__* vnodeGid; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ SVgObj ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  int /*<<< orphan*/  SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_CREATE ; 
 char* mgmtBuildCreateMeterIe (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetDnode (int /*<<< orphan*/ ) ; 
 char* taosBuildReqMsgToDnodeWithSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosSendMsgToDnode (int /*<<< orphan*/ *,char*,int) ; 

int mgmtSendCreateMsgToVgroup(STabObj *pMeter, SVgObj *pVgroup) {
  char *     pMsg, *pStart;
  int        i, msgLen = 0;
  SDnodeObj *pObj;
  uint64_t   timeStamp;

  timeStamp = taosGetTimestampMs();

  for (i = 0; i < pVgroup->numOfVnodes; ++i) {
    //if (pVgroup->vnodeGid[i].ip == 0) continue;

    pObj = mgmtGetDnode(pVgroup->vnodeGid[i].ip);
    if (pObj == NULL) continue;

    pStart = taosBuildReqMsgToDnodeWithSize(pObj, TSDB_MSG_TYPE_CREATE, 64000);
    if (pStart == NULL) continue;
    pMsg = mgmtBuildCreateMeterIe(pMeter, pStart, pVgroup->vnodeGid[i].vnode);
    msgLen = pMsg - pStart;

    taosSendMsgToDnode(pObj, pStart, msgLen);
  }

  pVgroup->lastCreate = timeStamp;

  return 0;
}