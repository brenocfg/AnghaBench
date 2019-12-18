#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* int32_t ;
struct TYPE_13__ {int numOfVnodes; int /*<<< orphan*/  privateIp; TYPE_1__* vload; } ;
struct TYPE_12__ {int vnode; int sid; } ;
struct TYPE_11__ {int /*<<< orphan*/ ** meterList; } ;
struct TYPE_10__ {int vgId; } ;
typedef  TYPE_2__ SVgObj ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  TYPE_3__ SMeterCfgMsg ;
typedef  TYPE_4__ SDnodeObj ;

/* Variables and functions */
 char TSDB_CODE_INVALID_METER_ID ; 
 int /*<<< orphan*/  TSDB_CODE_SERV_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_METER_CFG_RSP ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int,int) ; 
 char* mgmtBuildCreateMeterIe (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__* mgmtGetVgroup (int) ; 
 char* taosBuildRspMsgToDnodeWithSize (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendMsgToDnode (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  taosSendSimpleRspToDnode (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgmtProcessMeterCfgMsg(char *cont, int contLen, SDnodeObj *pObj) {
  char *        pMsg, *pStart;
  int           msgLen = 0;
  STabObj *     pMeter = NULL;
  SMeterCfgMsg *pCfg = (SMeterCfgMsg *)cont;
  SVgObj *      pVgroup;

  int vnode = htonl(pCfg->vnode);
  int sid = htonl(pCfg->sid);

  pStart = taosBuildRspMsgToDnodeWithSize(pObj, TSDB_MSG_TYPE_METER_CFG_RSP, 64000);
  if (pStart == NULL) {
    taosSendSimpleRspToDnode(pObj, TSDB_MSG_TYPE_METER_CFG_RSP, TSDB_CODE_SERV_OUT_OF_MEMORY);
    return 0;
  }
  pMsg = pStart;

  if (vnode < pObj->numOfVnodes) {
    int vgId = pObj->vload[vnode].vgId;

    pVgroup = mgmtGetVgroup(vgId);
    if (pVgroup) pMeter = pVgroup->meterList[sid];
  }

  if (pMeter) {
    *pMsg = 0;  // code
    pMsg++;
    pMsg = mgmtBuildCreateMeterIe(pMeter, pMsg, vnode);
  } else {
    mTrace("dnode:%s, vnode:%d sid:%d, meter not there", taosIpStr(pObj->privateIp), vnode, sid);
    *pMsg = TSDB_CODE_INVALID_METER_ID;
    pMsg++;

    *(int32_t *)pMsg = htonl(vnode);
    pMsg += sizeof(int32_t);
    *(int32_t *)pMsg = htonl(sid);
    pMsg += sizeof(int32_t);
  }

  msgLen = pMsg - pStart;
  taosSendMsgToDnode(pObj, pStart, msgLen);

  return 0;
}