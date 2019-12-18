#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_15__ {scalar_t__ numOfQueries; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_14__ {int numOfMeters; TYPE_3__* pSidSet; int /*<<< orphan*/  pMeterObj; } ;
struct TYPE_13__ {TYPE_1__* pObj; TYPE_5__* pMeterQuerySupporter; } ;
struct TYPE_12__ {TYPE_2__** pSids; } ;
struct TYPE_11__ {int /*<<< orphan*/  sid; } ;
struct TYPE_10__ {scalar_t__ numOfQueries; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
typedef  TYPE_4__ SQInfo ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_sub_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_4__*,size_t,size_t,...) ; 
 TYPE_6__* getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnodeDecMeterRefcnt(SQInfo *pQInfo) {
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  if (pSupporter == NULL || pSupporter->numOfMeters == 1) {
    atomic_fetch_sub_32(&pQInfo->pObj->numOfQueries, 1);
    dTrace("QInfo:%p vid:%d sid:%d meterId:%s, query is over, numOfQueries:%d", pQInfo, pQInfo->pObj->vnode,
           pQInfo->pObj->sid, pQInfo->pObj->meterId, pQInfo->pObj->numOfQueries);
  } else {
    int32_t num = 0;
    for (int32_t i = 0; i < pSupporter->numOfMeters; ++i) {
      SMeterObj *pMeter = getMeterObj(pSupporter->pMeterObj, pSupporter->pSidSet->pSids[i]->sid);
      atomic_fetch_sub_32(&(pMeter->numOfQueries), 1);

      if (pMeter->numOfQueries > 0) {
        dTrace("QInfo:%p vid:%d sid:%d meterId:%s, query is over, numOfQueries:%d", pQInfo, pMeter->vnode, pMeter->sid,
               pMeter->meterId, pMeter->numOfQueries);
        num++;
      }
    }

    /*
     * in order to reduce log output, for all meters of which numOfQueries count are 0,
     * we do not output corresponding information
     */
    num = pSupporter->numOfMeters - num;
    dTrace("QInfo:%p metric query is over, dec query ref for %d meters, numOfQueries on %d meters are 0", pQInfo,
           pSupporter->numOfMeters, num);
  }
}