#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* sid; void* vnode; } ;
typedef  int /*<<< orphan*/  SMgmtObj ;
typedef  TYPE_1__ SMeterCfgMsg ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_METER_CFG ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  mgmtObj ; 
 char* taosBuildReqMsgToMnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int taosSendMsgToMnode (int /*<<< orphan*/ *,char*,int) ; 

int vnodeSendMeterCfgMsg(int vnode, int sid) {
  char *        pMsg, *pStart;
  int           msgLen;
  SMeterCfgMsg *pCfg;
  SMgmtObj *    pObj = &mgmtObj;

  pStart = taosBuildReqMsgToMnode(pObj, TSDB_MSG_TYPE_METER_CFG);
  if (pStart == NULL) return -1;
  pMsg = pStart;

  pCfg = (SMeterCfgMsg *)pMsg;
  pCfg->vnode = htonl(vnode);
  pCfg->sid = htonl(sid);
  pMsg += sizeof(SMeterCfgMsg);

  msgLen = pMsg - pStart;
  return taosSendMsgToMnode(pObj, pStart, msgLen);
}