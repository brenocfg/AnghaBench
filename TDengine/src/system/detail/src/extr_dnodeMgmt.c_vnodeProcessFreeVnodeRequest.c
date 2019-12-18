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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ vnode; } ;
typedef  int /*<<< orphan*/  SMgmtObj ;
typedef  TYPE_1__ SFreeVnodeMsg ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_ACTION_IN_PROGRESS ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_FREE_VNODE_RSP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dTrace (char*,scalar_t__) ; 
 int /*<<< orphan*/  dWarn (char*,scalar_t__) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  taosSendSimpleRspToMnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vnodeRemoveVnode (scalar_t__) ; 

int vnodeProcessFreeVnodeRequest(char *pMsg, int msgLen, SMgmtObj *pMgmtObj) {
  SFreeVnodeMsg *pFree;

  pFree = (SFreeVnodeMsg *)pMsg;
  pFree->vnode = htons(pFree->vnode);

  if (pFree->vnode < 0 || pFree->vnode >= TSDB_MAX_VNODES) {
    dWarn("vid:%d out of range", pFree->vnode);
    return -1;
  }

  dTrace("vid:%d receive free vnode message", pFree->vnode);
  int32_t code = vnodeRemoveVnode(pFree->vnode);
  assert(code == TSDB_CODE_SUCCESS || code == TSDB_CODE_ACTION_IN_PROGRESS);

  taosSendSimpleRspToMnode(pMgmtObj, TSDB_MSG_TYPE_FREE_VNODE_RSP, code);
  return 0;
}