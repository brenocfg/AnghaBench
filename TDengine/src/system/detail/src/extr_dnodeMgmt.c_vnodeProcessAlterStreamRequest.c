#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int status; scalar_t__ stime; int /*<<< orphan*/  uid; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_11__ {int sid; int vnode; int status; scalar_t__ lastKey; } ;
struct TYPE_9__ {int /*<<< orphan*/  maxSessions; } ;
struct TYPE_10__ {TYPE_3__** meterList; TYPE_1__ cfg; int /*<<< orphan*/ * pCachePool; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  int /*<<< orphan*/  SMgmtObj ;
typedef  TYPE_3__ SMeterObj ;
typedef  TYPE_4__ SAlterStreamMsg ;

/* Variables and functions */
 int TSDB_CODE_INVALID_SESSION_ID ; 
 int TSDB_CODE_NOT_ACTIVE_SESSION ; 
 int TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_STREAM_RSP ; 
 int /*<<< orphan*/  dError (char*,int,...) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRspToMnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnodeCreateStream (TYPE_3__*) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeRemoveStream (TYPE_3__*) ; 
 int /*<<< orphan*/  vnodeSaveMeterObjToFile (TYPE_3__*) ; 

int vnodeProcessAlterStreamRequest(char *pMsg, int msgLen, SMgmtObj *pObj) {
  SAlterStreamMsg *pAlter;
  int              code = 0;
  int              vid, sid;
  SVnodeObj *      pVnode;

  pAlter = (SAlterStreamMsg *)pMsg;
  vid = htons(pAlter->vnode);
  sid = htonl(pAlter->sid);

  if (vid >= TSDB_MAX_VNODES || vid < 0) {
    dError("vid:%d, vnode is out of range", vid);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _over;
  }

  pVnode = vnodeList + vid;
  if (pVnode->cfg.maxSessions <= 0 || pVnode->pCachePool == NULL) {
    dError("vid:%d is not activated yet", pAlter->vnode);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _over;
  }

  if (pAlter->sid >= pVnode->cfg.maxSessions || pAlter->sid < 0) {
    dError("vid:%d sid:%d uid:%ld, sid is out of range", pAlter->vnode, pAlter->sid, pAlter->uid);
    code = TSDB_CODE_INVALID_SESSION_ID;
    goto _over;
  }

  SMeterObj *pMeterObj = vnodeList[vid].meterList[sid];
  if (pMeterObj == NULL || sid != pMeterObj->sid || vid != pMeterObj->vnode) {
    dError("vid:%d sid:%d, no active session", vid, sid);
    code = TSDB_CODE_NOT_ACTIVE_SESSION;
    goto _over;
  }

  pMeterObj->status = pAlter->status;
  if (pMeterObj->status == 1) {
    if (pAlter->stime > pMeterObj->lastKey)  // starting time can be specified
      pMeterObj->lastKey = pAlter->stime;
    vnodeCreateStream(pMeterObj);
  } else {
    vnodeRemoveStream(pMeterObj);
  }

  vnodeSaveMeterObjToFile(pMeterObj);

_over:
  taosSendSimpleRspToMnode(pObj, TSDB_MSG_TYPE_ALTER_STREAM_RSP, code);

  return code;
}