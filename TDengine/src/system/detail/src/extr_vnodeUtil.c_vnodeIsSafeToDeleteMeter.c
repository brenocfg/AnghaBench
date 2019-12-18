#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {scalar_t__ numOfQueries; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_7__ {int /*<<< orphan*/  vmutex; TYPE_2__** meterList; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_METER_STATE_DELETED ; 
 size_t TSDB_METER_STATE_DELETING ; 
 size_t TSDB_METER_STATE_READY ; 
 int /*<<< orphan*/  dWarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vnodeIsMeterState (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeSetMeterDeleting (TYPE_2__*) ; 
 size_t vnodeSetMeterState (TYPE_2__*,size_t) ; 

bool vnodeIsSafeToDeleteMeter(SVnodeObj* pVnode, int32_t sid) {
  SMeterObj* pObj = pVnode->meterList[sid];

  if (pObj == NULL || vnodeIsMeterState(pObj, TSDB_METER_STATE_DELETED)) {
    return true;
  }

  int32_t prev = vnodeSetMeterState(pObj, TSDB_METER_STATE_DELETING);

  /*
   * if the meter is not in ready/deleting state, it must be in insert/import/update,
   * set the deleting state and wait the procedure to be completed
   */
  if (prev != TSDB_METER_STATE_READY && prev < TSDB_METER_STATE_DELETING) {
    vnodeSetMeterDeleting(pObj);

    dWarn("vid:%d sid:%d id:%s, can not be deleted, state:%d, wait", pObj->vnode, pObj->sid, pObj->meterId, prev);
    return false;
  }

  bool ready = true;

  /*
   * the query will be stopped ASAP, since the state of meter is set to TSDB_METER_STATE_DELETING,
   * and new query will abort since the meter is deleted.
   */
  pthread_mutex_lock(&pVnode->vmutex);
  if (pObj->numOfQueries > 0) {
    dWarn("vid:%d sid:%d id:%s %d queries executing on it, wait query to be finished",
          pObj->vnode, pObj->sid, pObj->meterId, pObj->numOfQueries);
    ready = false;
  }
  pthread_mutex_unlock(&pVnode->vmutex);

  return ready;
}