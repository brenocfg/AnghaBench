#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_15__ {scalar_t__ state; int numOfQueries; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_14__ {size_t sid; } ;
struct TYPE_13__ {size_t vnode; size_t numOfSids; } ;
struct TYPE_12__ {TYPE_4__** meterList; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SQueryMeterMsg ;
typedef  TYPE_3__ SMeterSidExtInfo ;
typedef  TYPE_4__ SMeterObj ;

/* Variables and functions */
 size_t TSDB_CODE_ACTION_IN_PROGRESS ; 
 size_t TSDB_CODE_NOT_ACTIVE_SESSION ; 
 size_t TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_METER_STATE_DELETING ; 
 scalar_t__ TSDB_METER_STATE_INSERT ; 
 int /*<<< orphan*/  atomic_fetch_add_32 (int*,int) ; 
 int /*<<< orphan*/  dError (char*,TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_2__*,size_t,size_t,size_t,...) ; 
 scalar_t__ vnodeIsMeterState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vnodeList ; 
 int /*<<< orphan*/  vnodeSendMeterCfgMsg (size_t,size_t) ; 

int32_t vnodeIncQueryRefCount(SQueryMeterMsg* pQueryMsg, SMeterSidExtInfo** pSids, SMeterObj** pMeterObjList,
                              int32_t* numOfInc) {
  SVnodeObj* pVnode = &vnodeList[pQueryMsg->vnode];

  int32_t num = 0;
  int32_t code = TSDB_CODE_SUCCESS;

  for (int32_t i = 0; i < pQueryMsg->numOfSids; ++i) {
    SMeterObj* pMeter = pVnode->meterList[pSids[i]->sid];

    if (pMeter == NULL || (pMeter->state > TSDB_METER_STATE_INSERT)) {
      if (pMeter == NULL || vnodeIsMeterState(pMeter, TSDB_METER_STATE_DELETING)) {
        code = TSDB_CODE_NOT_ACTIVE_SESSION;
        dError("qmsg:%p, vid:%d sid:%d, not there or will be dropped", pQueryMsg, pQueryMsg->vnode, pSids[i]->sid);
        vnodeSendMeterCfgMsg(pQueryMsg->vnode, pSids[i]->sid);
      } else {//update or import
        code = TSDB_CODE_ACTION_IN_PROGRESS;
        dTrace("qmsg:%p, vid:%d sid:%d id:%s, it is in state:%d, wait!", pQueryMsg, pQueryMsg->vnode, pSids[i]->sid,
               pMeter->meterId, pMeter->state);
      }
    } else {
      /*
       * vnodeIsSafeToDeleteMeter will wait for this function complete, and then it can
       * check if the numOfQueries is 0 or not.
       */
      pMeterObjList[(*numOfInc)++] = pMeter;
      atomic_fetch_add_32(&pMeter->numOfQueries, 1);

      // output for meter more than one query executed
      if (pMeter->numOfQueries > 1) {
        dTrace("qmsg:%p, vid:%d sid:%d id:%s, inc query ref, numOfQueries:%d", pQueryMsg, pMeter->vnode, pMeter->sid,
               pMeter->meterId, pMeter->numOfQueries);
        num++;
      }
    }
  }

  dTrace("qmsg:%p, query meters: %d, inc query ref %d, numOfQueries on %d meters are 1", pQueryMsg,
         pQueryMsg->numOfSids, *numOfInc, (*numOfInc) - num);

  return code;
}