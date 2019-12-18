#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_18__ {scalar_t__ lastResRows; } ;
struct TYPE_17__ {size_t meterOrderIdx; TYPE_8__* pMeterQInfo; int /*<<< orphan*/  pMeterObj; } ;
struct TYPE_14__ {int /*<<< orphan*/  pMeterObj; TYPE_4__* pQuery; } ;
struct TYPE_16__ {size_t numOfMeters; TYPE_2__* pSidSet; int /*<<< orphan*/  pMeterObj; TYPE_6__* pMeterDataInfo; TYPE_3__ runtimeEnv; } ;
struct TYPE_15__ {scalar_t__ nAggTimeInterval; } ;
struct TYPE_13__ {TYPE_1__** pSids; } ;
struct TYPE_12__ {int /*<<< orphan*/  sid; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterDataInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saveResult (TYPE_5__*,TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  setIntervalQueryExecutionContext (TYPE_5__*,size_t,TYPE_8__*) ; 

void doCloseAllOpenedResults(SMeterQuerySupportObj *pSupporter) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;

  /* for interval query, close all unclosed results */
  if (pQuery->nAggTimeInterval > 0) {
    SMeterDataInfo *pMeterInfo = pSupporter->pMeterDataInfo;
    for (int32_t i = 0; i < pSupporter->numOfMeters; ++i) {
      if (pMeterInfo[i].pMeterQInfo != NULL && pMeterInfo[i].pMeterQInfo->lastResRows > 0) {
        int32_t index = pMeterInfo[i].meterOrderIdx;

        pRuntimeEnv->pMeterObj = getMeterObj(pSupporter->pMeterObj, pSupporter->pSidSet->pSids[index]->sid);
        assert(pRuntimeEnv->pMeterObj == pMeterInfo[i].pMeterObj);

        setIntervalQueryExecutionContext(pSupporter, i, pMeterInfo[i].pMeterQInfo);
        saveResult(pSupporter, pMeterInfo[i].pMeterQInfo, pMeterInfo[i].pMeterQInfo->lastResRows);
      }
    }
  }
}