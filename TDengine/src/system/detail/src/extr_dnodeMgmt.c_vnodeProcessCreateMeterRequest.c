#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_6__ {scalar_t__ maxSessions; } ;
struct TYPE_7__ {scalar_t__ syncStatus; TYPE_1__ cfg; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  int /*<<< orphan*/  SMgmtObj ;
typedef  TYPE_3__ SCreateMsg ;

/* Variables and functions */
 int TSDB_CODE_INVALID_SESSION_ID ; 
 int TSDB_CODE_NOT_ACTIVE_SESSION ; 
 int TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_CREATE_RSP ; 
 scalar_t__ TSDB_SSTATUS_SYNCING ; 
 int /*<<< orphan*/  dError (char*,int) ; 
 int /*<<< orphan*/  dTrace (char*,int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRspToMnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* vnodeList ; 
 int vnodeProcessCreateMeterMsg (char*,int) ; 
 int vnodeSaveCreateMsgIntoQueue (TYPE_2__*,char*,int) ; 

int vnodeProcessCreateMeterRequest(char *pMsg, int msgLen, SMgmtObj *pObj) {
  SCreateMsg *pCreate;
  int         code = 0;
  int         vid;
  SVnodeObj * pVnode;

  pCreate = (SCreateMsg *)pMsg;
  vid = htons(pCreate->vnode);

  if (vid >= TSDB_MAX_VNODES || vid < 0) {
    dError("vid:%d, vnode is out of range", vid);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _over;
  }

  pVnode = vnodeList + vid;
  if (pVnode->cfg.maxSessions <= 0) {
    dError("vid:%d, not activated", vid);
    code = TSDB_CODE_NOT_ACTIVE_SESSION;
    goto _over;
  }

  if (pVnode->syncStatus == TSDB_SSTATUS_SYNCING) {
    code = vnodeSaveCreateMsgIntoQueue(pVnode, pMsg, msgLen);
    dTrace("vid:%d, create msg is saved into sync queue", vid);
  } else {
    code = vnodeProcessCreateMeterMsg(pMsg, msgLen);
  }

_over:
  taosSendSimpleRspToMnode(pObj, TSDB_MSG_TYPE_CREATE_RSP, code);

  return code;
}