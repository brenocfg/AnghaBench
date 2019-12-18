#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_15__ {size_t vnode; size_t sid; scalar_t__ numOfQueries; scalar_t__ timeStamp; int /*<<< orphan*/  state; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sversion; int /*<<< orphan*/  pCache; struct TYPE_15__* schema; int /*<<< orphan*/  maxBytes; int /*<<< orphan*/  bytesPerPoint; int /*<<< orphan*/  numOfColumns; } ;
struct TYPE_14__ {scalar_t__ lastCreate; int /*<<< orphan*/  vmutex; TYPE_2__** meterList; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SMeterObj ;

/* Variables and functions */
 scalar_t__ TSDB_METER_STATE_DELETING ; 
 scalar_t__ TSDB_METER_STATE_READY ; 
 int /*<<< orphan*/  TSDB_METER_STATE_UPDATING ; 
 int /*<<< orphan*/  dError (char*,size_t,size_t,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dTrace (char*,size_t,size_t,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosTmrStart (void (*) (void*,void*),int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeAllocateCacheInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeClearMeterState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeFreeCacheInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  vnodeIsCacheCommitted (TYPE_2__*) ; 
 scalar_t__ vnodeIsMeterState (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* vnodeList ; 
 void vnodeProcessUpdateSchemaTimer (void*,void*) ; 
 int /*<<< orphan*/  vnodeSaveMeterObjToFile (TYPE_2__*) ; 
 scalar_t__ vnodeSetMeterState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 

void vnodeUpdateMeter(void *param, void *tmrId) {
  SMeterObj *pNew = (SMeterObj *)param;
  if (pNew == NULL || pNew->vnode < 0 || pNew->sid < 0) return;

  SVnodeObj* pVnode = &vnodeList[pNew->vnode];

  if (pVnode->meterList == NULL) {
    dTrace("vid:%d sid:%d id:%s, vnode is deleted, abort update schema", pNew->vnode, pNew->sid, pNew->meterId);
    free(pNew->schema);
    free(pNew);
    return;
  }

  SMeterObj *pObj = pVnode->meterList[pNew->sid];
  if (pObj == NULL || vnodeIsMeterState(pObj, TSDB_METER_STATE_DELETING)) {
    dTrace("vid:%d sid:%d id:%s, meter is deleted, abort update schema", pNew->vnode, pNew->sid, pNew->meterId);
    free(pNew->schema);
    free(pNew);
    return;
  }

  int32_t state = vnodeSetMeterState(pObj, TSDB_METER_STATE_UPDATING);
  if (state >= TSDB_METER_STATE_DELETING) {
    dError("vid:%d sid:%d id:%s, meter is deleted, failed to update, state:%d",
           pObj->vnode, pObj->sid, pObj->meterId, state);
    return;
  }

  int32_t num = 0;
  pthread_mutex_lock(&pVnode->vmutex);
  num = pObj->numOfQueries;
  pthread_mutex_unlock(&pVnode->vmutex);

  if (num > 0 || state != TSDB_METER_STATE_READY) {
    // the state may have been changed by vnodeSetMeterState, recover it in the first place
    vnodeClearMeterState(pObj, TSDB_METER_STATE_UPDATING);
    dTrace("vid:%d sid:%d id:%s, update failed, retry later, numOfQueries:%d, state:%d",
           pNew->vnode, pNew->sid, pNew->meterId, num, state);

    // retry update meter in 50ms
    if (taosTmrStart(vnodeUpdateMeter, 50, pNew, vnodeTmrCtrl) == NULL) {
      dError("vid:%d sid:%d id:%s, failed to start update timer, no retry", pNew->vnode, pNew->sid, pNew->meterId);
      free(pNew->schema);
      free(pNew);
    }
    return;
  }

  // commit first
  if (!vnodeIsCacheCommitted(pObj)) {
    // commit data first
    if (taosTmrStart(vnodeProcessUpdateSchemaTimer, 0, pObj, vnodeTmrCtrl) == NULL) {
      dError("vid:%d sid:%d id:%s, failed to start commit timer", pObj->vnode, pObj->sid, pObj->meterId);
      vnodeClearMeterState(pObj, TSDB_METER_STATE_UPDATING);
      free(pNew->schema);
      free(pNew);
      return;
    }

    if (taosTmrStart(vnodeUpdateMeter, 50, pNew, vnodeTmrCtrl) == NULL) {
      dError("vid:%d sid:%d id:%s, failed to start update timer", pNew->vnode, pNew->sid, pNew->meterId);
      vnodeClearMeterState(pObj, TSDB_METER_STATE_UPDATING);
      free(pNew->schema);
      free(pNew);
    }

    dTrace("vid:%d sid:%d meterId:%s, there are data in cache, commit first, update later",
           pNew->vnode, pNew->sid, pNew->meterId);
    vnodeClearMeterState(pObj, TSDB_METER_STATE_UPDATING);
    return;
  }

  strcpy(pObj->meterId, pNew->meterId);
  pObj->numOfColumns = pNew->numOfColumns;
  pObj->timeStamp = pNew->timeStamp;
  pObj->bytesPerPoint = pNew->bytesPerPoint;
  pObj->maxBytes = pNew->maxBytes;
  if (pObj->timeStamp > vnodeList[pObj->vnode].lastCreate) vnodeList[pObj->vnode].lastCreate = pObj->timeStamp;

  tfree(pObj->schema);
  pObj->schema = pNew->schema;

  vnodeFreeCacheInfo(pObj);
  pObj->pCache = vnodeAllocateCacheInfo(pObj);

  pObj->sversion = pNew->sversion;
  vnodeSaveMeterObjToFile(pObj);
  vnodeClearMeterState(pObj, TSDB_METER_STATE_UPDATING);

  dTrace("vid:%d sid:%d id:%s, schema is updated, state:%d", pObj->vnode, pObj->sid, pObj->meterId, pObj->state);
  free(pNew);
}