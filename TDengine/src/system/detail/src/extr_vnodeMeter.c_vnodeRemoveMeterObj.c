#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int maxSessions; } ;
struct TYPE_10__ {int /*<<< orphan*/  lastRemove; TYPE_2__** meterList; TYPE_1__ cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SVnodeCfg ;
typedef  TYPE_2__ SMeterObj ;

/* Variables and functions */
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  TSDB_METER_STATE_DELETED ; 
 int /*<<< orphan*/  dError (char*,int,...) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  vnodeFreeMeterObj (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeIsSafeToDeleteMeter (TYPE_5__*,int) ; 
 TYPE_5__* vnodeList ; 
 int /*<<< orphan*/  vnodeRemoveStream (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeSaveMeterObjToFile (TYPE_2__*) ; 

int vnodeRemoveMeterObj(int vnode, int sid) {
  SMeterObj *pObj;

  if (vnode < 0 || vnode >= TSDB_MAX_VNODES) {
    dError("vid:%d is out of range", vnode);
    return 0;
  }

  SVnodeCfg *pCfg = &vnodeList[vnode].cfg;
  if (sid < 0 || sid >= pCfg->maxSessions) {
    dError("vid:%d, sid:%d is larger than max:%d or less than 0", vnode, sid, pCfg->maxSessions);
    return 0;
  }

  // vnode has been closed, no meters in this vnode
  if (vnodeList[vnode].meterList == NULL) return 0;

  pObj = vnodeList[vnode].meterList[sid];
  if (pObj == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  if (!vnodeIsSafeToDeleteMeter(&vnodeList[vnode], sid)) {
    return TSDB_CODE_ACTION_IN_PROGRESS;
  }

  // after remove this meter, change its state to DELETED
  pObj->state = TSDB_METER_STATE_DELETED;
  pObj->timeStamp = taosGetTimestampMs();
  vnodeList[vnode].lastRemove = pObj->timeStamp;

  vnodeRemoveStream(pObj);
  vnodeSaveMeterObjToFile(pObj);
  vnodeFreeMeterObj(pObj);

  return 0;
}