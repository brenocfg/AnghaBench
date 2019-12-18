#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ sqlLen; int /*<<< orphan*/ * pStream; int /*<<< orphan*/  lastKey; int /*<<< orphan*/  pSql; int /*<<< orphan*/  meterId; int /*<<< orphan*/  vnode; } ;
struct TYPE_7__ {int maxSessions; char* acct; } ;
struct TYPE_8__ {scalar_t__ streamRole; int /*<<< orphan*/  numOfStreams; int /*<<< orphan*/ * dbConn; int /*<<< orphan*/ * streamTimer; int /*<<< orphan*/  vnode; TYPE_1__ cfg; TYPE_3__** meterList; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_METER_STATE_DELETING ; 
 int /*<<< orphan*/  dError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * taos_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taos_open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsInternalPass ; 
 int /*<<< orphan*/  vnodeCloseStreamCallback ; 
 int /*<<< orphan*/  vnodeGetDBFromMeterId (TYPE_3__*,char*) ; 
 scalar_t__ vnodeIsMeterState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeProcessStreamRes ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 

void vnodeOpenStreams(void *param, void *tmrId) {
  SVnodeObj *pVnode = (SVnodeObj *)param;
  SMeterObj *pObj;

  if (pVnode->streamRole == 0) return;
  if (pVnode->meterList == NULL) return;

  taosTmrStopA(&pVnode->streamTimer);
  pVnode->streamTimer = NULL;

  for (int sid = 0; sid < pVnode->cfg.maxSessions; ++sid) {
    pObj = pVnode->meterList[sid];
    if (pObj == NULL || pObj->sqlLen == 0 || vnodeIsMeterState(pObj, TSDB_METER_STATE_DELETING)) continue;

    dTrace("vid:%d sid:%d id:%s, open stream:%s", pObj->vnode, sid, pObj->meterId, pObj->pSql);

    if (pVnode->dbConn == NULL) {
      char db[64] = {0};
      char user[64] = {0};
      vnodeGetDBFromMeterId(pObj, db);
      sprintf(user, "_%s", pVnode->cfg.acct);
      pVnode->dbConn = taos_connect(NULL, user, tsInternalPass, db, 0);
    }

    if (pVnode->dbConn == NULL) {
      dError("vid:%d, failed to connect to mgmt node", pVnode->vnode);
      taosTmrReset(vnodeOpenStreams, 1000, param, vnodeTmrCtrl, &pVnode->streamTimer);
      return;
    }

    if (pObj->pStream == NULL) {
      pObj->pStream = taos_open_stream(pVnode->dbConn, pObj->pSql, vnodeProcessStreamRes, pObj->lastKey, pObj,
                                       vnodeCloseStreamCallback);
      if (pObj->pStream) pVnode->numOfStreams++;
    }
  }
}