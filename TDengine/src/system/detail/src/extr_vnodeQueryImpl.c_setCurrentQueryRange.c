#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* pMeterQInfo; TYPE_2__* pMeterObj; } ;
struct TYPE_6__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_5__ {int /*<<< orphan*/  lastKey; int /*<<< orphan*/  ekey; int /*<<< orphan*/  skey; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  int /*<<< orphan*/  SQInfo ;
typedef  TYPE_1__ SMeterQueryInfo ;
typedef  TYPE_2__ SMeterObj ;
typedef  TYPE_3__ SMeterDataInfo ;

/* Variables and functions */
 scalar_t__ GET_QINFO_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qTrace (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool setCurrentQueryRange(SMeterDataInfo *pMeterDataInfo, SQuery *pQuery, TSKEY endKey, TSKEY *minval,
                                 TSKEY *maxval) {
  SQInfo *         pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);
  SMeterObj *      pMeterObj = pMeterDataInfo->pMeterObj;
  SMeterQueryInfo *pMeterQInfo = pMeterDataInfo->pMeterQInfo;

  if (QUERY_IS_ASC_QUERY(pQuery)) {
    *minval = pMeterQInfo->lastKey;
    *maxval = endKey;
  } else {
    *minval = endKey;
    *maxval = pMeterQInfo->lastKey;
  }

  if (*minval > *maxval) {
    qTrace("QInfo:%p vid:%d sid:%d id:%s, no result in files, qrange:%lld-%lld, lastKey:%lld", pQInfo, pMeterObj->vnode,
           pMeterObj->sid, pMeterObj->meterId, pMeterQInfo->skey, pMeterQInfo->ekey, pMeterQInfo->lastKey);
    return false;
  } else {
    qTrace("QInfo:%p vid:%d sid:%d id:%s, query in files, qrange:%lld-%lld, lastKey:%lld", pQInfo, pMeterObj->vnode,
           pMeterObj->sid, pMeterObj->meterId, pMeterQInfo->skey, pMeterQInfo->ekey, pMeterQInfo->lastKey);
    return true;
  }
}