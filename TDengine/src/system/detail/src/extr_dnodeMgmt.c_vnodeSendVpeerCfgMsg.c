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
struct TYPE_2__ {int /*<<< orphan*/  vnode; } ;
typedef  TYPE_1__ SVpeerCfgMsg ;
typedef  int /*<<< orphan*/  SMgmtObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_VPEER_CFG ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  mgmtObj ; 
 char* taosBuildReqMsgToMnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendMsgToMnode (int /*<<< orphan*/ *,char*,int) ; 

void vnodeSendVpeerCfgMsg(int vnode) {
  char *        pMsg, *pStart;
  int           msgLen;
  SVpeerCfgMsg *pCfg;
  SMgmtObj *    pObj = &mgmtObj;

  pStart = taosBuildReqMsgToMnode(pObj, TSDB_MSG_TYPE_VPEER_CFG);
  if (pStart == NULL) return;
  pMsg = pStart;

  pCfg = (SVpeerCfgMsg *)pMsg;
  pCfg->vnode = htonl(vnode);
  pMsg += sizeof(SVpeerCfgMsg);

  msgLen = pMsg - pStart;
  taosSendMsgToMnode(pObj, pStart, msgLen);
}