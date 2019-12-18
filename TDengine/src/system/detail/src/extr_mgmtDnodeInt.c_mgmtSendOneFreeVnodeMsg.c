#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * thandle; } ;
struct TYPE_9__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_8__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ SVnodeGid ;
typedef  TYPE_2__ SFreeVnodeMsg ;
typedef  TYPE_3__ SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_FREE_VNODE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* mgmtGetDnode (int /*<<< orphan*/ ) ; 
 char* taosBuildReqMsgToDnode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendMsgToDnode (TYPE_3__*,char*,int) ; 

int mgmtSendOneFreeVnodeMsg(SVnodeGid *pVnodeGid) {
  SFreeVnodeMsg *pFreeVnode;
  char *         pMsg, *pStart;
  int            msgLen = 0;
  SDnodeObj *    pDnode;

  pDnode = mgmtGetDnode(pVnodeGid->ip);
  if (pDnode == NULL) {
    mError("dnode:%s not there", taosIpStr(pVnodeGid->ip));
    return -1;
  }

  if (pDnode->thandle == NULL) {
    mTrace("dnode:%s offline, failed to send Vpeer msg", taosIpStr(pVnodeGid->ip));
    return -1;
  }

  pStart = taosBuildReqMsgToDnode(pDnode, TSDB_MSG_TYPE_FREE_VNODE);
  if (pStart == NULL) return -1;
  pMsg = pStart;

  pFreeVnode = (SFreeVnodeMsg *)pMsg;
  pFreeVnode->vnode = htons(pVnodeGid->vnode);

  pMsg += sizeof(SFreeVnodeMsg);

  msgLen = pMsg - pStart;
  taosSendMsgToDnode(pDnode, pStart, msgLen);

  return 0;
}