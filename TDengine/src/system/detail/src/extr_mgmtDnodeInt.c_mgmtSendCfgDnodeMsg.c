#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  config; int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  thandle; int /*<<< orphan*/  privateIp; } ;
typedef  TYPE_1__ SDnodeObj ;
typedef  TYPE_2__ SCfgMsg ;

/* Variables and functions */
 int TSDB_CODE_NODE_OFFLINE ; 
 int TSDB_CODE_NOT_CONFIGURED ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CFG_PNODE ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int mgmtCfgDynamicOptions (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 char* taosBuildReqMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendMsgToDnode (TYPE_1__*,char*,int) ; 

int mgmtSendCfgDnodeMsg(char *cont) {
  char *     pMsg, *pStart;
  int        msgLen = 0;
  SDnodeObj *pDnode;
  SCfgMsg *  pCfg = (SCfgMsg *)cont;
  uint32_t   ip;

  ip = inet_addr(pCfg->ip);
  pDnode = mgmtGetDnode(ip);
  if (pDnode == NULL) {
    mError("dnode ip:%s not configured", pCfg->ip);
    return TSDB_CODE_NOT_CONFIGURED;
  }

  mTrace("dnode:%s, dynamic option received, content:%s", taosIpStr(pDnode->privateIp), pCfg->config);
  int code = mgmtCfgDynamicOptions(pDnode, pCfg->config);
  if (code != -1) {
    return code;
  }

  pStart = taosBuildReqMsg(pDnode->thandle, TSDB_MSG_TYPE_CFG_PNODE);
  if (pStart == NULL) return TSDB_CODE_NODE_OFFLINE;
  pMsg = pStart;

  memcpy(pMsg, cont, sizeof(SCfgMsg));
  pMsg += sizeof(SCfgMsg);

  msgLen = pMsg - pStart;
  taosSendMsgToDnode(pDnode, pStart, msgLen);

  return 0;
}